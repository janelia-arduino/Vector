// ----------------------------------------------------------------------------
// Vector.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef VECTOR_H
#define VECTOR_H
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstddef>
#endif


template <typename T>
class Vector
{
public:
  Vector();
  template <size_t MAX_SIZE>
  Vector(T (&values)[MAX_SIZE], size_t size=0);
  template <size_t MAX_SIZE>
  void setStorage(T (&values)[MAX_SIZE], size_t size=0);
  void setStorage(T * values, size_t max_size, size_t size);
  T & operator[](const size_t index);
  T & at(const size_t index);
  T & front();
  T & back();
  void clear();
  template <typename U>
  void fill(const U & value);
  template <typename U, size_t N>
  void fill(const U (&values)[N]);
  template <typename U>
  void fill(Vector<U> & values);
  template <typename U>
  void assign(const size_t n, const U & value);
  template <typename U, size_t N>
  void assign(const size_t n, const U (&values)[N]);
  template <typename U>
  void assign(const size_t n, Vector<U> & values);
  void push_back(const T & value);
  void pop_back();
  void remove(const size_t index);
  size_t size() const;
  size_t max_size() const;
  bool empty() const;
  bool full() const;
  T * data();

private:
  T * values_;
  size_t max_size_;
  size_t size_;
};

template <typename T>
inline Print & operator <<(Print & stream, Vector<T> & vector)
{
  stream.print("[");
  for (size_t i=0; i<vector.size(); ++i)
  {
    if (i != 0)
    {
      stream.print(",");
    }
    stream.print(vector[i]);
  }
  stream.print("]");
  return stream;
}

#include "Vector/VectorDefinitions.h"

#endif
