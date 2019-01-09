#include "fib.hpp"
#include "catch/catch.hpp"

TEST_CASE("Bottom-up implementation.") {
  REQUIRE(jander::fib(10) == 55);
  REQUIRE(jander::fib(56) == 225851433717);
}

TEST_CASE("Recursive implementation.") {
  REQUIRE(jander::fib_recur(10) == 55);
  REQUIRE(jander::fib_recur(56) == 225851433717);
}
