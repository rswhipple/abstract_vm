#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include "ioperand.hpp"
#include <vector>
#include <list>


int execute(std::vector<Instruction>& commands);
void executeDump(std::list<IOperand*>& stk);
int executePush(std::list<IOperand*>& stk, std::string typ, std::string val);
int executeAssert(std::list<IOperand*>& stk, std::string typ, std::string val);
int executePrint(std::list<IOperand*>& stk);

#endif