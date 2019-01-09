#include "insert.hpp"
#include "catch/catch.hpp"

TEST_CASE("Insert Sort (vector implementation)") {
  std::vector<int> unsorted = {1,6,3,6,5};
  std::vector<int> sorted = {1,3,5,6,6};

  REQUIRE(jander::insert_sort(unsorted) == sorted);
}

TEST_CASE("Insert Sort (in-place implementation)") {
  const unsigned int size = 5;
  int unsorted[size] = {1,6,3,6,5};
  std::vector<int> sorted = {1,3,5,6,6};

  jander::insert_sort(unsorted, size);

  std::vector<int> output(unsorted, unsorted+size);
  REQUIRE(output == sorted);
}
