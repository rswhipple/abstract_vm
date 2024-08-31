
#include "../inc/main.hpp"


int readFile(const std:: string& filename)
{
    // Open file stream
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file" << filename << std::endl;
        return EXIT_FAILURE;
    }

    // Instanciate Instruction obj + create vector to store all instructions.
    std::vector<Instruction> commands;
    Instruction inst = {"temp", "temp", "temp"};

    // Parse program line by line
    std::string line;
    while (std::getline(file, line)) {
        if (line == "exit") {
            file.close();
            // Execute all commands
            if (executeCmd(commands) != 0) return EXIT_FAILURE;
            return EXIT_SUCCESS;
        }
        if (!isValidInstruction(line)) return EXIT_FAILURE;
        if (tokenize(line, inst) != 0) return EXIT_FAILURE;
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
            if (executeCmd(commands) != 0) return EXIT_FAILURE;
            return EXIT_SUCCESS;
        }
        if (!isValidInstruction(line)) return EXIT_FAILURE;
        if (tokenize(line, inst) != 0) return EXIT_FAILURE;
        if (inst.getCommand() == ";") continue;     // Skips comments.
        commands.emplace_back(inst);    // Store current inst in vector.
    }
    return EXIT_FAILURE;
}


// improve this later ?
bool isValidValue(const std::string& str, const std::array<std::string, 5>& prefixes) 
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

bool isValidInstruction(const std::string& line) 
{
    int spaceCount;
    if ((spaceCount = std::count(line.begin(), line.end(), ' ')) > 1){
        std::cerr << "Error: Invalid instruction" << std::endl;
        return false;
    }
    
    std::string str1, str2;
    std::stringstream ss(line);
    ss >> str1;

    if (isValidCommand(str1, instructionList)) {
        if (str1 == "push" || str1 == "assert") {
            ss >> str2;
            if (isValidValue(str2, valueList)) {
                std::cout << "Valid instruction: " << str1 << " " << str2 << std::endl;
                return true;
            }
        } else if (str1 == ";") {
            std::cout << "Valid instruction: " << str1 << std::endl;
            return true;
        } else if (spaceCount == 0 ) {
            std::cout << "Valid instruction: " << str1 << std::endl;
            return true;
        }
    }
    std::cerr << "Error: Invalid instruction" << std::endl;
    return false;
}

bool splitTypeValue (const std::string& input, std::string& type, std::string& value)
{
    size_t open = input.find('(');
    size_t close = input.find(')', open);

    if (open != std::string::npos && close != std::string::npos && close > open) {
        type = input.substr(0, open);    // Text before '('
        value = input.substr(open + 1, close - open - 1); // Text between '(' and ')'
        return true;
    }

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
            std::cerr << "Invalid input format." << std::endl;
            return EXIT_FAILURE;
        }
    } else {
        inst.setType("");
        inst.setValue("");
    }

    return EXIT_SUCCESS;
}

int executeCmd(std::vector<Instruction> commands) 
{
    // execute the command here
    std::list <Number> stack;
    mark_unused(commands);
    return EXIT_SUCCESS;
}
