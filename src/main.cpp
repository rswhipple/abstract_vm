
#include "../inc/main.hpp"

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

int main(int argc, char* argv[])
{
    try { 
        if (argc > 2) errorHandler(errorType::usage);
        else if (argc > 1) {
            int result = readFile(argv[1]);
            if (result != 0) errorHandler(static_cast<errorType>(result));
        } else {
            int result = readFromStdin();
            if (result != 0) errorHandler(static_cast<errorType>(result));
        }
    } catch (const AvmException& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
