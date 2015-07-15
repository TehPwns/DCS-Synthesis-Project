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
	(void)seqGraph;

	unsigned int ops = module.operations.size();
	unsigned int offset;
	unsigned int t1, t2;
	unsigned i, j;
	std::vector<unsigned int> stamp (ops);
	std::vector<bool> ready (ops);
	std::vector<bool>::iterator pos;
	std::string one, two, three;
	bool i1 = false, i2 = false;
	
	out.schedule.resize(ops);
	out.schedule_alt.resize(ops);

	//TODO: Produce scheduler output here

	if (input.maxLatency == -1) {
		std::cout << "resource constrained (not implemented)" << std::endl;


	} else {
		std::cout << "latency constrained" << std::endl;

		/* Current operation readiness requirements
		 *
		 *    (i1 and i2 is in the module input set)
		 * or (i1 is a module input and i2 is from an ancestor that's ready)
		 * or (i1 is from an ancestor that's ready and i2 is from module input)
		 * or (i1 and i2 are from ancestors that are ready) */

		do {

			for (i = 0; i < ops; i++) {

				// Using the ready vector to find the earliest instances
				// of unscheduled operations until there are none

				pos = std::find(ready.begin(), ready.end(), false);
				offset = pos - ready.begin();

				if (pos == ready.end())
					break;

				// Comparing the current operation's operands to all of the module inputs
				// since those signals are considered to be ready from the start

				one = module.operations[offset].input0;
				two = module.operations[offset].input1;

				for (j = 0; j < module.inputs.size(); j++) {
					if (one.compare(module.inputs[j].name) == 0) {
						i1 = true;
						t1 = 0;
					}

					if (two.compare(module.inputs[j].name) == 0) {
						i2 = true;
						t2 = 0;
					}

					if (i1 && i2)
						break;
				}

				/* Comparing the output signals of all other operations to the
				 * input signal of the current one, using their time stamps to
				 * determine the earliest possible time to schedule the current
				 * operation, along with updating the timestamp/readiness vectors */

				for (j = 0; j < ops; j++) {
					three = module.operations[j].output;

					if (ready[j] && three.compare(one) == 0) {
						i1 = true;
						t1 = stamp[j];
					}

					if (ready[j] && three.compare(two) == 0) {
						i2 = true;
						t2 = stamp[j];
					}

					if ((i1 && i2) && !ready[offset]) {
						ready[offset] = true;
						stamp[offset] = ((t1 > t2) ? t1 : t2) + 1;
						out.schedule[stamp[offset] - 1].push_back(offset + 1);
						i1 = i2 = false;
						break;
					}
				}

				// std::cout << ready << std::endl;
				// std::cout << stamp << std::endl;
			}

		} while (pos != ready.end());

	}

	for (i = 0; out.schedule[i].size() != 0; i++)
		for (j = 0; j < out.schedule[i].size(); j++)
			out.schedule_alt[out.schedule[i][j] - 1] = i + 1;

	out.schedule.resize(i);

	return out;
}

}
