#include "tcl++/core/List.h"
#include "tcl++/core/String.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch2/catch.hpp"

TEST_CASE("Factorials are computed", "[factorial]") {
  tcl::List l;
  tcl::List l2;
  l2.append(tcl::String("blupt")).append(tcl::String("blarg"));
  l.append(tcl::String("ble")).append(tcl::String("bla")).splice(l2);

  REQUIRE(l.getStringRep() == "ble bla blupt blarg");
}
