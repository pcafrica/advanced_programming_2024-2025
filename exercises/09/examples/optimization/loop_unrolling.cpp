#include <chrono>
#include <iostream>
#include <vector>

inline static constexpr size_t vec_size = 1000;

int multiply(const std::vector<int> &data) {
  int result = 1;

  for (const auto &v : data)
    result *= v;

  return result;
}

int multiply_with_unrolling(const std::vector<int> &data) {
  int result = 1;

  int a0, a1, a2, a3, a4;

  for (size_t i = 0; i < data.size() - 4; i += 5) {
    a0 = data[i];
    a1 = data[i + 1];
    a2 = data[i + 2];
    a3 = data[i + 3];
    a4 = data[i + 4];

    result *= a0 * a1 * a2 * a3 * a4;
  }

  return result;
}

using timer = std::chrono::high_resolution_clock;

int main(int argc, char **argv) {
  const size_t n_iterations = 1e7;

  // Generate an arbitrary dataset.
  auto data = std::vector<int>(vec_size, 1);

  double result;

  {
    auto start = timer::now();
    for (size_t i = 0; i < n_iterations; ++i)
      result = multiply(data);
    auto end = timer::now();

    std::cout << "Multiply: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << " ms, result: " << result << "." << std::endl;
  }

  {
    auto start = timer::now();
    for (size_t i = 0; i < n_iterations; ++i)
      result = multiply_with_unrolling(data);
    auto end = timer::now();

    std::cout << "Multiply (with unrolling): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << " ms, result: " << result << "." << std::endl;
  }

  return 0;
}
