namespace jander {


int divide(int lower, int upper, int num, int denom) {
  auto quotient = (lower + upper) >> 1;
  auto num_ = quotient * denom;

  if (num_ < num)
    return divide(quotient + 1, upper, num, denom);
  else if (num_ > num)
    return divide(lower, quotient - 1, num, denom);
  else
    return quotient;
}

int divide(int num, int denom) {
  return divide(0, num, num-(num%denom), denom);
}

} // namespace jander
