#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include <iostream>
#include "edge.h"
#include "node.h"

template<typename T>
class Graph
{
  Edges<T> _edges;
public:
  Nodes<T> nodes ();
  Edges<T> edges () { return _edges; };
};

template<typename T>
std::ostream& operator<< (std::ostream& out, Graph<T> graph);

#endif
