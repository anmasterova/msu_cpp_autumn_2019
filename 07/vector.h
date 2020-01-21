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

  template <class R>
  class _Iterator : public Iterator<R>
  {
    friend class Vector;
    _Iterator(T *p) : Iterator<R>(p) {}
  };

  template <class R>
  class _ReverseIterator : public Iterator<R>
  {
    friend class Vector;
    _ReverseIterator(T *p) : Iterator<R>(p) {}

  public:
    _ReverseIterator &operator++()
    {
      Iterator<R>::operator--();
      return *this;
    }
    _ReverseIterator &operator--()
    {
      Iterator<R>::operator++();
      return *this;
    }
  };

  void destruct(T *begin, T *end);

public:
  using iterator = _Iterator<T>;
  using const_iterator = _Iterator<const T>;
  using reverse_iterator = _ReverseIterator<T>;
  using const_reverse_iterator = _ReverseIterator<const T>;

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

  ~Vector()
  {
    if (begin_)
    {
      destruct(begin_, end_);
      alloc_.deallocate(begin_, 0);
    }
  }

  Size size() const { return end_ - begin_; }
  Size capacity() const { return capacity_; }
  bool empty() const { return size() == 0; }

  void reserve(Size n);
  void resize(Size n, const T &def = T());

  void push_back(const T &value);
  void pop_back();
  void clear();

  T &operator[](Size i) { return *(begin_ + i); }
  T &at(Size i);

  iterator begin() { return _Iterator<T>(begin_); }
  const_iterator cbegin() const { return _Iterator<const T>(begin_); }
  iterator end() { return _Iterator<T>(end_); }
  const_iterator cend() const { return _Iterator<const T>(end_); }

  reverse_iterator rbegin() { return _ReverseIterator<T>(end_ - 1); }
  const_reverse_iterator crbegin() const { return _ReverseIterator<const T>(end_ - 1); }
  reverse_iterator rend() { return _ReverseIterator<T>(begin_ - 1); }
  const_reverse_iterator crend() const { return _ReverseIterator<const T>(begin_ - 1); }
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
  destruct(old, end_);
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
    destruct(begin_ + n, end_);
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
    reserve((capacity_ == 0) ? 1 : 2 * capacity_);

  *end_++ = value;
}

template <class T, class Alloc>
void Vector<T, Alloc>::pop_back()
{
  if (end_ == begin_)
    return;
  T *old = end_--;
  destruct(end_, old);
}

template <class T, class Alloc>
void Vector<T, Alloc>::clear()
{
  destruct(begin_, end_);
  end_ = begin_;
}

template <class T, class Alloc>
void Vector<T, Alloc>::destruct(T *begin, T *end)
{

  while (begin != end)
    (begin++)->~T();
}