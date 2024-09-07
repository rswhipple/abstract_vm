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

eOperandType stringToType(const std::string& typStr);


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

/*
Operand template:
    Handles all possible IOperand types, with 2 noted exceptions.
    Float and Double have specialized classes because they do not have a 
    functional modulo '%' operator.
*/
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
	IOperand * operator%(const IOperand &rhs) const override {
		T rhsValue = static_cast<T>(std::stod(rhs.toString()));
        if (rhsValue == 0) throw std::runtime_error("Mod by zero");
		return new Operand(value % rhsValue);
	}

};


template <>
class Operand<float, eOperandType::Float> : public IOperand
{
private:
	float value;
	std::string strValue;

public:
    Operand(float val) : value(val), strValue(std::to_string(val)) {}

	std::string const & toString() const override {
		return strValue;
	}

	int getPrecision() const override {
		return static_cast<int>(sizeof(float) * 8);
	}
	eOperandType getType() const override {
		return eOperandType::Float;
	}

	IOperand * operator+(const IOperand &rhs) const override {
		float rhsValue = static_cast<float>(std::stod(rhs.toString()));
		return new Operand(value + rhsValue);
	}

	IOperand * operator-(const IOperand &rhs) const override {
		float rhsValue = static_cast<float>(std::stod(rhs.toString()));
		return new Operand(value - rhsValue);
	}
	IOperand * operator*(const IOperand &rhs) const override {
		float rhsValue = static_cast<float>(std::stod(rhs.toString()));
		return new Operand(value * rhsValue);
	}
	IOperand * operator/(const IOperand &rhs) const override {
		float rhsValue = static_cast<float>(std::stod(rhs.toString()));
        if (rhsValue == 0) throw std::runtime_error("Division by zero");
		return new Operand(value / rhsValue);
	}
    IOperand * operator%(const IOperand &rhs) const override {
        (void)rhs;
        const std::string message = 
            "Error: invalid operands of type 'float' to binary 'operator%'";
		throw std::runtime_error(message);
		return nullptr;
	}
};


template <>
class Operand<double, eOperandType::Double> : public IOperand
{
private:
	float value;
	std::string strValue;

public:
    Operand(double val) : value(val), strValue(std::to_string(val)) {}

	std::string const & toString() const override {
		return strValue;
	}

	int getPrecision() const override {
		return static_cast<int>(sizeof(double) * 8);
	}
	eOperandType getType() const override {
		return eOperandType::Double;
	}

	IOperand * operator+(const IOperand &rhs) const override {
		double rhsValue = static_cast<double>(std::stod(rhs.toString()));
		return new Operand(value + rhsValue);
	}

	IOperand * operator-(const IOperand &rhs) const override {
		double rhsValue = static_cast<double>(std::stod(rhs.toString()));
		return new Operand(value - rhsValue);
	}
	IOperand * operator*(const IOperand &rhs) const override {
		double rhsValue = static_cast<double>(std::stod(rhs.toString()));
		return new Operand(value * rhsValue);
	}
	IOperand * operator/(const IOperand &rhs) const override {
		double rhsValue = static_cast<double>(std::stod(rhs.toString()));
        if (rhsValue == 0) throw std::runtime_error("Division by zero");
		return new Operand(value / rhsValue);
	}
    IOperand * operator%(const IOperand &rhs) const override {
        (void)rhs;
        const std::string message = 
            "Error: invalid operands of type 'float' to binary 'operator%'";
		throw std::runtime_error(message);
		return nullptr;
	}
};

// Overload << operator for use with cout
template <typename T, eOperandType OperandType>
std::ostream& operator<<(std::ostream& os, const Operand<T, OperandType>& operand) {
    os << operand.toString();
    return os;
};


#endif
