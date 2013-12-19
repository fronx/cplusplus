#include <iostream>
#include "node.h"

template<typename T>
std::ostream& operator<< (std::ostream& out, Node<T> node)
{
  return out << "(" << node.value << ")";
}
