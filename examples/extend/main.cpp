#include "tcl++/commands/UnixCommandParser.h"
#include "tcl++/core/Dict.h"
#include "tcl++/core/List.h"
#include "tcl++/extend/defs.h"

#include <memory>

class DummyValidator : public tcl::ArgValidator {
 public:
  void validate(tcl::Interp &interp, tcl::Object &obj) override {
    m_value = "dummy " + obj.getStringRep();
  }

  const std::string &value() { return m_value; }

 private:
  std::string m_value;
};

class HelloCmd : public tcl::BaseCommand {
  tcl::CompletionCode proc(tcl::Interp &interp, tcb::span<tcl::Object> args) override {
    tcl::List l;
    for (const auto &arg : args) {
      l.append(arg.getStringRep());
    }
    interp.setResult(tcl::Dict().put("args", l));
    return tcl::CompletionCode::OK;
  }
};

class AddSubCmd : public tcl::UnixCommandParser {
 public:
  AddSubCmd() { setSwitch("-value", m_arg); }
  void doLogic(tcl::Interp &interp) override {
    if (handledSwitch("-value")) {
      interp.setResult(tcl::String("switch provided, value is " + m_arg.value()));
    }
    else {
      interp.setResult(tcl::String("no switch provided"));
    }
  }

 private:
  DummyValidator m_arg;
};

class CalcCmd : public tcl::UnixCommandParser {
 public:
  CalcCmd() {
    setSubcommand("add", std::make_unique<AddSubCmd>());
    requireSubcommand();
  }
  void doLogic(tcl::Interp &interp) override { interp.setResult(tcl::String("calc cmd")); }
};

MAKE_EXTENSION(Math_example, "1.0", myinterp) {
  myinterp.setVar("test_var", tcl::String("test_value"));
  myinterp.registerCommand("hello_cmd", std::make_unique<HelloCmd>());
  myinterp.registerCommand("calc", std::make_unique<CalcCmd>());
}
