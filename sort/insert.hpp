#pragma once

#include <utility>
#include <vector>

namespace jander {

  // This version of Insert Sort is very simple. We have two arrays,
  // an unsorted array (our input) and a sorted array (which starts
  // empty). One by one, we grab a value from the unsorted array
  // and insert it into the sorted array at it's appropriate index.

  std::vector<int> insert_sort(const std::vector<int>& unsorted) {
    std::vector<int> sorted;

    for (int value : unsorted) {
      auto location = sorted.end();

      for (unsigned int i=0; i<sorted.size(); i++) {
        if (sorted[i] > value) {
          location = sorted.insert(sorted.begin()+i, value);
          break;
        }
      }

      if (location == sorted.end()) sorted.push_back(value);
    }

    return sorted;
  }


  // This version of Insert Sort is a bit more complex than the
  // one above because it sorts the array in-place. The input
  // array is split into two halves: a sorted half and an
  // unsorted half. These halves are denoted by the `boundary`
  // variable, which points to the first element of the
  // unsorted half. One by one, the boundary element is moved
  // into the sorted half at it's appropriate index. When this
  // occurs, all the elements in the sorted half that are
  // greater than the boundary element are moved up an index to
  // make room for the boundary element. The boundary is then
  // moved up an index. This continues until the entire array
  // is sorted.

  void insert_sort(int array[], unsigned int size) {
    using std::swap;
    unsigned int boundary = 1;

    while (boundary < size) {
      auto value = array[boundary];

      for (unsigned int i=0; i<boundary; i++)
        if (array[i] > value) swap(array[i], value);

      array[boundary] = value;

      boundary++;
    }
  }

};
