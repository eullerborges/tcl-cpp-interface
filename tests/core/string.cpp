#include "tcl++/core/String.h"
#include "tcl++/core/Interp.h"

#include "catch2/catch.hpp"

SCENARIO("String base operations", "[string]") {
  GIVEN("The initialization of a Tcl String") {
    tcl::Interp interp;

    WHEN("initialized with a character array with auto size") {
      const char *initialRep = "initial rep";
      tcl::String s{initialRep};
      THEN("string's representation is equivalent to the array") {
        CHECK(s.getStringRep() == "initial rep");
      }
    }

    WHEN("initialized with a character array with determined size") {
      std::string initialRep = "initial rep";
      std::size_t charsToCopy = initialRep.size() - 3;
      tcl::String s{initialRep.c_str(), charsToCopy};
      THEN("string's representation is equivalent to the array") {
        CHECK(s.getStringRep() == initialRep.substr(0, charsToCopy));
      }
    }

    WHEN("initialized with an std::string") {
      std::string initialRep = "initial rep";
      tcl::String s{initialRep};
      THEN("string's representation is equivalent to std::string") {
        CHECK(s.getStringRep() == initialRep);
      }
    }
  }
}
