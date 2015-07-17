#include <iostream>
#include <string>
#include "audi_parse.h"
#include "scheduler.h"
#include "sequence_graph.h"
#include "utility.h"
#include "resource_binding.h"
#include <unordered_map>

namespace output
{

std::pair<std::set<std::string>, std::vector<std::string>>
getFunctionUnitInfo(const ad_module& module)
{
    std::set<std::string> funcunits;
    std::vector<std::string> vertices;
    for(const ad_binary_op& op : module.operations){    //for each module.operations[i]
        funcunits.insert(op.type);                      //push operation type string into a set funcunits
        vertices.push_back(op.type);                    //push operation type string into vector (use index to denote vertex,
    }                                                   //item to denote function type)
    return std::make_pair(std::move(funcunits), std::move(vertices));
}


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


std::string getOutput(int argc, char** argv)
{
    //Parse and print .aif file
    ad_module m = parseAifFile(argv[1]);

    //Generate sequencing graph and print in DOT format
    digraph g = sequence::generate(m);

    //Generate module schedule and print
    scheduler::output sched = scheduler::generate(m, g, scheduler::getUserInput(argc, argv));

    auto pair = getFunctionUnitInfo(m);

    //Generate function and memory resource binding (prints graph too in DOT)
    vvint binding = binding::functionalBind(m, sched, g, "ADD");

    return getFinalDotGraphText(g, m, sched);
}

}
