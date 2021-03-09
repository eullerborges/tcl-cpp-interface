#include "tcl++/core/List.h"

#include "tcl++/core/Interp.h"
#include "tcl++/core/String.h"

#include <catch2/catch.hpp>

SCENARIO("List base operations", "[list]") {
  GIVEN("An initial Tcl list") {
    tcl::Interp interp;
    tcl::List l;
    REQUIRE(l.size() == 0);

    WHEN("iterated over") {
      REQUIRE(std::distance(l.begin(), l.end()) == std::ptrdiff_t(0));
    }
    WHEN("reversily iterated over") {
      REQUIRE(std::distance(l.rbegin(), l.rend()) == std::ptrdiff_t(0));
    }

    WHEN("elements appended") {
      l.append("appended").append("elements");
      THEN("Size and string representation change") {
        CHECK(l.size() == 2);
        REQUIRE(l.getStringRep() == "appended elements");
      }

      WHEN("iterated over") {
        REQUIRE(std::distance(l.begin(), l.end()) == 2);
        auto it = l.begin();
        REQUIRE(it->getStringRep() == "appended");
        REQUIRE((++it)->getStringRep() == "elements");
      }
    }

    WHEN("other lists appended") {
      auto l2 = tcl::List().append("single_element");
      auto l3 = tcl::List().append("multiple").append("elements");
      l.append(l2).append(l3);
      THEN("Size and string representation change") {
        CHECK(l.size() == 2);
        REQUIRE(l.getStringRep() == "single_element {multiple elements}");
      }
      WHEN("iterated over (nested)") {
        REQUIRE(std::distance(l.begin(), l.end()) == 2);
        REQUIRE(l.begin()->getStringRep() == "single_element");
        auto l2 = std::next(l.begin())->as<tcl::List>();
        REQUIRE(l2.begin()->getStringRep() == "multiple");
        REQUIRE(std::prev(l2.end(), 2)->getStringRep() == "multiple");
        REQUIRE(std::next(l2.begin())->getStringRep() == "elements");
        REQUIRE(std::prev(l2.end())->getStringRep() == "elements");
      }
      WHEN("reversely iterated over (nested)") {
        REQUIRE(std::distance(l.rbegin(), l.rend()) == 2);
        REQUIRE(l.rbegin()->getStringRep() == "multiple elements");
        REQUIRE(std::next(l.rbegin())->getStringRep() == "single_element");
        auto l2 = l.rbegin()->as<tcl::List>();
        REQUIRE(l2.rbegin()->getStringRep() == "elements");
        REQUIRE(std::prev(l2.rend(), 2)->getStringRep() == "elements");
        REQUIRE(std::next(l2.rbegin())->getStringRep() == "multiple");
        REQUIRE(std::prev(l2.rend())->getStringRep() == "multiple");
      }
    }

    WHEN("spliced with other list") {
      auto other = tcl::List().append("underlying").append("elements");
      auto to_splice = tcl::List().append("several").append(other).append("inside");
      l.splice(to_splice);
      THEN("Size and string representation change") {
        CHECK(l.size() == 3);
        REQUIRE(l.getStringRep() == "several {underlying elements} inside");
      }

      WHEN("iterated over (nested)") {
        REQUIRE(std::distance(l.begin(), l.end()) == 3);
        REQUIRE(l.begin()->getStringRep() == "several");
        auto l2 = std::next(l.begin())->as<tcl::List>();
        REQUIRE(l2.begin()->getStringRep() == "underlying");
        REQUIRE(std::next(l2.begin())->getStringRep() == "elements");
        REQUIRE(std::next(l.begin(), 2)->getStringRep() == "inside");
      }
    }
  }
}
