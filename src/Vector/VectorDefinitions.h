// ----------------------------------------------------------------------------
// VectorDefinitions.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef VECTOR_DEFINITIONS_H
#define VECTOR_DEFINITIONS_H

#ifndef ARDUINO
#include <cstring>
#endif

template <typename T>
Vector<T>::Vector()
{
  values_ = NULL;
  max_size_ = 0;
  size_ = 0;
}

template <typename T>
template <size_t MAX_SIZE>
Vector<T>::Vector(T (&values)[MAX_SIZE],
  size_t size)
{
  setStorage(values,size);
}

template <typename T>
template <size_t MAX_SIZE>
void Vector<T>::setStorage(T (&values)[MAX_SIZE],
  size_t size)
{
  values_ = values;
  max_size_ = MAX_SIZE;
  size_ = size;
}

template <typename T>
void Vector<T>::setStorage(T * values,
  size_t max_size,
  size_t size)
{
  values_ = values;
  max_size_ = max_size;
  size_ = size;
}

template <typename T>
const T & Vector<T>::operator[](size_t index) const
{
  return values_[index];
}

template <typename T>
T & Vector<T>::operator[](size_t index)
{
  return values_[index];
}

template <typename T>
T & Vector<T>::at(size_t index)
{
  return values_[index];
}

template <typename T>
const T & Vector<T>::at(size_t index) const
{
  return values_[index];
}

template <typename T>
T & Vector<T>::front()
{
  return values_[0];
}

template <typename T>
T & Vector<T>::back()
{
  return values_[size_-1];
}

template <typename T>
void Vector<T>::clear()
{
  size_ = 0;
}

template <typename T>
template <typename U>
void Vector<T>::fill(const U & value)
{
  assign(max_size_,value);
}

template <typename T>
template <typename U,
  size_t N>
void Vector<T>::fill(const U (&values)[N])
{
  assign(N,values);
}

template <typename T>
template <typename U>
void Vector<T>::fill(const Vector<U> & values)
{
  assign(values.size(),values);
}

template <typename T>
template <typename U>
void Vector<T>::assign(size_t n,
  const U & value)
{
  size_t assign_size = ((n < max_size_) ? n : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = value;
  }
}

template <typename T>
template <typename U,
  size_t N>
void Vector<T>::assign(size_t n,
  const U (&values)[N])
{
  size_t n_smallest = ((n < N) ? n : N);
  size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = values[i];
  }
}

template <typename T>
template <typename U>
void Vector<T>::assign(size_t n,
  const Vector<U> & values)
{
  size_t n_smallest = ((n < values.size()) ? n : values.size());
  size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = values[i];
  }
}

template <typename T>
void Vector<T>::push_back(const T & value)
{
  if ((values_ != NULL) && (size_ < max_size_))
  {
    values_[size_++] = value;
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
void Vector<T>::remove(size_t index)
{
  if (size_ > index)
  {
    for (size_t i=index; i<(size_-1); ++i)
    {
      values_[i] = values_[i+1];
    }
    --size_;
  }
}

template <typename T>
size_t Vector<T>::size() const
{
  return size_;
}

template <typename T>
size_t Vector<T>::max_size() const
{
  return max_size_;
}

template <typename T>
bool Vector<T>::empty() const
{
  return size_ == 0;
}

template <typename T>
bool Vector<T>::full() const
{
  return size_ == max_size_;
}

template <typename T>
T * Vector<T>::data()
{
  return values_;
}

template <typename T>
const T * Vector<T>::data() const
{
  return values_;
}

#endif
