#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

template<typename T>
class Node
{
public:
  T value;
};

template<typename T>
class Edge
{
public:
  Node<T> a, b;
};

template<typename T>
using Nodes = std::vector<Node<T>>;
template<typename T>
using Edges = std::vector<Edge<T>>;

template<typename T>
class Graph
{
  Edges<T> _edges;
public:
  Nodes<T> nodes ();
  Edges<T> edges () { return _edges; };
};

template<typename T>
Nodes<T> Graph<T>::nodes ()
{
  std::vector<T> v;
  return v;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, Edge<T> edge)
{
  out << edge.a.value << " -> " << edge.b.value;
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

template<typename T>
std::ostream& operator<< (std::ostream& out, Graph<T> graph)
{
  out << "[Graph" << graph.edges() << "]";
  return out;
}

int main (void)
{
  Graph<int> graph;
  std::cout << graph;
}
