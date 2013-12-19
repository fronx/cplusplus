#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include <vector>

template<typename T>
class Node
{
public:
  Node(T _value) { value = _value; }
  T value;
};

template<typename T>
using Nodes = std::vector<Node<T>>;

template<typename T>
std::ostream& operator<< (std::ostream& out, Node<T> node);

#endif
