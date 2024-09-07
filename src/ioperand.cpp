
#include "../inc/main.hpp"


eOperandType stringToType(const std::string& typStr) {
    if (typStr == "int8") return eOperandType::Int8;
    else if (typStr == "int16") return eOperandType::Int16;
    else if (typStr == "int32") return eOperandType::Int32;
    else if (typStr == "float") return eOperandType::Float;
    else return eOperandType::Double;
    // No error handling here, is there a way to fix? 
    // Can't return a nullptr, don't want to create an enum just for errors
}

bool lhsIsMostPrecise(IOperand* lhs, IOperand* rhs) {
    if (lhs->getPrecision() > rhs->getPrecision()) return true;
    return false;
}