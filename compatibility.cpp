#include "compatibility.h"

namespace compatiblity
{

void invertGraph(graph&)
{

}

/* Generates a memory compatibility graph.
 * Each vertex corresponds to an input, output, or register.
 * An edge exists between vertices i,j if the first write and 
 * final read times are not the same.
 */
graph memoryGraph(const ad_module& m, const digraph& seqGraph, const scheduler::output& schduele)
{
    graph g;

    (void)m;
    (void)seqGraph;
    (void)schduele;

    //TODO: Produce graph here

    return g;
}

/* Generates a functional compatibility graph for the function type
 * ("ADD", "SUB", "MULT", ...) given the global schedule and sequencing graph.
 * Each vertex corresponds to an operation of type "type", and an edge exists
 * between vertices (i,j) if i is not in the same timestep of j.
 */
graph functionalGraph(const ad_module& m, const digraph& seqGraph, 
	const scheduler::output& schduele, const std::string& type)
{
    graph g;

    (void)m;
    (void)seqGraph;
    (void)schduele;
    (void)type;

    //TODO: Produce graph here

    return g;
}

}
