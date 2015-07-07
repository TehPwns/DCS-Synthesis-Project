#include "compatibility.h"

namespace compatiblity
{

void invertGraph(graph& g)
{
	for(auto& row : g)
		for(int& entry : row)
			entry = (entry == 1) ? 0 : 1;
}

/* Generates a memory compatibility graph.
 * Each vertex corresponds to an input, output, or register.
 * An edge exists between verticies i,j if the first write and 
 * final read times are not the same.
 */
graph memoryGraph(const ad_module& m, const graph& seqGraph, const scheduler::output& schduele)
{

}

/* Generates a functional compatibility graph for the function type
 * ("ADD", "SUB", "MULT", ...) given the global schduele and sequenceing graph.
 * Each vertex corresponds to an operation of type "type", and an edge exists
 * between verticies (i,j) if i is not in the same timestep of j.
 */
graph functionalGraph(const ad_module& m, const graph& seqGraph, 
	const scheduler::output& schduele, const std::string& type)
{


}

}