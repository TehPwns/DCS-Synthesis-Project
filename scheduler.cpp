#include <cstdlib>
#include <cctype>
#include "types.h"
#include "utility.h"
#include "audi_types.h"
#include "scheduler.h"

namespace scheduler
{

//User input is specified in the form TYPE=LIMIT
user_input getUserInput(int argc, char** argv)
{
	(void)argc;
	user_input ret;
	
	for(; *argv; ++argv) 
	{
		//Get a std string and convert to uppercase
		std::string arg(*argv);
		for(char& c : arg) c = std::toupper(c);
			
		//Look for equals sign
		size_t eqpos = arg.find('=');
		if(eqpos == std::string::npos) {
			continue;
		}
		
		//Parse "key=value" and insert into return structure
		std::string key = arg.substr(0, eqpos);
		int value = std::atoi(arg.substr(eqpos+1).c_str());
		if(key == "LATENCY") {
			ret.maxLatency = value;
		} else {
			ret.maxResources[key] = value;
		}
	}
	
	return std::move(ret);
}

output generate(const ad_module& module, const digraph& seqGraph, const user_input& input)
{
	output out;
	(void)module;
	(void)seqGraph;
	(void)input;

	//TODO: Produce scheduler output here

	return out;
}

}
