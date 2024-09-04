
#include "../inc/main.hpp"


int errorHandler(errorType typ)
{
    switch (typ) {
        case errorType::usage:
            throw AvmException("Usage: ./abstract_vm [filename]");
        case errorType::read:
            throw AvmException("Error: Could not read file.");
        case errorType::invalidArg:
            throw AvmException("Error: Invalid instruction arg.");
        case errorType::divideByZero:
            throw AvmException("Error: Attempting to divide by 0.");
        case errorType::emptyStack:
            throw AvmException("Error: Attempting to access value on empty stack.");
        default:
            throw AvmException("Error: Unknown error.");
    }

    return EXIT_FAILURE;

}