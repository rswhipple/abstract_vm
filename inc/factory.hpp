#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "ioperand.hpp"
#include <array>


// Factory pattern to manage creation of IOperand instances
class OperandFactory {
public:
    using CreateOperandFunc = IOperand* (*)(const std::string&);
    
    static const std::array<CreateOperandFunc, 5> constructors;
    
    IOperand* createOperand(eOperandType type, const std::string& value) const {
        return constructors[static_cast<size_t>(type)](value);
    }

private:
    static IOperand* _createInt8(const std::string& value) {
        int8_t val = static_cast<int8_t>(std::stoi(value));
        return new Operand<int8_t, eOperandType::Int8>(val);
    }

    static IOperand* _createInt16(const std::string& value) {
        int16_t val = static_cast<int16_t>(std::stoi(value));
        return new Operand<int16_t, eOperandType::Int16>(val);
    }

    static IOperand* _createInt32(const std::string& value) {
        int32_t val = static_cast<int32_t>(std::stoi(value));
        return new Operand<int32_t, eOperandType::Int32>(val);
    }

    static IOperand* _createFloat(const std::string& value) {
        float val = std::stof(value);
        return new Operand<float, eOperandType::Float>(val);
    }

    static IOperand* _createDouble(const std::string& value) {
        double val = std::stod(value);
        return new Operand<double, eOperandType::Double>(val);
    }
};


#endif
