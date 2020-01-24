#include "tcl++/commands/UnixCommandParser.h"

#include "tcl++/core/Interp.h"
#include "tcl++/core/NumericTypes.h"
#include "tcl++/core/String.h"

#include <catch2/catch.hpp>

#include <memory>

class IntVal : public tcl::ArgValidator {
 public:
  void validate(tcl::Interp &interp, tcl::Object &obj) override { m_value = obj.as<tcl::Int>(); }

  const int value() { return m_value.value(); }

 private:
  tcl::Int m_value;
};

class DummyValidator : public tcl::ArgValidator {
 public:
  void validate(tcl::Interp &interp, tcl::Object &obj) override {
    m_value = "dummy " + obj.getStringRep();
  }

  const std::string &value() { return m_value; }

 private:
  std::string m_value;
};

class BasicCmd : public tcl::UnixCommandParser {
public:
  void doLogic(tcl::Interp &interp) override { interp.setResult(tcl::String("basic cmd")); }
};

class AddSubCmd : public tcl::UnixCommandParser {
public:
  AddSubCmd() {
    setSwitch("-value", m_dummy);
    setPositionalArg(m_operand1);
    setPositionalArg(m_operand2);
  }
  void doLogic(tcl::Interp &interp) override {
    if (handledSwitch("-value")) {
      interp.setResult(tcl::String("switch provided: " + m_dummy.value()));
    }
    else {
      interp.setResult(tcl::Int(m_operand1.value() + m_operand2.value()));
    }
  }

private:
  DummyValidator m_dummy;
  IntVal m_operand1;
  IntVal m_operand2;
};

class CalcCmd : public tcl::UnixCommandParser {
public:
  CalcCmd() {
    setSubcommand("add", std::make_unique<AddSubCmd>());
    requireSubcommand();
  }
  void doLogic(tcl::Interp &interp) override { interp.setResult(tcl::String("unreachable")); }
};


SCENARIO("UnixCommandParser basic operations", "[unix_cmd_parser]") {
  tcl::Interp interp;
  GIVEN("Command with no subcommand provided") {
    // interp.registerCommand("calc", std::make_unique<CalcCmd>());
    interp.registerCommand("basic", std::make_unique<BasicCmd>());

    WHEN("basic evaluation") {
      auto res = interp.eval("basic");
      THEN ("interp result is set to evaluation") {
        REQUIRE(res == tcl::CompletionCode::OK);
        REQUIRE(interp.getResult().getStringRep() == "basic cmd");
      }
    }

    WHEN("providing invalid argument") {
      auto res = interp.eval("basic invalid_arg");
      THEN ("interp result set to error with invalid argument") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "command does not take argument 'invalid_arg'");
      }
    }

    WHEN("providing invalid argument") {
      auto res = interp.eval("basic invalid_arg");
      THEN ("interp result set to error with invalid argument") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "command does not take argument 'invalid_arg'");
      }
    }
  }

  GIVEN("Command registered with required subcommand") {
    interp.registerCommand("calc", std::make_unique<CalcCmd>());

    WHEN("basic evaluation") {
      auto res = interp.eval("calc");
      THEN ("interp set to error, subcommand required") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "command requires subcommand");
      }
    }

    WHEN("argument provided to base command") {
      auto res = interp.eval("calc invalid_arg");
      THEN ("interp result set to error with invalid argument") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "command does not take argument 'invalid_arg'");
      }
    }

    WHEN("invalid argument provided to positional argument") {
      auto res = interp.eval("calc add invalid_arg");
      THEN ("ArgValidator error is set as result") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "Could not convert object to numeric representation");
      }
    }

    WHEN("missing first positional argument") {
      auto res = interp.eval("calc add");
      THEN ("missing argument error is set") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "missing required argument");
      }
    }

    WHEN("first argument is valid but second is missing") {
      auto res = interp.eval("calc add 1");
      THEN ("missing argument error is set") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "missing required argument");
      }
    }

    WHEN("excessive number of arguments") {
      auto res = interp.eval("calc add 1 2 3");
      THEN ("interp result set to error with invalid argument") {
        REQUIRE(res == tcl::CompletionCode::ERROR);
        REQUIRE(interp.getResult().getStringRep() == "command does not take argument '3'");
      }
    }

    WHEN("valid arguments provided") {
      auto res = interp.eval("calc add 11 28");
      THEN ("interp result set to command evaluation logic result") {
        REQUIRE(res == tcl::CompletionCode::OK);
        REQUIRE(interp.getResult().as<tcl::Int>().value() == 39);
      }
    }

    WHEN("valid arguments provided with switch at end") {
      auto res = interp.eval("calc add 11 28 -value sw_val");
      THEN ("switch is processed as present by command logic") {
        REQUIRE(res == tcl::CompletionCode::OK);
        REQUIRE(interp.getResult().getStringRep() == "switch provided: dummy sw_val");
      }
    }

    WHEN("valid arguments provided with switch at beginning") {
      auto res = interp.eval("calc add -value sw_val 28 11");
      THEN ("switch is processed as present by command logic") {
        REQUIRE(res == tcl::CompletionCode::OK);
        REQUIRE(interp.getResult().getStringRep() == "switch provided: dummy sw_val");
      }
    }

    WHEN("valid arguments provided with switch interleaved") {
      auto res = interp.eval("calc add 28 -value sw_val 11");
      THEN ("switch is processed as present by command logic") {
        // REQUIRE(res == tcl::CompletionCode::OK);
        REQUIRE(interp.getResult().getStringRep() == "switch provided: dummy sw_val");
      }
    }
  }
}
