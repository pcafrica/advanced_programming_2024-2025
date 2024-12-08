#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdlib>
#include <iostream>
#include <vector>

template <class T> class Matrix {
public:
  // Default constructor.
  Matrix<T>(){};

  // Constructor.
  Matrix<T>(const std::vector<size_t> &shape, const T *data = NULL) {
    if (shape.size() < 1 || shape.size() > 3)
      throw std::runtime_error("Input should be 1-D, 2-D, or 3-D");

    // store 'm_strides' and 'm_shape' always in 3-D,
    // use unit-length for "extra" dimensions (> 'shape.size()')
    while (m_shape.size() < 3) {
      m_shape.push_back(1);
    }
    while (m_strides.size() < 3) {
      m_strides.push_back(1);
    }

    for (int i = 0; i < shape.size(); i++)
      m_shape[i] = shape[i];

    m_strides[0] = m_shape[2] * m_shape[1];
    m_strides[1] = m_shape[2];
    m_strides[2] = 1;

    int size = m_shape[0] * m_shape[1] * m_shape[2];

    for (int i = 0; i < m_data.size(); i++)
      m_data[i] = static_cast<T>(0);

    while (m_data.size() < size)
      m_data.push_back(static_cast<T>(0));

    if (data != NULL)
      for (int i = 0; i < size; i++)
        m_data[i] = data[i];
  };

  // Copy constructor.
  Matrix(const Matrix<T> &) = default;
  Matrix<T> &operator=(const Matrix<T> &) = default;

  // Access operators.
  T &operator[](size_t i) { return m_data[i]; };
  const T &operator[](size_t i) const { return m_data[i]; };

  T &operator()(size_t h, size_t i = 0, size_t j = 0) {
    return m_data[h * m_strides[0] + i * m_strides[1] + j * m_strides[2]];
  };

  const T &operator()(size_t h, size_t i = 0, size_t j = 0) const {
    return m_data[h * m_strides[0] + i * m_strides[1] + j * m_strides[2]];
  };

  // Iterators.
  auto begin() { return m_data.begin(); }
  auto begin() const { return m_data.begin(); }
  auto end() { return m_data.end(); }
  auto end() const { return m_data.end(); }

  // Return pointer to data.
  const T *data(void) const { return m_data.data(); };

  // Return shape array.
  std::vector<size_t> shape(size_t ndim = 0) const {
    if (ndim == 0)
      ndim = this->ndim();

    std::vector<size_t> ret(ndim);

    for (size_t i = 0; i < ndim; ++i)
      ret[i] = m_shape[i];

    return ret;
  };

  // Return strides array.
  std::vector<size_t> strides(bool bytes = false) const {
    size_t ndim = this->ndim();
    std::vector<size_t> ret(ndim);

    for (size_t i = 0; i < ndim; ++i)
      ret[i] = m_strides[i];

    if (bytes)
      for (size_t i = 0; i < ndim; ++i)
        ret[i] *= sizeof(T);

    return ret;
  };

  // Return size.
  size_t size(void) const { return m_data.size(); };

  // Return number of dimensions.
  size_t ndim(void) const {
    size_t i;

    for (i = 2; i > 0; --i)
      if (m_shape[i] != 1)
        break;

    return i + 1;
  };

private:
  std::vector<T> m_data;         // Data array.
  std::vector<size_t> m_shape;   // Number of entries in each dimensions.
  std::vector<size_t> m_strides; // Stride length for each index.

}; // class Matrix

#endif /* MATRIX_HPP */
