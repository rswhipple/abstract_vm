#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

class Instruction {
private:
    std::string command;
    std::string type;
    std::string value;

public:
	// Constructor
	Instruction(const std::string& cmd, const std::string& typ,
		const std::string& val)
		: command(cmd), type(typ), value(val) {}

	std::string getCommand() const { return command; }
	void setCommand(const std::string& cmd) { command = cmd; }

	std::string getType() const { return type; }
	void setType(const std::string& typ) { type = typ; }

	std::string getValue() const { return value; }
	void setValue(const std::string& val) { value = val; }
};

#endif
