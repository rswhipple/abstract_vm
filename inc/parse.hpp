#ifndef PARSE_HPP
#define PARSE_HPP

#include "types.hpp"
#include <string>

void readFile(const std::string& filename, const t_node*& cmdPtr); // Read file
void readFromStdin(const t_node*& cmdPtr); // Read from stdin
void strToNode(std::string line);

#endif