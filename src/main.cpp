
#include "../inc/main.hpp"

const std::array<std::string, 12> instructionList = {
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

const std::array<std::string, 5> valueList = {
  "int8",
  "int16",
  "int32",
  "float",
  "double"
};

int main(int argc, char* argv[])
{
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return EXIT_FAILURE;  
    } else if (argc > 1) {
        if (readFile(argv[1]) != 0) return EXIT_FAILURE;
    } else {
        if (readFromStdin() != 0) return EXIT_FAILURE;
    } 

    return EXIT_SUCCESS;
}
