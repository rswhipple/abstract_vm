
#include "../inc/main.hpp"


int readFile(const std:: string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file" << filename << std::endl;
        return EXIT_FAILURE;
    }

    Instruction inst = {"temp", "temp", "temp"};

    std::string line;
    while (std::getline(file, line)) {
        if (line == "exit") {
            file.close();
            return EXIT_SUCCESS;
        }
        if (!isValidInstruction(line)) return EXIT_FAILURE;
        if (tokenize(line, inst) != 0) return EXIT_FAILURE;
        executeCmd(inst);
        std::cout << line << std::endl;
    }

    file.close();
    return EXIT_SUCCESS;
}

int readFromStdin()
{
    Instruction inst = {"temp", "temp", "temp"};

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ";;") return EXIT_SUCCESS;
        if (!isValidInstruction(line)) return EXIT_FAILURE;
        if (tokenize(line, inst) != 0) return EXIT_FAILURE;
        executeCmd(inst);
        std::cout << line << std::endl;
    }
    return EXIT_SUCCESS;
}


// improve this later
bool isValidValue(const std::string& str, const std::unordered_set<std::string>& prefixes) 
{
    for (const auto& prefix : prefixes) {
        if (str.find(prefix) == 0) {
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

        if (instructionList.find(str1) != instructionList.end()) {

            if (str1 == "push" || str1 == "assert") {
                ss >> str2;
                if (isValidValue(str2, valueList)) {
                    std::cout << "Valid instruction: " << str1 << " " << str2 << std::endl;
                    return true;
                }
            } else if (spaceCount == 0) {
                std::cout << "Valid instruction: " << str1 << std::endl;
                return true;
            }
        
        }
    std::cerr << "Error: Invalid instruction" << std::endl;
    return false;
}

bool splitTypeValue (const std::string& input, std::string& type, std::string& value)
{
    size_t openPos = input.find('(');
    size_t closePos = input.find('(', openPos);

    if (openPos != std::string::npos && closePos != std::string::npos && closePos > openPos) {
        type = input.substr(0, openPos);    // Text before '('
        value = input.substr(openPos + 1, closePos - openPos - 1); // Text between '(' and ')'
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

    if (splitTypeValue(tokens[1], type, value)) {
        std::cout << "Type: " << type << std::endl;
        std::cout << "Value: " << value << std::endl;
        inst.setType(type);
        inst.setValue(value);
    } else {
        std::cerr << "Invalid input format." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int executeCmd(Instruction& inst) 
{
    // execute the command here
}
