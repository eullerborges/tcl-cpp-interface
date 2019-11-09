#include "tcl++/core/Dict.h"
#include "tcl++/core/Interp.h"
#include "tcl++/core/List.h"
#include "tcl++/core/String.h"

#include "catch2/catch.hpp"

#include <memory>

SCENARIO("Object memory management", "[object]") {
  GIVEN("The initialization of an Object") {
    tcl::Interp interp;

    WHEN("copy constructed") {
      tcl::String other;
      tcl::String first{other};
      THEN("new object is allocated") {
        CHECK(first.getNativeRep() != other.getNativeRep());
      }
    }

    WHEN("move constructed") {
      tcl::String other;
      auto *otherRep = other.getNativeRep();
      tcl::String first{std::move(other)};
      THEN("object takes ownership of moved") {
        CHECK(first.getNativeRep() == otherRep);
        CHECK(other.getNativeRep() == nullptr);
      }
    }
  }

  GIVEN("An initialized Object") {
    tcl::Interp interp;
    tcl::String first;
    auto *firstRep = first.getNativeRep();
    WHEN("copy assigned") {
      tcl::String other;
      first = other;
      THEN("new object is allocated") {
        CHECK(first.getNativeRep() != other.getNativeRep());
      }
    }
    WHEN("copy assigned") {
      tcl::String other;
      auto *otherRep = other.getNativeRep();
      first = std::move(other);
      THEN("internal representations are swapped") {
        CHECK(first.getNativeRep() == otherRep);
        CHECK(other.getNativeRep() == firstRep);
      }
    }
  }
}
