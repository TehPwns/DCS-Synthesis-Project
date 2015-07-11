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

    //TODO: Produce scheduler output here

    if (input.maxLatency == -1) {
        std::cout << "resource constrained (not implemented)" << std::endl;


    } else {
        std::cout << "latency constrained" << std::endl;
        out.schedule.resize(input.maxLatency);

        unsigned int ops = module.operations.size();
        unsigned int offset;
        unsigned int stage = 0;
        unsigned int t1, t2;
        std::vector<unsigned int> stamp (ops);
        std::vector<bool> ready (ops);
        std::vector<bool>::iterator pos;
        std::string one, two, three;
        bool i1 = false, i2 = false;

        /*
            readiness precedence (descending order)
            - both operation inputs are original module inputs
            - both immediate ancestor edges for an operation lead to nodes that are ready

            if (i1 and i2 is in inputs)
            if (i1 is an input and i2 is from ready ancestor)
            if (i1 is from ready ancestor and i2 is from input)
            if (i1 and i2 is from ready ancestor)
        */

        do {

            for (unsigned int i = 0; i < ops; i++) {

                pos = std::find(ready.begin(), ready.end(), false);
                offset = pos - ready.begin();

                if (pos == ready.end())
                    break;

                one = module.operations[offset].input0;
                two = module.operations[offset].input1;

                for (unsigned int j = 0; j < module.inputs.size(); j++) {
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

                for (unsigned int j = 0; j < ops; j++) {
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

                //std::cout << ready << std::endl;
                // std::cout << stamp << std::endl;
            }

            ++stage;

        } while (stage < ops);

    }

    return out;
}

}
