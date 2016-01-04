// ----------------------------------------------------------------------------
// ServerDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SERVER_DEFINITIONS_H
#define SERVER_DEFINITIONS_H

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
Server<T,X_SIZE,Y_SIZE,Z_SIZE>::Server(HardwareSerial &serial)
{
  setSerial(serial);
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
void Server<T,X_SIZE,Y_SIZE,Z_SIZE>::setSerial(HardwareSerial &serial)
{
  serial_ptr_ = &serial;
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
void Server<T,X_SIZE,Y_SIZE,Z_SIZE>::print()
{
  *serial_ptr_ << "x:" << endl;
  printVector(x_);

  *serial_ptr_ << "y:" << endl;
  printVector(y_);

  *serial_ptr_ << "z:" << endl;
  printVector(z_);
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
template <typename E>
void Server<T,X_SIZE,Y_SIZE,Z_SIZE>::printRandomObject(const E &obj)
{
  *serial_ptr_ << obj << endl;
}

template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
template <unsigned int ARRAY_SIZE>
void Server<T,X_SIZE,Y_SIZE,Z_SIZE>::printVector(Vector<T,ARRAY_SIZE> array)
{
  *serial_ptr_ << "[";
  for (int i=0; i<ARRAY_SIZE; i++)
  {
    if (i != 0)
    {
      *serial_ptr_ << ",";
    }
    *serial_ptr_ << array[i];
  }
  *serial_ptr_ << "]" << endl;
}

#endif
