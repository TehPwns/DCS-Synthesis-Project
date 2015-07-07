#include "utility.h"

std::vector<std::string> Split(const std::string& target, const std::string& delims)
{
    std::vector<std::string> result;
    size_t startPos = 0, it = 0;
    
    do {
        it = target.find_first_of(delims, startPos);
        result.push_back(target.substr(startPos, it - startPos));
        startPos = target.find_first_not_of(delims, it+1);
    }
    while(it != std::string::npos);
    
    return result;
}

void trim(std::string& s)
{
    s.erase(0, s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t")+1, std::string::npos);
}

void removeComments(std::string& s)
{
    size_t comment = s.find('#');
    if(comment != std::string::npos)
        s.erase(comment, std::string::npos);
}