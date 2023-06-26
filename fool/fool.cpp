#include "fmt/format.h"

auto f(auto x) { return static_cast<double>(x); }

int main() {

  auto x = f(3);

  fmt::println("x:{}", x);

  return 0;
}