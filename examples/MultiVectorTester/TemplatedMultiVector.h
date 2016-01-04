// ----------------------------------------------------------------------------
// TemplatedMultiVector.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef TEMPLATED_MULTI_ARRAY_H
#define TEMPLATED_MULTI_ARRAY_H
#include "Arduino.h"
#include "Streaming.h"
#include "Vector.h"


template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
class TemplatedMultiVector
{
public:
  TemplatedMultiVector();
  void print();
private:
  Vector<T, X_SIZE> x_;
  Vector<T, Y_SIZE> y_;
  Vector<T, Z_SIZE> z_;
  Vector<T, X_SIZE+1> x2_;
  template <unsigned int ARRAY_SIZE>
  void printVector(Vector<T,ARRAY_SIZE> array);
};
#include "TemplatedMultiVectorDefinitions.h"

#endif
