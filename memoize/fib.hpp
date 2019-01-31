#pragma once

#include <algorithm>
#include <functional>

namespace jander {

// Bottom-up solution.

long fib(int n) {
  long fibs[n+1];
  fibs[0] = 0;
  fibs[1] = 1;
  fibs[2] = 1;

  for(int i=3; i<=n; i++)
    fibs[i] = fibs[i-1] + fibs[i-2];

  return fibs[n];
}


// Recursive (with memoization) solution.

long fib_recur(int n, long cache[]) {
  auto recur = [&](auto num) {
    return !cache[num]
      ? cache[num] = fib_recur(num, cache)
      : cache[num];
  };

  if (n == 0) return 0;
  if (n <= 2) return 1;
  return recur(n-1) + recur(n-2);
}

long fib_recur(int n) {
  long array[n+1];
  std::fill(array, array+n+1, 0);
  return fib_recur(n, array);
}

} // namespace jander
