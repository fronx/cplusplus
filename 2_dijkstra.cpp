#include <iostream>

#include "2_dijkstra/tree.h"
#include "2_dijkstra/node.h"

int main (void)
{
  Graph<int> graph;
  Node<int> n = Node<int>(3);
  std::cout      << "node:  " << n
    << std::endl << "graph: " << graph
    << std::endl
    ;
}

// premake4 gmake && make Dijkstra
