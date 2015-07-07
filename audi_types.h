#ifndef AUDI_TYPE_H
#define AUDI_TYPE_H
#include <iosfwd>
#include <vector>
#include <string>

/* A file specifying types parsed from a .aif file */

struct ad_input
{
	std::string name;
	int bitwidth;
};

//Inputs, outputs, and registers are the same thing
typedef ad_input ad_output;
typedef ad_input ad_register;

/* A single-output binary operation consisting of an id, two inputs, output,
 * type, and bitwidth. These are specified on lines like "op2 MULT 8 c1 r0 r1" */
struct ad_binary_op
{
	int number;
	int bitwidth;
	std::string type;
	std::string input0, input1;
	std::string output;
};


/* A full AUDI module file, of I/O, operations, and registers. */
struct ad_module
{
	std::vector<ad_input>  	  inputs;
	std::vector<ad_output> 	  outputs;
	std::vector<ad_binary_op> operations;
	std::vector<ad_register>  regs;
};

//Audi type I/O operators
std::istream& operator>>(std::istream& is, ad_input& in);
std::istream& operator>>(std::istream& is, ad_binary_op	& op);
std::istream& operator>>(std::istream& is, ad_module& m);
std::ostream& operator<<(std::ostream& os, const ad_input& in);
std::ostream& operator<<(std::ostream& os, const ad_binary_op& op);
std::ostream& operator<<(std::ostream& os, const ad_module& m);

#endif
