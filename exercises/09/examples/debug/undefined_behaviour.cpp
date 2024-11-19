#include <iostream>
#include <limits>

int main(int argc, char **argv) {
  for (int i = 1; i <= 10; ++i) {
    // Try to remove parentheses from the following line.
    const double y = i + (std::numeric_limits<int>::max() / 1.0e10);

    std::cout << y << std::endl;
  }

  return 0;
}
