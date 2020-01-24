#ifndef TCL_UNIXCOMMANDPARSER_H
#define TCL_UNIXCOMMANDPARSER_H

#include "ArgValidator.h"
#include "tcl++/core/BaseCommand.h"
#include "tcl++/core/Object.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace tcl {

namespace internal {
struct Switch {
  ArgValidator* validator;  //! The argument validator for this switch.
  bool isOptional;          //! This switch is optional on the command line.
};

struct Argument {
  ArgValidator* validator;  //! The argument validator for the argument.
  bool isOptional;          //! This argument is optional on the command line.
};
}  // namespace internal

/**
 * @brief Implementation of a unix-like command parser.
 *
 * This class can be used to model a command's behaviour on the interpreter. One
 * can define subcommands, switches and argument handlers to define the needed logic.
 *
 * Application logic should inherit from this class, setup the command behaviour
 * on the constructor and the infrastructure will take care of verifying syntax.
 *
 * If any errors happen during syntax verification, the command execution will
 * exit with an error set to the interpreter. The doLogic method should be
 * implemented by the application, and is only called when the syntax is ok. At
 * that point all argument validators will have already been handled and the
 * application can proceed with the main command logic.
 */
class UnixCommandParser : public tcl::BaseCommand {
 public:
  /**
   * @brief Implements the main logic for the command.
   * @param interp The running interpreter where the command was matched.
   * @note The application can assume the syntax is valid when this method is run.
   */
  virtual void doLogic(Interp& interp) = 0;

  /**
   * @brief Sets up a subcommand on the syntax.
   * @param name The name of the switch to add to the syntax.
   * @param parser The parser implementation for the added subcommand.
   * @note The subcommand is only matched when it is the first argument to this command.
   */
  void setSubcommand(const std::string& name, std::unique_ptr<UnixCommandParser>&& parser);
  //! Marks this command as being an "ensemble", meaning its syntax requires a subcommand.
  void requireSubcommand() { m_requireSubcommand = true; }

  /**
   * @brief Sets up a switch with an argument on the syntax.
   * @param name The name of the switch to set.
   * @param validator The validator for the switch's argument.
   */
  void setSwitch(const std::string& name, ArgValidator& validator);
  //! Returns whether a given switch was provided to this command.
  bool handledSwitch(const std::string& switchName);

  void setPositionalArg(ArgValidator& validator, bool optional = false);

 protected:
  /**
   * @brief Entry point to the command coming from the interpreter.
   * @warning Improper overriding will break the syntax parsing.
   */
  CompletionCode proc(Interp& interp, tcb::span<tcl::Object> args) override;
  /**
   * @brief Implementation of the parser logic.
   * @warning Improper overriding will break the syntax parsing.
   */
  void parse(Interp& interp, tcb::span<tcl::Object> args);

 private:
  void reset();

  std::unordered_map<std::string, std::unique_ptr<UnixCommandParser>> m_subcommands;
  std::unordered_map<std::string, internal::Switch> m_switches;
  std::vector<internal::Argument> m_positionalArgs;
  bool m_requireSubcommand{false};

  // State reset before every parse
  std::unordered_set<std::string> m_matchedSwitches;
  std::size_t m_matchedPositionalArgs {0};
};

};  // namespace tcl

#endif
