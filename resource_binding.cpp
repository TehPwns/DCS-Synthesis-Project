#include "scheduler.h"
#include "utility.h"
#include "clique_partition.h"
#include "resource_binding.h"

namespace binding
{

//Replaced by bryan's code for constant-time lookups
int checkSchd(const scheduler::output& scheduele, int vertex)
{
    //Returns the timestep "vertex" starts in
    return scheduele.schedule_alt[vertex];
}

/*
*Function builds a compatibility graph based on which functin (registerBind or functionalBind) called it
*Then takes graph output for that and feeds into clique partitioning function, which feeds back a vvint
*vector of vectors of cliques:
* A sample output would be:
*   Clique #0 (size = 3) = {  7  3  0  }
*   Clique #1 (size = 2) = {  5  1  }
*   Clique #2 (size = 1) = {  8  }
*/
vvint buildBind(const ad_module& module, const digraph& seqGraph,
                const scheduler::output sch, bool b,
                const std::string& type,
                std::string& conflict_out
                ) //DOUBLE CHECK THIS, YEA THIS!
{
    int n = 0;                              //Number of verticies to build conflict graph over
    std::vector<int> relationIndex;

    if(b) { 								//if register bind function call
        n = seqGraph.numberOfVertices();	//size of seqGraph is our regbind size
    }
    else {												//if functional unit function call
        int count = 0;
        for(const ad_binary_op& op : module.operations){//for each module.operations[i]
            if(op.type == type) {						//if op type matches desired type
                relationIndex.push_back(count);			//make next index position equal to count(absolute position)
                ++n;									//increment relative count
            }
            ++count;									//increment absolute counter
        }
    }

    // Build the edge compatibility graph; new graph rBinding of size n
    graph rBinding(n);

    for (unsigned i=0; i < rBinding.numberOfVertices(); ++i) { 	//for each vertex i, if b use i, if b! use relationIndex
        //Skip operations not of this type on functional binding
        if(!b && module.operations[i].type != type)
            continue;

        int s1 = 0;
        s1 = checkSchd(sch, !b ? relationIndex[i] : i);

        int e1 = 0;													//(start with ending edge time of 0)
        for (auto j =  seqGraph.verticesFromVertexBegin(i);
                  j != seqGraph.verticesFromVertexEnd(i); ++j) {             //for each vertex reachable from said vertex i
            if(!b && module.operations[*j].type != type)
                continue;
            e1 = std::max(e1, checkSchd(sch, !b ? relationIndex[*j] : *j)); //for each vertex j, if b use j, if b! use relationIndex
        }

        //do same thing here to find e2
        for (unsigned k = 0; k < rBinding.numberOfVertices(); ++k) {  //for each vertex k, if b use k, if b! use relationIndex
            //Skip operations not of this type
            if(!b && module.operations[k].type != type)
                continue;

            int s2 = 0;
            s2 = checkSchd(sch, !b ? relationIndex[k] : k);

            int e2 = 0;                                               //(start with ending edge time of 0)
            for (auto l = seqGraph.verticesFromVertexBegin(k);
                      l < seqGraph.verticesFromVertexEnd(k); ++l) {   //for each vertex l, if b use l, if b! use relationIndex
                if(!b && module.operations[*l].type != type)
                    continue;
                e2 = std::max(e2, checkSchd(sch, !b ? relationIndex[*l] : *l));
            }

            //Here we determine if the verticies with their start/ends are compatible.
            //Do some voodoo here to compare e1 to e1 then teleport back to find e2 again,
            //then e1 after deciding if inserting edge or not.
            if((i != k) && (!((e1 == e2) || (s1 == s2) || ((s1 < s2) && (e1 > s2))))) {
                rBinding.insertEdge(i,k);
            }
        }
    }

    //after graph, do this stuff:
    vvint result = clique_partition(rBinding); //not sure where to go after here-----------------Call clique partition on the binding

    //On functional binding, convert cliques given of relational verticies to absolute verticies
    if(!b) {
        for(auto& row : result)
            for(int& item : row)
                item = relationIndex[item];
    }

    //Output conflict graph upwards
    conflict_out = getDotGraphText(rBinding);

    return result;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

vvint registerBind(const ad_module& module,
                   const scheduler::output sch,
                   const digraph& seqGraph)
{
    std::string dummy;
    return buildBind(module, seqGraph, sch, true, "", dummy);
}

vvint functionalBind(const ad_module& module,
                     const scheduler::output sch,
                     const digraph& seqGraph,
                     const std::string& type,
                     std::string& conflict_out)
{
    return buildBind(module, seqGraph, sch, false, type, conflict_out);
}

}
