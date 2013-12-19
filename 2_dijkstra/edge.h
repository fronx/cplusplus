#ifndef __EDGE_H_INCLUDED__
#define __EDGE_H_INCLUDED__

template<typename T> class Node;

#include <vector>

template<typename T>
class Edge
{
public:
  Node<T> a, b;
};

template<typename T>
using Edges = std::vector<Edge<T>>;

template<typename T>
std::ostream& operator<< (std::ostream& out, Edge<T> edge);

template<typename T>
std::ostream& operator<< (std::ostream& out, Edges<T> edges);

#endif
