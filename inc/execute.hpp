#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include "types.hpp"
#include <vector>

Cmd stringToCmd(const std::string& instName);
int execute(std::vector<Instruction> commands);
int executePush(std::list <Number> stk, std::string typ, std::string val);
int executeAssert(std::list <Number> stk, std::string typ, std::string val);

#endif