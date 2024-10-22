#ifndef PARSE_HPP
#define PARSE_HPP

#include <vector>
#include <array>
#include "instruction.hpp"

/* 
The 'instructionList' and 'valueList' arrays are used to validate the 
instructions during parsing.
*/
extern const std::array<std::string, 13> instructionList;
extern const std::array<std::string, 5> valueList;

int readFile(const std:: string& filename);
int readFromStdin();
bool isValidInstruction(const std::string& line);   // Validate instr format
bool isValidPrefix(const std::string& str, const std::array<std::string, 5>& prefixes);
bool isValidCommand(const std::string& str, const std::array<std::string, 13>& commands);
bool isValidParenthesis(std::string str, size_t& open, size_t& close);
bool isValidInt(const std::string &str, std::string valid);
bool isValidDecimal(const std::string &str, std::string valid);
bool splitTypeValue (const std::string& input, const std::string& type, const std::string& value);
int tokenize(std::string line, Instruction& inst);

#endif
