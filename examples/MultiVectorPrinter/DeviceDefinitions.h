// ----------------------------------------------------------------------------
// DeviceDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef DEVICE_DEFINITIONS_H
#define DEVICE_DEFINITIONS_H


template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
Device<T,X_SIZE,Y_SIZE,Z_SIZE>::Device()
{
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
void Device<T,X_SIZE,Y_SIZE,Z_SIZE>::print()
{
  server_.print();
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
template<typename E>
void Device<T,X_SIZE,Y_SIZE,Z_SIZE>::printRandomObject(const E &obj)
{
  server_.printRandomObject(obj);
}

#endif
