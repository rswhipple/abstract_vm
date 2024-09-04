
#include "../inc/main.hpp"


eOperandType stringToType(const std::string& typStr) {
    if (typStr == "int8") return eOperandType::Int8;
    else if (typStr == "int16") return eOperandType::Int16;
    else if (typStr == "int32") return eOperandType::Int32;
    else if (typStr == "float") return eOperandType::Float;
    else if (typStr == "double") return eOperandType::Double;
    else errorHandler(errorType::invalidArg);
}