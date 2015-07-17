#ifndef OUTPUT_H
#define OUTPUT_H
#include <string>
#include <vector>

namespace output
{

//Runs the entire program and returns the final output file text
std::pair<std::string,std::string> getOutput(int argc, char** argv);

}

#endif // OUTPUT_H
