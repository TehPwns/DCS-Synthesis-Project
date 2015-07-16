#include <iostream>
#include "audi_parse.h"
#include "scheduler.h"
#include "sequence_graph.h"
#include "utility.h"
#include "resource_binding.h"

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
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
