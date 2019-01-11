#pragma once

namespace jander {

// Bottom-up solution.

unsigned long fib(unsigned int n) {
  unsigned long fibs[n+1];
  fibs[0] = 0;
  fibs[1] = 1;
  fibs[2] = 1;

  for(unsigned int i=3; i<=n; i++)
    fibs[i] = fibs[i-1] + fibs[i-2];

  return fibs[n];
}


// Recursive (with memoization) solution.

unsigned long fib_recur(unsigned int n, unsigned long cache[] = nullptr) {
  if (cache == nullptr) {
    unsigned long array[n+1];
    for (unsigned int i=0; i<n; i++) array[i] = 0;
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
