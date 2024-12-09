#include "data_processor.hpp"
#include <cmath>
#include <sstream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

unsigned int DataProcessor::n_instances = 0;

DataProcessor::DataProcessor(const double *input_data,
                             const unsigned int &input_size)
    : size(input_size), data(new double[size]) {
  ++n_instances;

  for (unsigned int i = 0; i < size; ++i) {
    data[i] = input_data[i];
  }
}

DataProcessor::DataProcessor(const DataProcessor &other)
    : size(other.size), data(new double[size]) {
  ++n_instances;

  for (unsigned int i = 0; i < size; ++i) {
    data[i] = other[i];
  }
}

DataProcessor &DataProcessor::operator=(const DataProcessor &other) {
  if (this != &other) {
    delete[] data;
    size = other.size;
    data = new double[size];

    for (unsigned int i = 0; i < size; ++i) {
      data[i] = other[i];
    }
  }
  return *this;
}

DataProcessor DataProcessor::operator+(const DataProcessor &other) const {
  assert(size == other.size); // Check if sizes match.

  DataProcessor result(data, size); // Copy the current object.

  for (unsigned int i = 0; i < size; ++i) {
    result[i] += other[i];
  }

  return result;
}

double DataProcessor::compute_std_dev() const {
  const double mean = compute_mean();

  double sum_squared_diff = 0.0;
  for (unsigned int i = 0; i < size; ++i) {
    sum_squared_diff += (data[i] - mean) * (data[i] - mean);
  }

  return std::sqrt(sum_squared_diff / size);
}

std::ostream &operator<<(std::ostream &os, const DataProcessor &dp) {
  for (unsigned int i = 0; i < dp.size; ++i) {
    os << dp[i];
    if (i < dp.size - 1) {
      os << ", ";
    }
  }
  return os;
}

double compute_correlation(const DataProcessor &dp1, const DataProcessor &dp2) {
  assert(dp1.n_elements() == dp2.n_elements()); // Check if sizes match.

  const unsigned int n = dp1.n_elements();

  // Calculate the means of both datasets.
  const double mean1 = dp1.compute_mean();
  const double mean2 = dp2.compute_mean();

  // Calculate the sums of the cross-products of differences.
  double sum_cross_products = 0.0;
  double sum_diff1_squared = 0.0;
  double sum_diff2_squared = 0.0;

  for (unsigned int i = 0; i < n; ++i) {
    const double diff1 = dp1[i] - mean1;
    const double diff2 = dp2[i] - mean2;
    sum_cross_products += diff1 * diff2;
    sum_diff1_squared += diff1 * diff1;
    sum_diff2_squared += diff2 * diff2;
  }

  // Calculate the Pearson correlation coefficient.
  const double correlation =
      sum_cross_products /
      (std::sqrt(sum_diff1_squared) * std::sqrt(sum_diff2_squared));

  return correlation;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(data_processor, m) {
  m.doc() = "pybind11 example plugin";

  py::class_<DataProcessor>(m, "DataProcessor")
      .def(py::init([](const std::vector<double> &a) {
        return new DataProcessor(a.data(), a.size());
      }))
      .def("__add__", &DataProcessor::operator+)
      .def("n_elements", &DataProcessor::n_elements)
      .def("min", &DataProcessor::min)
      .def("max", &DataProcessor::max)
      .def("compute_mean", &DataProcessor::compute_mean)
      .def("compute_std_dev", &DataProcessor::compute_std_dev)
      .def_static("get_n_instances", &DataProcessor::get_n_instances)
      .def("__getitem__",
           (const double &(DataProcessor::*)(const unsigned int &) const) &
               DataProcessor::operator[])
      .def("__setitem__", [](DataProcessor &dp, unsigned int index,
                             double value) { dp[index] = value; })
      .def("__repr__", [](const DataProcessor &dp) {
        std::ostringstream ss;
        ss << dp;
        return ss.str();
      });

  m.def("compute_correlation", &compute_correlation);
}
