#include <new>

template <class T>
class Allocator
{
  using Size = unsigned long long;

public:
  T *allocate(Size n)
  {
    void *ptr_ = 0;

    if (n == 0)
      ;
    else if (((Size)(-1) / sizeof(T) < n) || (ptr_ = ::operator new(n * sizeof(T))) == 0)
    {
      throw std::bad_alloc();
    }
    return ((T *)ptr_);
  }

  void deallocate(T *ptr, Size) { ::operator delete(ptr); }
};
 
