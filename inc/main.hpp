#ifndef ABSTRACTVM_HPP
#define ABSTRACTVM_HPP

#include "parse.hpp"
#include "execute.hpp"
#include "error_handler.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <stdexcept>

#include <unordered_map>
#include <array>
#include <algorithm>

template <typename T>
void mark_unused(T&&) {}

extern const std::array<std::string, 13> instructionList;
extern const std::array<std::string, 5> valueList;

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
	Error,
};

Cmd stringToCmd(const std::string& instName);
int executeArithmetic(std::list <IOperand*> stk, Cmd op);

#endif
