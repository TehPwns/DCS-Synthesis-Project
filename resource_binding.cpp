#include "resource_binding.h"

namespace binding
{

vvint registerBind(const ad_module& module, vvint seqGraph)
{
bool b = true;
string op = "nothing";
return buildBind(module, seqGraph, b, op, type);
}

vvint functionalBind(const graph& function_conflict, const std::string& type, const ad_module& module, vvint seqGraph)
{
    vvint result;
    (void)function_conflict;
    (void)type;

    return result;
}



//will be replaced by bryan's code later for k-time
int checkSchd(const vertex){
	for(i=0 ; i < schduele.size(); ++i){										//iterate through each time space of schduele
		for(j=0; j < schduele[i].size(); ++j){									//iterate through vertexes in time spaces
			if (vertex(vertex) == schduele[i][j]){								//k is timeslot
				returh k;														//find ending time of vertex data (k) return
			}
		}	
	}

}





//---------------------------------------------------------------------------------------------------------------------------------------------

vvint buildBind(const ad_module& module, vvint seqGraph, bool b, string op){							//DOUBLE CHECK THIS, YEA THIS!

int absoluteCount, n = 0;
int <vector> relationIndex;

if(b){ 																							//if register bind function call
	n = seqGraph.numberOfVertices();															//size of seqGraph is our regbind size
}

else {																							//if functional unit function call
	for(ad_binary_op& op : module.operations) {													//for each module.operations[i] 
		if(op.type == type) {																	//if op type matches desired type
			relationIndex.push_back(count);														//make next index position equal to count(absolute position)
			++n;																				//increment relative count
		}
		++count;																				//increment absolute counter
	}
}

// Build the edge compatibility graph
andres::graph::Graph<> rBinding(n);																//create new graph rBinding of size n

for (i=0; i < rBinding.numberOfVertices(); ++i) { 												//for each vertex i, if b use i, if b! use relationIndex
	int s1 = 0;
	if(!b){
		s1 = checkSchd(relationIndex[i]);
	}
	else {							
	s1 = checkSchd(i);
	}
	
	int e1 = 0;																					//(start with ending edge time of 0)
	for (j = verticesFromVertexBegin(i); j < numberOfVerticesFromVertex(i); ++j){ 				//for each edge connected to said vertex i
		if(!b){																					//for each vertex j, if b use j, if b! use relationIndex
		e1 = checkSchd(relationIndex[j]);
		}
		else{
		e1 = checkSchd(j);

		}
	}
	//do same thing here to find e2
	for (k = 0; k < rBinding.numberOfVertices(); ++k) { 										//for each vertex k, if b use k, if b! use relationIndex
		int s2 = 0;																				
		if(!b){
		s2 = checkSchd(relationIndex[k]);
		}
		else{
		s2 = checkSchd(k);
		}

		int e2 = 0;																				//(start with ending edge time of 0)
			for (l = verticesFromVertexBegin(k); l < numberOfVerticesFromVertex(k); ++l){ 		//for each vertex l, if b use l, if b! use relationIndex
				if(!b){
				e2 = checkSchd(relationIndex[l]);
				}
				else{
				e2 = checkSchd(l);
				}
			}
		//do some voodoo here to compare e1 to e1 then teleport back to find e2 again, 
		//then e1 after deciding if inserting edge or not.
		if((i != k) && !((e1 == e2) || (s1 == s2) || ((s1 < s2) && (e1 > s2))) && (b)){ 				//check for compatibility && reg bind bool (true - reg.bind)
			rBinding.insertEdge(i,k); 																	//and create connection for registers if gucci.
		}
		else if((relationIndex[i] != relationIndex[k]) && !((e1 == e2) || (s1 == s2) || ((s1 < s2) && (e1 > s2))) && (!b)){			//else check for compatibility and reg bool (false - f.u.)
			rBinding.insertEdge(relationIndex[i],relationIndex[k]);																	//and create connection for functional units if gucci.
		}																										
	}
}
//after graph, do this stuff:
vvint result = clique_partition(rBinding); //not sure where to go after here-----------------Call clique partition on the binding
for(i = 0; i < newClique.size(); ++i){
	//allocate new register R
	//Bind all edges in c to R
}

}
//------------------------------------------------------------------------------------------------------------------------------------------------





}