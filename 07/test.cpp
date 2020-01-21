#include "vector.h"

#include <iostream>

int main()
{
  Vector<int> v(3);
  v.resize(10, 4);
  for (int i = 0; i < 10; ++i)
    std::cout << v[i] << " ";
  std::cout << std::endl;

  Vector<int> other(v);
  for (int i = 0; i < 10; ++i)
    std::cout << other.at(i) << " ";
  std::cout << std::endl;
}