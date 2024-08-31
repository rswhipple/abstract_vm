#ifndef PARSE_HPP
#define PARSE_HPP

#include <unordered_set>
#include <string>
#include <sstream>
#include <vector>
#include <array>

int readFile(const std:: string& filename); // Read file
int readFromStdin(); // Read from stdin
bool isValidInstruction(const std::string& line);   // Validate instr format
bool isValidValue(const std::string& str, const std::array<std::string, 5>& prefixes);    // Validate instr prefix
bool splitTypeValue (const std::string& input, const std::string& type, const std::string& value);  // Split 
int tokenize(std::string line, Instruction& inst);
int executeCmd(std::vector<Instruction> commands);

#endif
