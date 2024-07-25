#ifndef PARSE_HPP
#define PARSE_HPP

#include "types.hpp"
#include <string>

const int parse(char *filename, const t_node*& cmdPtr);
const t_node*& readFile(const std::string& filename, const t_node*& cmdPtr); // Read file
const t_node*& readFromStdin(const t_node*& cmdPtr); // Read from stdin
const t_node*& strToNode(std::string line);

#endif