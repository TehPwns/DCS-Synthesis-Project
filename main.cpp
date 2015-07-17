#include <iostream>
#include "output.h"

int main(int argc, char** argv)
{
    //Print usage if not enough arguments
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <.aif file> [RESOURCE=LIMIT]..." << std::endl;
        exit(1);
    }

    try {
        std::cout << output::getOutput(argc, argv) << std::endl;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
