#ifndef TYPES_H
#define TYPES_H
#include <vector>

//Graphs are adjacency matricies
typedef std::vector<std::vector<int>> graph;
typedef graph digraph;

//Generic type (not a graph) of 2D integers
typedef std::vector<std::vector<int>> vvint;

#endif