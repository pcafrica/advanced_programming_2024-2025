#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

inline static constexpr size_t vec_size = 1000;

int lookup(const size_t &index) {
  // Generate an arbitrary dataset.
  auto data = std::vector<int>(vec_size);
  std::iota(data.begin(), data.end(), 0);

  return data[index];
}

int lookup_static(const size_t &index) {
  // Generate an arbitrary dataset.
  static auto data = std::vector<int>(vec_size);

  if (data.empty()) {
    std::iota(data.begin(), data.end(), 0);
  }

  return data[index];
}

int main(int argc, char **argv) {
  const size_t n_iterations = 1e7;

  std::default_random_engine engine(std::random_device{}());

  std::uniform_int_distribution<int> rand_int(0, vec_size - 1);
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n_iterations; ++i)
      lookup(rand_int(engine));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Lookup: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << " ms." << std::endl;
  }

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n_iterations; ++i)
      lookup_static(rand_int(engine));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Lookup (static): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << " ms." << std::endl;
  }

  return 0;
}
