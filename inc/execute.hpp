#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include "ioperand.hpp"
#include <vector>
#include <list>


int execute(std::vector<Instruction> commands);
void executeDump(std::list <OperandVar> stk);
int executePush(std::list <OperandVar> stk, std::string typ, std::string val);
int executeAssert(std::list <OperandVar> stk, std::string typ, std::string val);

#endif