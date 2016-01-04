// ----------------------------------------------------------------------------
// MultiVector.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "MultiVector.h"

MultiVector::MultiVector()
{
  x_.fill(constants::x_default);
  y_.fill(constants::y_default);
  z_.fill(constants::z_default);
}

void MultiVector::print()
{
  Serial << "x:" << endl;
  Serial << "[";
  for (int i=0; i<constants::X_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << x_[i];
  }
  Serial << "]" << endl;

  Serial << "y:" << endl;
  Serial << "[";
  for (int i=0; i<constants::Y_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << y_[i];
  }
  Serial << "]" << endl;

  Serial << "z:" << endl;
  Serial << "[";
  for (int i=0; i<constants::Z_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << z_[i];
  }
  Serial << "]" << endl;
}
