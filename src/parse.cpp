#include "../inc/main.hpp"
#include <iostream>

using namespace std;

const std::array<std::string, 13> instructionList = {
	"push",	
	"pop", 
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit",
	";;",
    ";"
};

const std::array<std::string, 5> valueList = {
  "int8",
  "int16",
  "int32",
  "float",
  "double"
};

int readFile(const string& filename)
{
    // Open file stream
    ifstream file(filename);

     if (!file.is_open()) return 2;

     // Instanciate Instruction obj + create vector to store all instructions
    vector<Instruction> commands;
    Instruction inst = {"temp", "temp", "temp"};

     // Parse program line by line
    string line;
    while (getline(file, line)) {
        if (line == "exit") {
            file.close();
            int runtimeError = execute(commands);
            if (runtimeError) return runtimeError;
            return EXIT_SUCCESS;
        }
        if (isComment(line)) continue;  // Skips comments
        if (!isValidInstruction(line)) return 3; // error: invalid instruction
        if (tokenize(line, inst) != 0) return 3; // error: invalid instruction
        commands.emplace_back(inst);    // Store current inst in vector
    }

     file.close();
    return EXIT_FAILURE;
}

int readFromStdin()
{
    // Instanciate Instruction obj + create vector to store all instructions.
    vector<Instruction> commands;
    Instruction inst = {"temp", "temp", "temp"};

     // Parse program line by line
    string line;
    while (getline(cin, line)) {
        if (line == ";;") {
            // Execute all commands
            int runtimeError = execute(commands);
            if (runtimeError) return runtimeError;
            return EXIT_SUCCESS;
        }
        if (isComment(line)) continue;  // Skips comments
        if (!isValidInstruction(line)) return 3; // error: invalid instruction
        if (tokenize(line, inst) != 0) return 3; // error: invalid instruction
        commands.emplace_back(inst);    // Store current inst in vector.
    }
    return EXIT_FAILURE;
}

bool isComment(const string& line) 
{
    if (line == "") return true;

     string str1;
    stringstream ss(line);
    ss >> str1;

     if (str1[0] == ';') return true;

     return false;
}

bool isValidPrefix(const string& str, const array<string, 5>& prefixes) 
{
    for (const auto& prefix : prefixes) {
        if (str.find(prefix) == 0) {
        return true;
        }
    }
    return false;
}

bool isValidCommand(const string& str, const array<string, 13>& commands) 
{
    for (const auto& command : commands) {
        if (str.find(command) == 0) {
        return true;
        }
    }
    return false;
}

bool isValidValue (const string& input)
{
    string value;
    string type;
    size_t open = input.find('(');
    size_t close = input.find(')', open);

     if (open != string::npos && close != string::npos && close > open) {
        type = input.substr(0, open);    // Text before '('
        value = input.substr(open + 1, close - open - 1); // Text between '(' and ')'
        return true;
    }

     return false;
}

bool isValidInstruction(const string& line) 
{
    int spaceCount = count(line.begin(), line.end(), ' ');
    
    string str1, str2, str3;
    stringstream ss(line);
    ss >> str1;

     if (isValidCommand(str1, instructionList)) {
        if (str1 == "push" || str1 == "assert") {
            ss >> str2;
            if (spaceCount > 1) {
                ss >> str3;
                if (str3[0] != ';') {
                    return false;
                }
            }
            if (isValidPrefix(str2, valueList)) {
                return true;
            }
            cout << "failing here" << endl;
        } else if (str1[0] == ';') {
            return true;
        } else if (spaceCount == 0 ) {
            return true;
        } else if (spaceCount > 0) {
            ss >> str2;
            if (str2[0] == ';'){
                return true;
            }
        }
    }
    return false;
}

bool isValidParenthesis(string str, size_t& open, size_t& close) 
{ 
    int openCount = 0;
    int closeCount = 0;
    size_t index = 0;
    string::iterator it;

     for (it = str.begin(); it != str.end(); it++, index++) { 
        if (*it == '(') {
            open = index;
            openCount++;
            }
        if (*it == ')') {
            close = index;
            closeCount++;
            }
    } 

     // Check that there is only 1 '(' and 1 ')' 
    // Check that the ')' is the last char of the str
    if (openCount > 1 || closeCount > 1 || close != index - 1) 
        return false;
    return true;
} 

bool isValidInt(const string &str, string valid) 
{ 
    for (char ch : str) { 
        // If ch isn't in valid string return false
        if (valid.find(ch) == string::npos) return false;
    } 

     return true;
} 

bool isValidDecimal(const string &str, string valid) 
{ 
    int decimalPoint = 0;
    for (char ch : str) { 
        if (valid.find(ch) == string::npos) return false;
        if (ch == '.') decimalPoint++;
    } 

     if (decimalPoint > 1) return false;
    return true;
} 

 
bool splitTypeValue (const string& input, string& type, string& value)
{
    size_t open;
    size_t close;

     if (!isValidParenthesis(input, open, close)) return false;

     if (open != string::npos && close != string::npos && close > open) {
        type = input.substr(0, open);    // Text before '('
        value = input.substr(open + 1, close - open - 1); // Text between '(' and ')'
    } else return false;

     // validate value string
    if (type == "int8" || type == "int16" || type == "int32") {
        if (isValidInt(value, "0123456789")) return true;
    } else if (isValidDecimal(value, "0123456789.")) return true;

     return false;
}

int tokenize(string line, Instruction& inst)
{
    stringstream ss(line);
    string tok;
    vector<string> tokens;
    string type;
    string value;

     while (ss >> tok) {
        tokens.push_back(tok);
    }

     inst.setCommand(tokens[0]);

     if (tokens[0] == "push" || tokens[0] == "assert") {
        if (splitTypeValue(tokens[1], type, value)) {
            inst.setType(type);
            inst.setValue(value);
        } else {
            return EXIT_FAILURE;
        }
    } else {
        inst.setType("");
        inst.setValue("");
    }

     return EXIT_SUCCESS;
}