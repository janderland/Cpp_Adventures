#include "insert.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "catch/catch.hpp"
#include <algorithm>
#include <array>

const std::vector<int> unsorted = {9,1,6,3,6,5,8,0,12,3,2};
const std::vector<int> sorted = {0,1,2,3,3,5,6,6,8,9,12};
const unsigned int size = unsorted.size();

TEST_CASE("Insert Sort (vector)") {
  REQUIRE(jander::insert_sort(unsorted) == sorted);
}

TEST_CASE("Insert Sort (in-place)") {
  int unsorted_arr[size];
  std::copy(unsorted.begin(), unsorted.end(), unsorted_arr);

  jander::insert_sort(unsorted_arr, size);

  std::vector<int> output(unsorted_arr, unsorted_arr+size);
  REQUIRE(output == sorted);
}

TEST_CASE("Merge Sort") {
  REQUIRE(jander::merge_sort(unsorted) == sorted);
}

TEST_CASE("Quick Sort") {
  int unsorted_arr[size];
  std::copy(unsorted.begin(), unsorted.end(), unsorted_arr);

  jander::quick_sort(unsorted_arr, 0, size);

  std::vector<int> output(unsorted_arr, unsorted_arr+size);
  REQUIRE(output == sorted);
}
