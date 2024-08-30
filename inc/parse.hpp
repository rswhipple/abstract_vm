#ifndef PARSE_HPP
#define PARSE_HPP

#include <unordered_set>
#include <string>
#include <sstream>

int readFile(const std:: string& filename, const t_node*& cmdPtr); // Read file
int readFromStdin(const t_node*& cmdPtr); // Read from stdin
bool isValidInstruction(const std::string& line);   // Validate instr format
bool isValidValue(const std::string& str, const std::unordered_set<std::string>& prefixes);     // Validate instr prefix
void strToNode(std::string line);

#endif