#ifndef AUDI_PARSE_H
#define AUDI_PARSE_H
#include "audi_types.h"

/* Given a .aif file, returns an AUDI module. See audi_types.h
 * for definition of this type */

ad_module parseAifFile(const std::string& filename);

#endif
