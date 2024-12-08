#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>

// ----------------
// Regular C++ code
// ----------------

std::vector<int> multiply(const std::vector<double> &input) {
  std::vector<int> output(input.size());

  for (size_t i = 0; i < input.size(); ++i)
    output[i] = 10 * static_cast<int>(input[i]);

  return output;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

// Wrap C++ function with NumPy array IO.
// C-style means row-major (vs. F(ortran)-style, column-major).
py::array_t<int>
py_multiply(const py::array_t<double, py::array::c_style | py::array::forcecast>
                &array) {
  // Allocate std::vector (to pass to the C++ function).
  std::vector<double> vector(array.size());

  // Copy py::array -> std::vector.
  std::memcpy(vector.data(), array.data(), array.size() * sizeof(double));

  // Call pure C++ function.
  std::vector<int> result_vec = multiply(vector);

  // Allocate py::array (to pass the result of the C++ function to Python).
  auto result = py::array_t<int>(array.size());
  auto result_buffer = result.request();
  int *result_ptr = (int *)result_buffer.ptr;

  // Copy std::vector -> py::array.
  std::memcpy(result_ptr, result_vec.data(), result_vec.size() * sizeof(int));

  return result;
}

// Wrap as Python module.
PYBIND11_MODULE(example, m) {
  m.doc() = "pybind11 example plugin";

  m.def("multiply", &py_multiply,
        "Convert all entries of an 1-D NumPy-array to int and multiply by 10");
}
