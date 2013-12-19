#include <iostream>
#include <vector>
#include "tree.h"

template<typename T>
Nodes<T> Graph<T>::nodes ()
{
  std::vector<T> v;
  return v;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, Graph<T> graph)
{
  out << "[Graph" << graph.edges() << "]";
  return out;
}
