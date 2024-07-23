#ifndef PARSE_HPP
#define PARSE_HPP

#include "types.hpp"
#include <string>

const int parse(char *filename);
const t_node readFile(const std::string& filename); // Read file
const t_node readFromStdin(); // Read from stdin

#endif