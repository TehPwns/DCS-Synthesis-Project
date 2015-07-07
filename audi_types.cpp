#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "utility.h"
#include "audi_types.h"

std::istream& operator>>(std::istream& is, ad_input& in)
{
	is >> in.name >> in.bitwidth;
	return is;
}

std::istream& operator>>(std::istream& is, ad_binary_op& op)
{
	is >> op.number >> op.type   >> op.bitwidth 
	   >> op.input0 >> op.input1 >> op.output;
	return is;
}

std::istream& operator>>(std::istream& is, ad_module& m)
{
	std::string line;
	bool foundEnd = false;
	
	/* In finding each of the lines, the beginnings are ignored here.
	 * The indivudal input function assume there is no beginning text
	 * on the line. and if the "end" line is found, the loop terminates */
	
	while(std::getline(is,line)) {
		trim(line);
		std::stringstream ss(line);
		if(line == "end") {
			foundEnd = true;
			break;
		}
		else if(line.find("inputs") != std::string::npos) {
			ss.ignore(6) >> m.inputs;
		}
		else if(line.find("outputs") != std::string::npos) {		
			ss.ignore(7) >> m.outputs;
		}
		else if(line.find("regs") != std::string::npos) {
			ss.ignore(4) >> m.regs;
		}
		else if(line.find("op") != std::string::npos) {
			ad_binary_op op;
			ss.ignore(2) >> op;
			m.operations.push_back(std::move(op));
		}
		else {
			//Invalid line error
			error(".aif line \"", line, "\" is not a valid AUDI module line.");
		}
	}
	
	//There is an error if we did not find the end of the module
	if(!foundEnd)
		error("Did not find module \"end\" in .aif file");
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const ad_input& in)
{
	os << in.name << "-" << in.bitwidth;
	return os;
}

std::ostream& operator<<(std::ostream& os, const ad_binary_op& op)
{
	os << op.number << " " << op.type   << " " << op.bitwidth << " [" 
	   << op.input0 << " " << op.input1 << " " << op.output   << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const ad_module& m)
{
	os << m.inputs  << '\n'
	   << m.outputs << '\n' 
	   << m.regs    << '\n'
	   << m.operations;
	return os;
}

