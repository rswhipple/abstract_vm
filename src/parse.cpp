
#include "../inc/main.hpp"


int readFile(const std:: string& filename)
{
    // Open file stream
    std::ifstream file(filename);

    if (!file.is_open()) return 2;

    // Instanciate Instruction obj + create vector to store all instructions.
    std::vector<Instruction> commands;
    Instruction inst = {"temp", "temp", "temp"};

    // Parse program line by line
    std::string line;
    while (std::getline(file, line)) {
        if (line == "exit") {
            file.close();
            int runtimeError = execute(commands);
            if (runtimeError) return runtimeError;
            return EXIT_SUCCESS;
        }
        if (!isValidInstruction(line)) return 3; // error: invalid instruction
        if (tokenize(line, inst) != 0) return 3; // error: invalid instruction
        if (inst.getCommand() == ";") continue;     // Skips comments.
        commands.emplace_back(inst);    // Store current inst in vector.
    }

    file.close();
    return EXIT_FAILURE;
}

int readFromStdin()
{
    // Instanciate Instruction obj + create vector to store all instructions.
    std::vector<Instruction> commands;
    Instruction inst = {"temp", "temp", "temp"};

    // Parse program line by line
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ";;") {
            // Execute all commands
            int runtimeError = execute(commands);
            if (runtimeError) return runtimeError;
            return EXIT_SUCCESS;
        }
        if (!isValidInstruction(line)) return 3; // error: invalid instruction
        if (tokenize(line, inst) != 0) return 3; // error: invalid instruction
        if (inst.getCommand() == ";") continue;     // Skips comments.
        commands.emplace_back(inst);    // Store current inst in vector.
    }
    return EXIT_FAILURE;
}


bool isValidPrefix(const std::string& str, const std::array<std::string, 5>& prefixes) 
{
    for (const auto& prefix : prefixes) {
        if (str.find(prefix) == 0) {
        return true;
        }
    }
    return false;
}

bool isValidCommand(const std::string& str, const std::array<std::string, 13>& commands) 
{
    for (const auto& command : commands) {
        if (str.find(command) == 0) {
        return true;
        }
    }
    return false;
}

bool isValidValue (const std::string& input)
{
    std::string value;
    std::string type;
    size_t open = input.find('(');
    size_t close = input.find(')', open);

    if (open != std::string::npos && close != std::string::npos && close > open) {
        type = input.substr(0, open);    // Text before '('
        value = input.substr(open + 1, close - open - 1); // Text between '(' and ')'
        return true;
    }

    return false;
}

bool isValidInstruction(const std::string& line) 
{
    int spaceCount;
    if ((spaceCount = std::count(line.begin(), line.end(), ' ')) > 1){
        return false;
    }
    
    std::string str1, str2;
    std::stringstream ss(line);
    ss >> str1;

    if (isValidCommand(str1, instructionList)) {
        if (str1 == "push" || str1 == "assert") {
            ss >> str2;
            if (isValidPrefix(str2, valueList)) {
                return true;
            }
        } else if (str1 == ";") {
            return true;
        } else if (spaceCount == 0 ) {
            return true;
        }
    }
    return false;
}

bool isValidParenthesis(std::string str, size_t& open, size_t& close) 
{ 
    int openCount = 0;
    int closeCount = 0;
    size_t index = 0;
    std::string::iterator it;

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

bool isValidInt(const std::string &str, std::string valid) 
{ 
    for (char ch : str) { 
        // If ch isn't in valid string return false
        if (valid.find(ch) == std::string::npos) return false;
    } 

    return true;
} 

bool isValidDecimal(const std::string &str, std::string valid) 
{ 
    int decimalPoint = 0;
    for (char ch : str) { 
        if (valid.find(ch) == std::string::npos) return false;
        if (ch == '.') decimalPoint++;
    } 

    if (decimalPoint > 1) return false;
    return true;
} 


bool splitTypeValue (const std::string& input, std::string& type, std::string& value)
{
    size_t open;
    size_t close;

    if (!isValidParenthesis(input, open, close)) return false;

    if (open != std::string::npos && close != std::string::npos && close > open) {
        type = input.substr(0, open);    // Text before '('
        value = input.substr(open + 1, close - open - 1); // Text between '(' and ')'
    } else return false;

    // validate value string
    if (type == "int8" || type == "int16" || type == "int32") {
        if (isValidInt(value, "0123456789")) return true;
    } else if (isValidDecimal(value, "0123456789.")) return true;

    return false;
}

int tokenize(std::string line, Instruction& inst)
{
    std::stringstream ss(line);
    std::string tok;
    std::vector<std::string> tokens;
    std::string type;
    std::string value;

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

