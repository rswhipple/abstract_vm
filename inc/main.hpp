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
<<<<<<< HEAD
#include <stdexcept>

=======
#include <unordered_map>
#include <array>
#include <algorithm>
>>>>>>> 849d7ca082ac69dabb4c161369e66c15fb44698f

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
<<<<<<< HEAD

#endif
=======
>>>>>>> 849d7ca082ac69dabb4c161369e66c15fb44698f
