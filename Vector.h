// ----------------------------------------------------------------------------
// Vector.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef ARRAY_H
#define ARRAY_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
// #define __ASSERT_USE_STDERR
// #include <assert.h>


// // handle diagnostic informations given by assertion and abort program execution:
// void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp);

template <typename T, unsigned int max_size_>
class Vector
{
public:
  Vector();
  Vector(const T &value);
  Vector(const T (&values)[max_size_]);
  T& operator[](const unsigned int i);
  T& at(const unsigned int i);
  T& front();
  T& back();
  void clear();
  void fill(const T &value);
  void fill(const T (&values)[max_size_]);
  void assign(const unsigned int n, const T &value);
  void assign(const unsigned int n, const T values[]);
  void push_back(const T &value);
  void pop_back();
  unsigned int size();
  unsigned int max_size();
  bool empty();
  bool full();

private:
  T values_[max_size_];
  unsigned int size_;
};
#include "VectorDefinitions.h"

#endif
