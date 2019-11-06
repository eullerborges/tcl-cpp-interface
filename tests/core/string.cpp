#include "tcl++/core/Interp.h"
#include "tcl++/core/List.h"
#include "tcl++/core/String.h"

#include "catch2/catch.hpp"

SCENARIO("String base operations", "[string]") {
  GIVEN("The initialization of a string") {
    tcl::Interp interp;

    WHEN("copy constructor") {
      const char *otherRep = "copied representation";
      tcl::String other{otherRep};
      tcl::String first{other};
      THEN("String representation is equivalent") {
        REQUIRE(first.getStringRep() == otherRep);
        REQUIRE(other.getStringRep() == otherRep);
      }
    }

    WHEN("move constructor") {
      const char *otherRep = "copied representation";
      tcl::String other{otherRep};
      tcl::String first{std::move(other)};
      THEN("String representation is equivalent") {
        REQUIRE(first.getStringRep() == otherRep);
        REQUIRE(other.getNativeRep() == nullptr);
      }
    }
  }

  GIVEN("An initial Tcl string") {
    tcl::Interp interp;
    const char* initialRep = "initial rep";
    tcl::String s {initialRep};
    REQUIRE(s.getStringRep() == "initial rep");

    WHEN("copy assignment operator") {
      const char *otherRep = "copied representation";
      tcl::String other {otherRep};
      s = other;
      THEN("String representation change") {
        REQUIRE(s.getStringRep() == otherRep);
      }
    }

    WHEN("move assignment operator") {
      const char *otherRep = "moved representation";
      tcl::String other{otherRep};
      s = std::move(other);
      THEN("String representation change") {
        REQUIRE(s.getStringRep() == otherRep);
        REQUIRE(other.getStringRep() == initialRep);
      }
    }
  }
}
