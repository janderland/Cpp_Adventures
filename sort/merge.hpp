#pragma once

#include <algorithm>
#include <vector>

namespace jander {

std::vector<int> merge_sort(const std::vector<int>& unsorted) {
  if (unsorted.size() < 2) return unsorted;

  const std::vector<int>
    unsorted1(unsorted.begin(), unsorted.begin() + unsorted.size()/2),
    unsorted2(unsorted.begin() + unsorted.size()/2, unsorted.end());

  const auto sorted1 = merge_sort(unsorted1);
  const auto sorted2 = merge_sort(unsorted2);
  std::vector<int> sorted;

  auto iter1 = sorted1.begin();
  auto iter2 = sorted2.begin();

  while(iter1 != sorted1.end() && iter2 != sorted2.end())
    if (*iter1 < *iter2) sorted.push_back(*iter1++);
    else sorted.push_back(*iter2++);

  while (iter1 != sorted1.end())
    sorted.push_back(*iter1++);

  while (iter2 != sorted2.end())
    sorted.push_back(*iter2++);

  return sorted;
}

} // namespace jander
