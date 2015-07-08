#ifndef SEQUENCE_GRAPH_H
#define SEQUENCE_GRAPH_H
#include "types.h"
#include "audi_types.h"

/* A file defining routunes to generate
 * a sequence graph from a parsed ad_module */

namespace sequence
{
 
/* (P. 122-123) 
 * A sequence graph is a digraph G(V,E) where each vertex
 * is a one-to-one corrispondance of n operations, and
 * the edge set E = {(vi,vj); i,j = 0,1,2,3...n-1} corresponds 
 * to a dependence from vi to vj.
 *
 * Input:  valid ad_module from an AUDI file
 * Output: sequencing graph of dependent operations
 */
digraph generate(const ad_module& m);

}
 
#endif
