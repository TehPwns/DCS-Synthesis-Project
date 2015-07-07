#include <fstream>
#include "utility.h"
#include "audi_types.h"
#include "audi_parse.h"

ad_module parseAifFile(const std::string& filename)
{
	ad_module m;
	
	std::fstream file(filename);
	if(!file.is_open()) {
		error("Could not open .aif file \"", filename, "\"");
	}
	
	file >> m;
	return m;
}
