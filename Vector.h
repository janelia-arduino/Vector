// ----------------------------------------------------------------------------
// Vector.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef VECTOR_H
#define VECTOR_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


template <typename T>
class Vector
{
public:
  Vector();
  template <size_t MAX_SIZE>
  Vector(T (&values)[MAX_SIZE], size_t size=0);
  template <size_t MAX_SIZE>
  void setStorageArray(T (&values)[MAX_SIZE], size_t size=0);
  T& operator[](const size_t i);
  T& at(const size_t i);
  T& front();
  T& back();
  void clear();
  // void fill(const T &value);
  // template <size_t MAX_SIZE>
  // void fill(const T (&values)[MAX_SIZE]);
  // void assign(const size_t n, const T &value);
  // void assign(const size_t n, const T values[]);
  void push_back(const T &value);
  void pop_back();
  size_t size();
  size_t max_size();
  bool empty();
  bool full();

private:
  T* values_ptr_;
  size_t max_size_;
  size_t size_;
};
#include "VectorDefinitions.h"

#endif
