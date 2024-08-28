#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <algorithm>

std::unordered_set<std::string> instructionList =
{
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
	";;"
};

std::unordered_set<std::string> valueList =
{
  "int8",
  "int16",
  "int32",
  "float",
  "double"
};

// improve this later
bool isValidValue(const std::string& str, const std::unordered_set<std::string>& prefixes) {
  for (const auto& prefix : prefixes) {
    if (str.find(prefix) == 0) {
      return true;
    }
  }
  return false;
}

bool isValidInstruction(const std::string& line) {

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

int readFromStdin() 
{
	while (1) {
		std::string input;
		std::getline(std::cin, input);
		if (input == ";;") {
		  return 0;
		}
    if (!isValidInstruction(input)) {
      return 1;
    }
    // run instruction here
  }
	return 0;
}

int readFromFile(const std::string& fileName){
  std::ifstream inputFile(fileName);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    if (line == "exit") {
      return 0;
    }
    if (!isValidInstruction(line)) {
      return 1;
    }
    // run instruction here
  }
  return 0;
}

int main(int argc, char* argv[])
{
    // t_node command = {"temp", 0, 0, NULL};
    // const t_node* cmdPtr = &command;

    // return EXIT_SUCCESS;

    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return EXIT_FAILURE;  
    } else if (argc > 1) {
        if (readFromFile(argv[1]) != 0) {
          return EXIT_FAILURE;
        }
    } else {
        if (readFromStdin() != 0) {
          return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

