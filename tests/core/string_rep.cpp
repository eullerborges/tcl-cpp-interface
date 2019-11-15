#include "tcl++/core/Dict.h"
#include "tcl++/core/Interp.h"
#include "tcl++/core/List.h"
#include "tcl++/core/String.h"

#include <catch2/catch.hpp>

namespace {
std::shared_ptr<tcl::Object> toShared(tcl::Object&& obj) {
  return std::make_shared<tcl::Object>(std::move(obj));
}

auto getFirstValueGenerator() {
  return Catch::Generators::values(
      {toShared(tcl::String("first string")),
       toShared(std::move(tcl::List().append("first").append("list"))),
       toShared(std::move(tcl::Dict().put("first", tcl::List().append("test").append("dict"))))});
}

auto getSecondValueGenerator() {
  return Catch::Generators::values(
      {toShared(tcl::String("second string")),
       toShared(std::move(tcl::List().append("second").append("list"))),
       toShared(std::move(tcl::Dict().put("second", tcl::List().append("test").append("dict"))))});
}
}  // namespace

SCENARIO("Tcl object string reps after operations", "[object_string_rep]") {
  GIVEN("The initialization of a string") {
    tcl::Interp interp;

    WHEN("copy constructor") {
      auto other = GENERATE(getFirstValueGenerator());
      std::string otherRep = other->getStringRep();
      tcl::Object first{*other};
      THEN("String representation is equivalent") {
        CHECK(first.getStringRep() == otherRep);
        CHECK(other->getStringRep() == otherRep);
      }
    }

    WHEN("move constructor") {
      auto other = GENERATE(getFirstValueGenerator());
      std::string otherRep = other->getStringRep();
      tcl::Object first{std::move(*other)};
      THEN("String representation is equivalent") {
        CHECK(first.getStringRep() == otherRep);
        CHECK_THROWS_AS(other->getStringRep(), std::runtime_error);
      }
    }
  }

  GIVEN("Two initialized Tcl objects") {
    tcl::Interp interp;
    auto first = GENERATE(getFirstValueGenerator());
    std::string initialRep = first->getStringRep();

    auto other = GENERATE(getSecondValueGenerator());
    std::string otherRep = other->getStringRep();

    WHEN("copy assignment operator") {
      *first = *other;
      THEN("String representation changes") { CHECK(first->getStringRep() == otherRep); }
    }

    WHEN("move assignment operator") {
      *first = std::move(*other);
      THEN("String representation changes") {
        CHECK(first->getStringRep() == otherRep);
        CHECK(other->getStringRep() == initialRep);
      }
    }
  }
}
