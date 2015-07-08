#ifndef UTILITY_H
#define UTILITY_H
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <type_traits>
#include "types.h"	//for graph/digraph

/* A file providing various I/O and string handling utilities. */
/************************************************************* */

/* String Split function that skips over consecutive delimiters, 
 * and splits on more than one delimiter (Used for space and tab) */
std::vector<std::string> Split(const std::string& target, const std::string& delims);

//Remove whitespace before and after a string
void trim(std::string& s);

//Provides a << operator for any standard container
template<typename T, class = decltype(std::declval<T>().begin())>
typename std::enable_if<!std::is_same<T,std::string>::value, std::ostream&>::type
operator<<(std::ostream& os, const T& cntr)
{
    os << '[';
    if(not(cntr.empty())) {
        auto end = std::prev(cntr.end());
        for(auto it = cntr.begin(); it != end; ++it)
            os << *it << ",";
        os << *end;
    }
    os << ']';

    return os;
}

//Provides an << operator for any pair
template<typename T1, typename T2>
std::ostream& operator<<(const std::ostream& os, const std::pair<T1,T2>& pair)
{
	os << pair.first << " " << pair.second;
	return os;
}

//Provides an >> operator for an arbitrary vector
template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec)
{
	while(!is.eof()) {
		T item;
		is >> item;
		vec.push_back(std::move(item));
	}
	return is;
}

//Generates the dot graph text for an Andres graph
template<typename GRAPH>
std::string getDotGraphText(const GRAPH& g)
{
	//We have seperate "--" and "->" for graph/digraph
	const char* seperator = " -- ";
	const char* name = "graph";
	if(std::is_same<GRAPH,digraph>::value) {
		seperator = " -> ";
		name = "digraph";
	}

	//Just writes each vertex across each edge
	std::stringstream ss;
	ss << name << " {" << std::endl;
	for(int i = 0; i != g.numberOfEdges(); ++i) {
		int v0 = g.vertexOfEdge(i,0);
		int v1 = g.vertexOfEdge(i,1);
		ss << "\t" << v0 << seperator << v1 << std::endl;
	}
	ss << "}";
	
	return ss.str();
}

//Used to format strings into a runtime_error.
//See http://en.cppreference.com/w/cpp/language/parameter_pack
template<typename... Ts>
void error(Ts... args)
{
    std::stringstream ss;
    int dummy[sizeof...(Ts)] = { (ss << args, 0)... };
    (void)dummy;
    throw std::runtime_error(ss.str());
}

#endif
