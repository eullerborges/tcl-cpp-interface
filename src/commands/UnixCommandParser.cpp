#include "tcl++/commands/UnixCommandParser.h"

#include "tcl++/core/Exception.h"
#include "tcl++/core/Interp.h"
#include "tcl.h"

#include <fmt/format.h>

#include <iostream>
#include <vector>

#define DEBUG 1 && std::cerr << "[DEBUG] "

using tcl::CompletionCode;
using tcl::UnixCommandParser;

static bool isString(const tcl::Object& obj) { return obj.getNativeRep()->bytes; }

static bool validSwitchSyntax(const std::string& name) { return name.size() && name[0] == '-'; }

void UnixCommandParser::reset() {
  m_matchedSwitches.clear();
  m_matchedPositionalArgs = 0;
}

CompletionCode UnixCommandParser::proc(Interp& interp, tcb::span<tcl::Object> args) {
  try {
    parse(interp, tcb::span<tcl::Object>(args));
    return CompletionCode::OK;
  } catch (const tcl::Exception& exc) {
    interp.setResult(tcl::String(exc.what()));
    return CompletionCode::ERROR;
  }
}

void UnixCommandParser::parse(Interp& interp, tcb::span<tcl::Object> args) {
  reset();  // Reset all state
  if (args.size() > 1) {
    // If we've received a subcommand, parse it.
    tcl::Object& possibleSubcommand = args[1];
    if (isString(possibleSubcommand) && m_subcommands.count(possibleSubcommand.getStringRep())) {
      DEBUG << fmt::format("Subcommand matched: '{}'\n", possibleSubcommand.getStringRep());
      // Ignore the current command name.
      m_subcommands[possibleSubcommand.getStringRep()]->parse(interp, args.subspan(1));
      return;
    }
  }

  auto argsToParse = args.subspan(1);
  for (auto it = argsToParse.begin(); it != argsToParse.end(); ++it) {
    DEBUG << "Proccessing " << it->getStringRep() << "\n";
    if (isString(*it)) {
      // Process switches
      std::string switchStr = it->getStringRep();
      if (validSwitchSyntax(switchStr) && m_switches.count(switchStr)) {
        auto& zwitch = m_switches[switchStr];
        if (zwitch.validator) {
          if (!std::distance(++it, argsToParse.end())) {
            throw tcl::Exception(fmt::format("switch '{}' expects an argument", switchStr));
          }
          DEBUG << fmt::format("Switch '{}' has argument, calling validator.\n", switchStr);
          // Validate switch's arguments.
          zwitch.validator->validateArg(interp, *it);
        }
        // Record we've parsed this switch.
        m_matchedSwitches.insert(switchStr);
        DEBUG << fmt::format("Inserted Switch: {}\n", switchStr);
        // Continue parsing arguments
        continue;
      }
    }

    if (m_matchedPositionalArgs < m_positionalArgs.size()) {
      // This is an argument to the command.
      m_positionalArgs[m_matchedPositionalArgs].validator->validateArg(interp, *it);
      DEBUG << fmt::format("Matched argument: {}\n", it->getStringRep());
      ++m_matchedPositionalArgs;
      continue;
    }

    throw tcl::Exception(fmt::format("command does not take argument '{}'", it->getStringRep()));
  }

  if ((m_matchedPositionalArgs != m_positionalArgs.size()) ||
      (m_positionalArgs.size() == 1 && !m_matchedPositionalArgs && !m_positionalArgs[0].isOptional)) {
    // We have to either match all required arguments, or have no arguments (and possibly a single
    // positional optional argument).
    throw tcl::Exception("missing required argument");
  }

  if (m_requireSubcommand) {
    // If we got to this point, then no subcommand has matched.
    throw tcl::Exception("command requires subcommand");
  }
  doLogic(interp);
}

void UnixCommandParser::setSubcommand(const std::string& name,
                                      std::unique_ptr<UnixCommandParser>&& parser) {
  m_subcommands.emplace(name, std::move(parser));
}

void UnixCommandParser::setSwitch(const std::string& name, ArgValidator& validator)

{
  assert(validSwitchSyntax(name));
  m_switches.emplace(name, tcl::internal::Switch{&validator, false /*isOptional*/});
}

bool UnixCommandParser::handledSwitch(const std::string& switchName) {
  assert(m_switches.count(switchName));
  return m_matchedSwitches.count(switchName);
}

void UnixCommandParser::setPositionalArg(ArgValidator& validator, bool optional) {
  // We can't disambiguate several optional arguments, thus we limit to one per command.
  assert((!optional || !m_positionalArgs.size()) && "Can only set one positional argument at a time.");
  m_positionalArgs.push_back(tcl::internal::Argument{&validator, optional});
}
