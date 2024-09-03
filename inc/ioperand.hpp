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
//   virtual IOperand *  operator%(const IOperand &rhs) const = 0;

  virtual ~IOperand() {}
};

template <typename T, eOperandType OperandType>
class Operand : public IOperand
{
private:
	T value;
	std::string strValue;

public:
	Operand(T val) : value(val), strValue(std::to_string(val)) {}

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
	// IOperand * operator%(const IOperand &rhs) const override {
	// 	T rhsValue = static_cast<T>(std::stod(rhs.toString()));
    //     if (rhsValue == 0) throw std::runtime_error("Mod by zero");
	// 	return new Operand(value % rhsValue);
	// }

};

// Overload << operator for use with cout
template <typename T, eOperandType OperandType>
std::ostream& operator<<(std::ostream& os, const Operand<T, OperandType>& operand) {
    os << operand.toString();
    return os;
}

using Int8Operand = Operand<int8_t, eOperandType::Int8>;
using Int16Operand = Operand<int16_t, eOperandType::Int16>;
using Int32Operand = Operand<int32_t, eOperandType::Int32>;
using FloatOperand = Operand<float, eOperandType::Float>;
using DoubleOperand = Operand<double, eOperandType::Double>;


using OperandVar = std::variant<Int8Operand, Int16Operand, Int32Operand, FloatOperand, DoubleOperand>;

// class Executor
// {
// private:
// 	IOperand* _createint8(const std::string& value) {}
// 	IOperand* _createint16(const std::string& value) {}
// 	IOperand* _createint32(const std::string& value) {}
// 	IOperand* _createFloat(const std::string& value) {}
// 	IOperand* _createDouble(const std::string& value) {}

// 	typedef IOperand* (Executor::*CreateOperand)(const std::string&);

// 	// Array of member function pointers
// 	std::array<CreateOperand, 5> createOperand = {
// 		&Executor::_createint8,
// 		&Executor::_createint16,
// 		&Executor::_createint32,
// 		&Executor::_createFloat,
// 		&Executor::_createDouble
// 	}; 

// public:
// 	IOperand* createOperand(eOperandType type, const std::string& value) {
// 			return (this->*createOperand[static_cast<size_t>(type)])(value);
// 		}

// };

#endif