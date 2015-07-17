#include <iostream>
#include <string>
#include <unordered_map>
#include "audi_parse.h"
#include "scheduler.h"
#include "sequence_graph.h"
#include "utility.h"
#include "resource_binding.h"

namespace output
{

template<typename GRAPH>
std::string getFinalDotGraphText(const GRAPH& g, const ad_module& m, const scheduler::output& sch)
{
    std::unordered_map<std::string, std::string> opmap = {
        {"ADD",  "color=blue, shape = box"},
        {"MULT", "color=green, shape = invhouse"},
        {"SUB", "color=red, shape = invhouse"}
    };

    std::stringstream ss;
    std::string text = getDotGraphText(g);
    std::vector<std::string> split = Split(text,"\n");

    ss << "digraph {" << std::endl;
    ss << "\tnode [style=filled];" << std::endl;

    //Print types
    ss << "\t{" << std::endl;
    for(const ad_binary_op& op : m.operations) {
        auto it = opmap.find(op.type);
        if(it != opmap.end()) {
            ss << "\t\t" << op.number-1 << " [" << it->second << "]" << std::endl;
        }
    }
    ss << "\t}\n" << std::endl;

    //Make same scheduled timesteps same rank
    for(auto& row : sch.schedule) {
        ss << "\t{ rank=same; ";
        for(auto& item : row)
            ss << std::to_string(item) << "; ";
        ss << "}" << std::endl;
    }
    ss << '\n';

    //Place the "a -- b" lines only into the output
    for(std::string& s : split) {
        if(s.find_first_of("{}") == std::string::npos) {
            ss << s << std::endl;
        }
    }

    ss << "}" << std::endl;
    return ss.str();
}

std::set<std::string> getFunctionUnitInfo(const ad_module& module)
{
    std::set<std::string> funcunits;
    for(const ad_binary_op& op : module.operations) {   //for each module.operations[i]
        funcunits.insert(op.type);                      //push operation type string into a set funcunits
    }                                                   //item to denote function type)
    return std::move(funcunits);
}

typedef std::vector<std::pair<std::string, vvint>> functional_bindings;

/* Generates the actual text to put in the file */
std::string getOutputFileText(const functional_bindings& func_bindings, const vvint& mem_bindings)
{
    std::stringstream ss;

    //Text for all multiplexers generated across registers and functional units
    std::vector<std::string> multiplexer_text;

    /* Put each functional unit in the file and what it is bound to
     * under it */
    for(const auto& binding_pair : func_bindings)
    {
        //Get info and output header. Ex: "N ADD Units:"
            std::string name = binding_pair.first;
        const vvint& binding = binding_pair.second;
        ss << binding.size() << " " << name << " functional units:" << std::endl;

        //Output each unit and what is bound to it
        int i = 0;
        for(const auto& cliques : binding) {
            ss << "\t" << name << i++ << ": " << cliques << std::endl;
            if(cliques.size() > 1) {
                std::stringstream mstream;
                mstream << "\t"    << "MUX"  << multiplexer_text.size() << ": "
                        << cliques << " -> " << name << i;
                multiplexer_text.push_back(mstream.str());
            }
        }
        ss << "\n";
    }

    /* Output register usage */
    ss << mem_bindings.size() << " " << "registers needed:" << std::endl;
    int i = 0;
    for(const auto& binding : mem_bindings) {
        ss << "\tR" << i++ << ": " << binding << std::endl;
        if(binding.size() > 1) {
            std::stringstream mstream;
            mstream << "\t"    << "MUX"  << multiplexer_text.size() << ": "
                    << binding << " -> " << "R" << i;
            multiplexer_text.push_back(mstream.str());
        }
    }
    ss << '\n';

    /* Print out accumulated multiplexers */
    ss << multiplexer_text.size() << " multiplexers needed: " << std::endl;
    for(const std::string& mux : multiplexer_text) {
        ss << mux << std::endl;
    }

    return ss.str();
}

std::string getGraphFileText(
    const ad_module& module,
    const digraph& seqGraph,
    const scheduler::output& sch,
    const std::vector<std::pair<std::string,std::string>>& conflict_texts)
{
    std::stringstream ss;

    //Put SeqGraph
    ss << "#Sequence Graph:" << std::endl;
    ss << getDotGraphText(seqGraph) << std::endl;
    ss << std::endl;

    //Put all conflict graphs
    for(auto& conflict_graph : conflict_texts) {
        ss << "#" << conflict_graph.first  << " compatibility graph:" << std::endl;
        ss << conflict_graph.second << std::endl;
        ss << std::endl;
    }

    //Put scheduled graph
    ss << "#Scheduled sequence graph: " << std::endl;
    ss << getFinalDotGraphText(seqGraph, module, sch) << std::endl;

    return ss.str();
}

std::pair<std::string,std::string> getOutput(int argc, char** argv)
{
    //Parse and print .aif file
    ad_module m = parseAifFile(argv[1]);

    //Generate sequencing graph and print in DOT format
    digraph g = sequence::generate(m);

    //Generate module schedule and print
    scheduler::output sched = scheduler::generate(m, g, scheduler::getUserInput(argc, argv));

    /* Get all types of funtions in module and bind resources for each
     * type of operation in the module */
    auto typeset = getFunctionUnitInfo(m);
    functional_bindings bindings;
    std::vector<std::pair<std::string,std::string>> conflict_texts;
    for(const std::string& type : typeset) {
        std::string conflict_out;
        bindings.push_back(
            std::make_pair(type, binding::functionalBind(m, sched, g, type, conflict_out)) );
        conflict_texts.push_back( std::make_pair(type, std::move(conflict_out)) );
    }

    //Generate function and memory resource binding
    vvint memory_binding = binding::registerBind(m, sched, g);

    return std::make_pair(
        getOutputFileText(bindings, memory_binding),
        getGraphFileText(m, g, sched, conflict_texts));
}

}
