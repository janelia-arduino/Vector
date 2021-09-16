// ----------------------------------------------------------------------------
// VectorIterator.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H

template<typename T>
class VectorIterator
{
public:
  VectorIterator(T * values_ptr) : values_ptr_{values_ptr}, position_{0} {}

  VectorIterator(T * values_ptr, size_t size) : values_ptr_{values_ptr}, position_{size} {}

  bool operator!=(const VectorIterator<T> & other) const
  {
    return !(*this == other);
  }

  bool operator==(const VectorIterator<T> & other) const
  {
    return position_ == other.position_;
  }

  VectorIterator & operator++()
  {
    ++position_;
    return *this;
  }

  T & operator*() const
  {
    return *(values_ptr_ + position_);
  }

private:
  T * values_ptr_;
  size_t position_;
};

#endif
