#include "sequence_graph.h"

namespace sequence
{

digraph generate(const ad_module& m)
{
	int numOps = m.operations.size();
	digraph g(numOps);
	
	/* For each operation, we look at the operations 
	 * coming after it. If any after it takes in the 
	 * output as input, add an edge. */
	
	for(int i =   0; i != numOps; ++i)
	for(int j = i+1; j != numOps; ++j)
	{
		const ad_binary_op& op0 = m.operations[i];
		const ad_binary_op& op1 = m.operations[j];
	
		/* End the loop when another operation writes
		 * to the register op0 wrote to */
		if(op1.output == op0.output)
			break;
			
		//Insert an edge (i,j) if op1 takes op0's output
		if(op1.input0 == op0.output || op1.input1 == op0.output) {
			g.insertEdge(i, j);
		}
	}

	return g;
}

}
