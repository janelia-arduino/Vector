// ----------------------------------------------------------------------------
// Device.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef DEVICE_H
#define DEVICE_H
#include "Server.h"


enum{RESERVED_X_COUNT=0};
enum{RESERVED_Y_COUNT=1};
enum{RESERVED_Z_COUNT=3};

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
class Device
{
public:
  Device();
  static void print();
  template<typename E>
  static void printRandomObject(const E &obj);
private:
  static Server<T,
                X_SIZE+RESERVED_X_COUNT,
                Y_SIZE+RESERVED_Y_COUNT,
                Z_SIZE+RESERVED_Z_COUNT> server_;
};

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
Server<T,
       X_SIZE+RESERVED_X_COUNT,
       Y_SIZE+RESERVED_Y_COUNT,
       Z_SIZE+RESERVED_Z_COUNT> Device<T,X_SIZE,Y_SIZE,Z_SIZE>::server_;

#include "DeviceDefinitions.h"

#endif
