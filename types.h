#ifndef TYPES_H
#define TYPES_H
#include "andres/graph/graph.hxx"
#include "andres/graph/digraph.hxx"

//Graph typedefs
typedef andres::graph::Graph<>   graph;
typedef andres::graph::Digraph<> digraph;

//Generic type (not a graph) of 2D integers
typedef std::vector<std::vector<int>> vvint;

#endif