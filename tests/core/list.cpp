#include "tcl++/core/Interp.h"
#include "tcl++/core/List.h"
#include "tcl++/core/String.h"

#include "catch2/catch.hpp"

SCENARIO("List base operations", "[list]") {
  GIVEN("An initial Tcl list") {
    tcl::Interp interp;
    tcl::List l;
    REQUIRE(l.size() == 0);

    WHEN("elements appended") {
      l.append("appended").append("elements");
      THEN("Size and string representation change") {
        REQUIRE(l.size() == 2);
        REQUIRE(l.getStringRep() == "appended elements");
      }
    }

    WHEN("other lists appended") {
      auto l2 = tcl::List().append("single_element");
      auto l3 = tcl::List().append("multiple").append("elements");
      l.append(l2).append(l3);
      THEN("Size and string representation change") {
        REQUIRE(l.size() == 2);
        REQUIRE(l.getStringRep() == "single_element {multiple elements}");
      }
    }

    WHEN("spliced with other list") {
      auto other = tcl::List().append("underlying").append("elements");
      auto to_splice = tcl::List().append("several").append(other).append("inside");
      l.splice(to_splice);
      THEN("Size and string representation change") {
        REQUIRE(l.size() == 3);
        REQUIRE(l.getStringRep() == "several {underlying elements} inside");
      }
    }
  }
}
