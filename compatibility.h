#ifndef COMPATIBILITY_GENERATOR_H
#define COMPATIBILITY_GENERATOR_H
#include "types.h"
#include "scheduler.h"

/* A file defining routines to generate
 * a compatibility graph for memory and functional resources 
 * from a schedule produced by a list scheduler */
 
namespace compatability
{

/* Inverts a graph; where all edges are removed and all non-edges are given an edge */
void invertGraph(graph& g);

/* Generates a memory compatibility graph.
 * Each vertex corresponds to a sequencing graph operation. An edge exists between
 * verticies i and j if start(i)+delay(i) <= start(j). The start times of each vertex
 * are located in the scheduler output. We define the "delay" as the start time of
 * the latest vertex i has an edge to MINUS the start time of i.
 */
graph memoryGraph(
	const ad_module& m, const digraph& seqGraph, const scheduler::output& schduele);

/* Generates a functional compatibility graph for a function type
 * ("ADD", "SUB", "MULT", ...), given the global schedule and sequencing graph.
 * Each vertex corresponds to an operation of type "type", and an edge exists
 * between vertices (i,j) if i is not in the same timestep of j.
 */
graph functionalGraph(
	const ad_module& m, const digraph& seqGraph, 
	const scheduler::output& schduele, const std::string& type);

}

#endif
