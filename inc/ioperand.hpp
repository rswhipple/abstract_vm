#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <variant>


enum class eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double,
};

class IOperand
{
public:

  virtual std::string const & toString() const = 0;

  virtual int           getPrecision() const = 0;
  virtual eOperandType  getType() const = 0;

  virtual IOperand *  operator+(const IOperand &rhs) const = 0;
  virtual IOperand *  operator-(const IOperand &rhs) const = 0;
  virtual IOperand *  operator*(const IOperand &rhs) const = 0;
  virtual IOperand *  operator/(const IOperand &rhs) const = 0;
  virtual IOperand *  operator%(const IOperand &rhs) const = 0;

  virtual ~IOperand() {}
};


template <typename T, eOperandType OperandType>
class Operand : public IOperand
{
private:
	T value;
	std::string strValue;
	IOperand* _createint8(const std::string& value) {
        int8_t val = static_cast<int8_t>(std::stoi(value));
        return new Operand(val);
    }
	IOperand* _createint16(const std::string& value) {
        int16_t val = static_cast<int16_t>(std::stoi(value));
        return new Operand(val);
    }
	IOperand* _createint32(const std::string& value) {
        int32_t val = static_cast<int32_t>(std::stoi(value));
        return new Operand(val);
    }
	IOperand* _createFloat(const std::string& value) {
        float val = static_cast<float>(std::stof(value));
        return new Operand(val);
    }
	IOperand* _createDouble(const std::string& value) {
        double val = static_cast<double>(std::stod(value));
        return new Operand(val);
    }

    typedef IOperand* (Operand::*CreateOperand)(const std::string&);

    // Array of member function pointers
    std::array<CreateOperand, 5> constructors = {
        &Operand::_createint8,
        &Operand::_createint16,
        &Operand::_createint32,
        &Operand::_createFloat,
        &Operand::_createDouble
    };

public:
	Operand(T val) : value(val), strValue(std::to_string(val)) {}

    IOperand* createOperand(eOperandType type, const std::string& value) const {
        return (this->*constructors[static_cast<size_t>(type)])(value);
    }

    
	std::string const & toString() const override {
		return strValue;
	}

	int getPrecision() const override {
		return static_cast<int>(sizeof(T) * 8);
	}
	eOperandType getType() const override {
		return OperandType;
	}

	IOperand * operator+(const IOperand &rhs) const override {
		T rhsValue = static_cast<T>(std::stod(rhs.toString()));
		return new Operand(value + rhsValue);
	}

	IOperand * operator-(const IOperand &rhs) const override {
		T rhsValue = static_cast<T>(std::stod(rhs.toString()));
		return new Operand(value - rhsValue);
	}
	IOperand * operator*(const IOperand &rhs) const override {
		T rhsValue = static_cast<T>(std::stod(rhs.toString()));
		return new Operand(value * rhsValue);
	}
	IOperand * operator/(const IOperand &rhs) const override {
		T rhsValue = static_cast<T>(std::stod(rhs.toString()));
        if (rhsValue == 0) throw std::runtime_error("Division by zero");
		return new Operand(value / rhsValue);
	}
	IOperand * operator%(const IOperand &rhs) const override {
		T rhsValue = static_cast<T>(std::stod(rhs.toString()));
        if (rhsValue == 0) throw std::runtime_error("Mod by zero");
		return new Operand(value % rhsValue);
	}

};

// Overload << operator for use with cout
template <typename T, eOperandType OperandType>
std::ostream& operator<<(std::ostream& os, const Operand<T, OperandType>& operand) {
    os << operand.toString();
    return os;
}


eOperandType stringToType(const std::string& typStr);

#endif
