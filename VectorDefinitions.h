// ----------------------------------------------------------------------------
// VectorDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef VECTOR_DEFINITIONS_H
#define VECTOR_DEFINITIONS_H

#ifndef ARDUINO
#include <cstring>
#endif

template <typename T>
Vector<T>::Vector()
{
  values_ptr_ = NULL;
  max_size_ = 0;
  size_ = 0;
}

template <typename T>
template <size_t MAX_SIZE>
Vector<T>::Vector(T (&values)[MAX_SIZE], size_t size)
{
  setStorage(values,size);
}

template <typename T>
template <size_t MAX_SIZE>
void Vector<T>::setStorage(T (&values)[MAX_SIZE], size_t size)
{
  values_ptr_ = values;
  max_size_ = MAX_SIZE;
  size_ = size;
}

template <typename T>
T& Vector<T>::operator[](const size_t i)
{
  return *(values_ptr_ + i);
}

template <typename T>
T& Vector<T>::at(const size_t i)
{
  return *(values_ptr_ + i);
}

template <typename T>
T& Vector<T>::front()
{
  return *(values_ptr_);
}

template <typename T>
T& Vector<T>::back()
{
  return *(values_ptr_ + (size_ - 1));
}

template <typename T>
void Vector<T>::clear()
{
  size_ = 0;
}

// template <typename T>
// void Vector<T>::fill(const T &value)
// {
//   assign(max_size_,value);
// }

// template <typename T>
// template <size_t MAX_SIZE>
// void Vector<T>::fill(const T (&values)[MAX_SIZE])
// {
//   assign(MAX_SIZE,values);
// }

// template <typename T>
// void Vector<T>::assign(const size_t n, const T &value)
// {
//   if (values_ptr_ != NULL)
//   {
//     size_t assign_size = n;
//     if ((n > size_) && (n <= max_size_))
//     {
//       size_ = n;
//     }
//     else if (n > max_size_)
//     {
//       size_ = max_size_;
//       assign_size = max_size_;
//     }
//     for (size_t i=0; i<assign_size; i++)
//     {
//       *(values_ptr_ + i) = value;
//     }
//   }
// }

// template <typename T>
// void Vector<T>::assign(const size_t n, const T values[])
// {
//   size_t assign_size = n;
//   if ((n > size_) && (n <= max_size_))
//   {
//     size_ = n;
//   }
//   else if (n > max_size_)
//   {
//     size_ = max_size_;
//     assign_size = max_size_;
//   }
//   memcpy((void*) (*values_ptr_), (void*) values, assign_size*sizeof(T));
// }

template <typename T>
void Vector<T>::push_back(const T &value)
{
  if ((values_ptr_ != NULL) && (size_ < max_size_))
  {
    *(values_ptr_ + size_++) = value;
  }
}

template <typename T>
void Vector<T>::pop_back()
{
  if (size_ > 0)
  {
    --size_;
  }
}

template <typename T>
size_t Vector<T>::size()
{
  return size_;
}

template <typename T>
size_t Vector<T>::max_size()
{
  return max_size_;
}

template <typename T>
bool Vector<T>::empty()
{
  return size_ == 0;
}

template <typename T>
bool Vector<T>::full()
{
  return size_ == max_size_;
}

#endif
