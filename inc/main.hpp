#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP
#include "parse.hpp"
#include "error_handler.hpp"
#include "factory.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <list>
#include <unordered_map>
#include <array>
#include <algorithm>
 
 enum class Cmd
{
	Push,
	Assert,
	Pop,
	Dump,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit,
	Error,
};

 
 Cmd stringToCmd(const std::string& instName);
int executeArithmetic(std::list<IOperand*>& stk, Cmd op);
bool lhsIsMostPrecise(IOperand* lhs, IOperand* rhs);
int execute(std::vector<Instruction>& commands);
void executeDump(std::list<IOperand*>& stk);
int executePush(std::list<IOperand*>& stk, std::string typ, std::string val);
int executeAssert(std::list<IOperand*>& stk, std::string typ, std::string val);
int executePrint(std::list<IOperand*>& stk);

 
#endif
