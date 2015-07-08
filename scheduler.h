#ifndef LIST_SCHDUELER_H
#define LIST_SCHDUELER_H
#include <map>
#include "types.h"
#include "audi_types.h"

/* A file defining a list scheduling algorithm */

namespace scheduler
{

//Specification of user input from the command line
struct user_input 
{
	/* Map of resource types (ADD,SUB,MULT...) and the upper requested bound 
	* of instances. If a key does not exist, assume an upper bound of infinite. */
	std::map<std::string,int> maxResources;
	
	//Maximum requested latency of the schedule, or -1 for infinite
	int maxLatency = -1;
};

//Output of the list scheduler
struct output
{
	/* vector[i][j] containing operations 0..j on timesteps 0..i
	 * Example:
	 *   0: 3,4,5,10
	 *   1: 1,2,7
	 *   2: 8,9,11 */
	vvint schduele; 	
	
	/* Map of string->int specifying the number of resources of each type allocated
	 * Examples: 
	 *   ADD -> 1; SUB -> 2; MULT -> 2 */
	std::map<std::string,int> allocated;	
};

//Parses argv for a specification of user input
user_input getUserInput(int argc, char** argv);

/*(P. 208)
 * Given a module to schedule and a sequencing graph, along with user input 
 * on requested maximum used resources, gives a list of operations in each timestep. */
output generate(const ad_module& module, const digraph& seqGraph, const user_input& input);

}

#endif
