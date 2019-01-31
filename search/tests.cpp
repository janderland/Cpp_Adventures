#include "divide.hpp"
#include "catch/catch.hpp"
#include <algorithm>
#include <array>

TEST_CASE("Divide by Search (iterative)") {
  REQUIRE(jander::divide(52, 3) == (52/3));
}
