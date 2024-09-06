#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <stdexcept>


enum class errorType
{
    usage = 1,
    read,
	invalidArg,
	divideByZero,
	emptyStack,
    stackUndeflow,
    binary,
    nonmatchingAssertValue,
    earlyExit
};

class AvmException : public std::runtime_error {
public:
    explicit AvmException(const std::string& message)
        : std::runtime_error(message) {}
};

int errorHandler(errorType typ);

#endif
