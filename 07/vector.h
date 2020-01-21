#include "allocator.h"
#include "iterator.h"

#include <stdexcept>

template <class T, class Alloc = Allocator<T>>
class Vector
{
private:
  using Size = unsigned long long;
  Alloc alloc_;
  T *begin_; // first element
  T *end_;   // after last element
  Size capacity_;

  class _Iterator : public Iterator<T>
  {
    friend class Vector;
  };

  class _ReverseIterator : public Iterator<T>
  {
    friend class Vector;

  public:
    T *operator++() { return Iterator<T>::operator--(); }
    T *operator--() { return Iterator<T>::operator++(); }
  };

public:
  using iterator = _Iterator;
  using reverse_iterator = _ReverseIterator;

  Vector(Size capacity = 0)
      : begin_(alloc_.allocate(capacity)),
        end_(begin_), capacity_(capacity)
  {
  }

  Vector(const Vector &other) : Vector(other.capacity_)
  {
    T *it = other.begin_;
    while (it != other.end_)
      *end_++ = *it++;
  }

  Size size() const { return end_ - begin_; }
  Size capacity() const { return capacity_; }
  bool empty() const { return size() == 0; }

  void reserve(Size n);
  void resize(Size n, const T &def = T(0));

  void push_back(const T &value);
  void pop_back();
  void clear();

  T &operator[](Size i) { return *(begin_ + i); }
  T &at(Size i);
};

template <class T, class Alloc>
T &Vector<T, Alloc>::at(Size i)
{
  if (i < size())
    return operator[](i);
  else
    throw std::out_of_range("index exceed size");
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(Size n)
{
  if (n < capacity_)
    return;

  T *data = alloc_.allocate(n);
  T *it = data;
  T *old = begin_;
  while (begin_ != end_)
    *it++ = *begin_++;
  begin_ = data;
  end_ = begin_ + (end_ - old);
  capacity_ = n;
  alloc_.deallocate(old, 0);
}

template <class T, class Alloc>
void Vector<T, Alloc>::resize(Size n, const T &def)
{
  reserve(n);
  if (n <= size())
  {
    end_ = begin_ + n;
  }
  else
  {
    while (end_ != begin_ + n)
      *end_++ = def;
  }
}

template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const T &value)
{
  if (end_ == begin_ + capacity_)
    reserve(2 * capacity_);

  *end_++ = value;
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back()
{
  if (end_ != begin_)
    --end_;
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear()
{
  end_ = begin_;
}