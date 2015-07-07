#ifndef CLIQUE_PARTITION_H
#define CLIQUE_PARTITION_H
#include <vector>
#include "types.h"

/* Given a compatibility graph, returns all of the cliques of the graph 
 * A sample output would be:
 *   Clique #0 (size = 3) = {  7  3  0  }
 *   Clique #1 (size = 2) = {  5  1  }
 *   Clique #2 (size = 1) = {  8  }
 *   Clique #3 (size = 1) = {  6  }
 *   Clique #4 (size = 1) = {  4  }
 *   Clique #5 (size = 1) = {  2  } 
 */
 
vvint clique_partition(const graph& compat_graph);

#endif
