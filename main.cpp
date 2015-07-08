#include <iostream>
#include "audi_parse.h"
#include "scheduler.h"
#include "sequence_graph.h"
#include "utility.h"

int main(int argc, char** argv)
{
    //Print usage if not enough arguments
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <.aif file> [RESOUCE=LIMIT]..." << std::endl;
        exit(1);
    }

    try {
        ad_module m = parseAifFile(argv[1]);
        std::cout << m << std::endl;
		
		digraph g = sequence::generate(m);
		std::cout << getDotGraphText(g) << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }
	
	return 0;
}
