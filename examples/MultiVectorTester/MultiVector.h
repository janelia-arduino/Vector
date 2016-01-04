// ----------------------------------------------------------------------------
// MultiVector.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H
#include "Arduino.h"
#include "Streaming.h"
#include "Vector.h"
#include "Constants.h"

class MultiVector
{
public:
  MultiVector();
  void print();
private:
  Vector<int, constants::X_SIZE> x_;
  Vector<int, constants::Y_SIZE> y_;
  Vector<int, constants::Z_SIZE> z_;
};

#endif
