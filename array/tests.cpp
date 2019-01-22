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

TEST_CASE("Pretty print") {
  REQUIRE(jander::prettyprint(3) == vector3);
  REQUIRE(jander::prettyprint(4) == vector4);
}
