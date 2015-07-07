#include <iostream>
#include "audi_parse.h"
#include "scheduler.h"
#include "utility.h"

int main(int argc, char** argv)
{
	ad_module m = parseAifFile(argv[1]);
	std::cout << m << std::endl;
	
	auto input = scheduler::getUserInput(argc, argv);
	std::cout << input.maxLatency << std::endl;
	for(auto& elem : input.maxResources)
		std::cout << elem.first << " " << elem.second;
	
	return 0;
}
