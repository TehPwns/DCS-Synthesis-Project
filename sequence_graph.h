#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H
#include "types.h"
#include "audi_types.h"

/* A file defining routunes to generate
 * a sequence graph from a parsed ad_module */

namespace sequence
{
 
/* (P. 122-123) 
 * A sequence graph is a graph G(V,E) where each vertex
 * is a one-to-one corrispondance of n operations, and
 * the edge set E = {(vi,vj); i,j = 0,1,2,3...n-1} corresponds 
 * to a dependence from vi to vj.
 *
 * Input:  valid ad_module from an AUDI file
 * Output: graph connectivity matrix
 */
graph generateGraph(const ad_module& m);

}
 
#endif
