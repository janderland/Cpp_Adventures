#include "prettyprint.hpp"
#include "catch/catch.hpp"
#include <algorithm>
#include <array>

std::vector<std::vector<int>> vector3 = {
  {3, 3, 3, 3, 3},
  {3, 2, 2, 2, 3},
  {3, 2, 1, 2, 3},
  {3, 2, 2, 2, 3},
  {3, 3, 3, 3, 3},
};

std::vector<std::vector<int>> vector4 = {
  {4, 4, 4, 4, 4, 4, 4},
  {4, 3, 3, 3, 3, 3, 4},
  {4, 3, 2, 2, 2, 3, 4},
  {4, 3, 2, 1, 2, 3, 4},
  {4, 3, 2, 2, 2, 3, 4},
  {4, 3, 3, 3, 3, 3, 4},
  {4, 4, 4, 4, 4, 4, 4},
};

TEST_CASE("Pretty print (simple)") {
  REQUIRE(jander::prettyprint_simple(3) == vector3);
  REQUIRE(jander::prettyprint_simple(4) == vector4);
}

TEST_CASE("Pretty print (parameterized)") {
  REQUIRE(jander::prettyprint_param(3) == vector3);
  REQUIRE(jander::prettyprint_param(4) == vector4);
}
