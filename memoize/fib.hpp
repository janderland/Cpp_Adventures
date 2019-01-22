#pragma once

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

long fib_recur(int n, long cache[] = nullptr) {
  if (cache == nullptr) {
    long array[n+1];
    for (int i=0; i<n; i++) array[i] = 0;
    return fib_recur(n, array);
  }

  auto recur = [&](auto num) {
    return !cache[num]
      ? cache[num] = fib_recur(num, cache)
      : cache[num];
  };

  if (n == 0) return 0;
  else if (n <= 2) return 1;
  else return recur(n-1) + recur(n-2);
}

} // namespace jander
