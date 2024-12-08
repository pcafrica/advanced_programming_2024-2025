#include "matrix.hpp"
#include "pybind_matrix.hpp"

// ----------------
// Regular C++ code
// ----------------

Matrix<double> multiply(const Matrix<double> &A, const Matrix<double> &B) {
  if (A.shape() != B.shape())
    throw std::length_error("Matrix 'A' and 'B' are inconsistent");

  Matrix<double> ret(A.shape());

  for (int i = 0; i < A.size(); i++)
    ret[i] = A[i] * B[i];

  return ret;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example, m) {
  m.doc() = "pybind11 example plugin";

  m.def("multiply", &multiply);
}
