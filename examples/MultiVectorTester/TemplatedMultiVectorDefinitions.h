// ----------------------------------------------------------------------------
// TemplatedMultiVectorDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef TEMPLATED_MULTI_ARRAY_DEFINITIONS_H
#define TEMPLATED_MULTI_ARRAY_DEFINITIONS_H

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
TemplatedMultiVector<T,X_SIZE,Y_SIZE,Z_SIZE>::TemplatedMultiVector()
{
  x_.fill(constants::x_default);
  y_.fill(constants::y_default);
  z_.fill(constants::z_default);
  x2_.fill(9);
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
void TemplatedMultiVector<T,X_SIZE,Y_SIZE,Z_SIZE>::print()
{
  Serial << "x:" << endl;
  printVector(x_);

  Serial << "y:" << endl;
  printVector(y_);

  Serial << "z:" << endl;
  printVector(z_);

  Serial << "x2:" << endl;
  printVector(x2_);
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
template <unsigned int ARRAY_SIZE>
void TemplatedMultiVector<T,X_SIZE,Y_SIZE,Z_SIZE>::printVector(Vector<T,ARRAY_SIZE> array)
{
  Serial << "[";
  for (int i=0; i<ARRAY_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << array[i];
  }
  Serial << "]" << endl;
}

#endif
