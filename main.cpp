#include <iostream>
#include "audi_parse.h"
#include "scheduler.h"
#include "sequence_graph.h"
#include "utility.h"
#include "resource_binding.h"
#include <unordered_map>

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

/*****************************************************************/

int main(int argc, char** argv)
{
    //Print usage if not enough arguments
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <.aif file> [RESOURCE=LIMIT]..." << std::endl;
        exit(1);
    }

    try {
        //Parse and print .aif file
        ad_module m = parseAifFile(argv[1]);
        std::cout << "Parsed .aif file:\n" << m  << '\n' << std::endl;

        //Generate sequencing graph and print in DOT format
        digraph g = sequence::generate(m);
        std::cout << "Sequence Graph in DOT format:\n" << getDotGraphText(g) << '\n' << std::endl;

        //Generate module schedule and print
        scheduler::output sched = scheduler::generate(m, g, scheduler::getUserInput(argc, argv));
        std::cout << "Scheduler output:\n" << sched.schedule << '\n' << std::endl;
        std::cout << "O(1) goodness:\n" << sched.schedule_alt << '\n' << std::endl;

        //Generate function and memory resource binding (prints graph too in DOT)
        vvint binding = binding::functionalBind(m, sched, g, "ADD");
        std::cout << binding << std::endl;

        std::cout << getFinalDotGraphText(g, m, sched) << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
