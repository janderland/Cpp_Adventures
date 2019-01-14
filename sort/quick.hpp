#pragma once

#include <utility>

namespace jander {

void quick_sort(int array[], size_t begin, size_t end) {
  if ((begin - end) < 2) return;

  size_t pivot_i = end-1;
  size_t swap_i = begin;

  for (size_t i=begin; i<end; i++)
    if (array[i] < array[pivot_i])
      std::swap(array[i], array[swap_i++]);

  std::swap(array[pivot_i], array[swap_i]);
  pivot_i = swap_i;

  quick_sort(array, begin, pivot_i);
  quick_sort(array, pivot_i+1, end);
}

} // namespace jander
