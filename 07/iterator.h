template <class T>
class Iterator
{
private:
  T *p_;

protected:
  Iterator(T *p) : p_(p) {}

public:
  Iterator(const Iterator &other) : p_(other.p_) {}

  bool operator!=(const Iterator &other) const
  {
    return p_ != other.p_;
  }
  bool operator==(const Iterator &other) const
  {
    return p_ == other.p_;
  }
  T &operator*() const
  {
    return *p_;
  }
  Iterator &operator++()
  {
    ++p_;
    return *this;
  }
  Iterator &operator--()
  {
    --p_;
    return *this;
  }
};
