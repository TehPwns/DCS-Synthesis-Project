#include <iostream>
#include <fstream>
#include "output.h"

int main(int argc, char** argv)
{
    //Print usage if not enough arguments
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <.aif file> [RESOURCE=LIMIT]..." << std::endl;
        exit(1);
    }

    try {
        std::fstream output_file("output.txt", std::ios::out);
        std::fstream graph_file("graphs.txt", std::ios::out);

        //Get output texts
        auto text_pair = output::getOutput(argc, argv);
        output_file << text_pair.first  << std::endl;
        graph_file  << text_pair.second << std::endl;

        //Generates cool images
        system("dot graphs.txt -O -Tpng");
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
