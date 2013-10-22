#include <iostream>
#include <numeric>

template <typename T, std::size_t Size>
std::size_t arraysize(T (&)[Size]) { return Size; }

template <typename T>
T add (T &a, T &b) { return a + b; }

template <typename T>
T mul (T &a, T &b) { return a * b; }

template <typename T, std::size_t Size>
T sum (T (&a)[Size])
{
  return std::accumulate(a, a + Size, 0, add<T>);
}

template <typename T, std::size_t Size>
T prod (T (&a)[Size])
{
  return std::accumulate(a, a + Size, 1, mul<T>);
}

int main ()
{
  int a[] = { 1, 2, 3, 4 };
  std::cout << arraysize(a)             // 4
            << "\n" << mul(a[1], a[2])  // 6
            << "\n" << sum(a)           // 10
            << "\n" << prod(a)          // 24
            << "\n"
  ;
  return 0;
}
