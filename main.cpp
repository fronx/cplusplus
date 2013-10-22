#include <cstddef>
#include <iostream>
#include <numeric>

template <typename T, std::size_t Size>
std::size_t arraysize(T (&)[Size]) { return Size; }

template <typename T>
T add (T &a, T &b)
{
  return a + b;
}

template <typename T>
T mul (T &a, T &b)
{
  return a * b;
}

template <typename T>
T sum (T a[])
{
  return accumulate(a, a + arraysize<T>(a), 0, add<T>);
}

template <typename T>
T prod (T a[])
{
  return accumulate(a, a + arraysize<T>(a), 1, mul<T>);
}

int main ()
{
  int a[] = { 1, 2, 3, 4 };
  std::cout << arraysize(a); // works
  // std::cout << sum(a) << "\n" << prod(a); // doesn't work
  return 0;
}
