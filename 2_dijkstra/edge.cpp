#include <iostream>
#include "edge.h"

template<typename T>
std::ostream& operator<< (std::ostream& out, Edge<T> edge)
{
  out << edge.a << " -> " << edge.b;
  return out;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, Edges<T> edges)
{
  out << " {";
  for (auto &edge : edges)
  {
    out << std::endl << "  " << edge << std::endl;
  }
  out << "}";
  return out;
}
