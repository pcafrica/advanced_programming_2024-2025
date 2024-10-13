#include "statistics.hpp"
#include <iostream>
#include <sstream>

int main() {
  std::cout << "Statistics calculator" << std::endl;

  while (true) {
    std::cout
        << "Enter a set of numbers separated by spaces (or 'q' to quit): ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "q" || input == "Q") {
      break;
    }

    // Split the input string into a vector of numbers.
    std::vector<double> numbers;
    std::istringstream iss(input);
    double num;
    while (iss >> num) {
      numbers.push_back(num);
    }

    if (numbers.empty()) {
      std::cout << "Invalid input. Please enter numbers." << std::endl;
      continue;
    }

    // Calculate and display statistics.
    const double mean = stat::calculate_mean(numbers);
    const double median = stat::calculate_median(numbers);
    const double stddev = stat::calculate_standard_deviation(numbers);

    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Median: " << median << std::endl;
    std::cout << "Standard deviation: " << stddev << std::endl;
  }

  return 0;
}
