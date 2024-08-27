#include <stdlib.h>

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

bool startsWithAny(const std::string& str, const std::unordered_set<std::string>& prefixes) {
  for (const auto& prefix : prefixes) {
    if (str.find(prefix) == 0) {
      return true;
    }
  }
  return false;
}

int isValidInstruction(const std::string& line){

  int spaceCount;
  if ((spaceCount = std::count(line.begin(), line.end(), ' ')) > 1){
    std::cerr << "Error: Invalid instruction" << std::endl;
    return 1;
  }
 
	std::string str1, str2;
	std::stringstream ss(line);
	ss >> str1;

	if (instructionList.find(str1) != instructionList.end()) {

		if (str1 != "push" && str1 != "assert" && spaceCount < 1) {
			std::cout << "Complete instruction: " << str1 << std::endl;
			return 0;
		}

    ss >> str2;
    if (startsWithAny(str2, valueList)) {
      std::cout << "Complete instruction: " << str1 << str2 << std::endl;
      return 0;
    } else {
      std::cerr << "Error: Invalid instruction" << std::endl;
      return 1;
    }
    
	}

  std::cerr << "Error: Invalid instruction" << std::endl;
  return 1; 
}

int readFromStdin() 
{
	while (1)
	{
		std::string input;
		std::getline(std::cin, input);
    if (isValidInstruction(input)) {
      return 1;
    }
	}
	return 0;
}

int readFromFile(const std::string& fileName){
  std::cout << "The name of the file is " << fileName << std::endl;
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
        readFromFile(argv[1]);
    } else {
        readFromStdin();
    }

    return EXIT_SUCCESS;
}

