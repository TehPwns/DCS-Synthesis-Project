#ifndef RESOURCE_BINDING_H
#define RESOURCE_BINDING_H
#include "types.h"

namespace binding
{

/* Register binding corresponds to determining the minimum number
 * of registers needed to share all resources for the function.
 * This is done using a clique partition on the conflict graph
 * of the resouce lifetimes (compatibility,h; p.234). The number of
 * cliques corresponds to the number of needed registers
 *
 * Input: Conflict graph of operation lifetimes (P.234 Fig. 6.4)
 * Output: vvint[i][j] where i is each register, and j is bound to i.
 *  Here, each j is an operation in the sequencing graph
 * Example:
 *  0:  1,2,5
 *  1:  3,4
 *  2:  6
 */
vvint registerBind(const graph& resource_conflict);

/* Given the conflict graph for operation of type `type`, (P. 233) binds the
 * operations to function units.
 * Similar to register binding, the number of cliques in the conflict graph
 * for each operation type gives the number of functional units needed.
 * A binding must be performed for each resouce type, hence the parameter
 *
 * Input: Conflict graph for functional type (ADD,SUB,MULT...)
 * Output: vvint[i][j] where i is a functional unit and j is bound to i
 *  Here, each j is a vertex in the sequencing graph.
 */
vvint functionalBind(const graph& function_conflict, const std::string& type);

}

#endif
