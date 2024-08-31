#ifndef TYPES_HPP
#define TYPES_HPP

#include <iostream>

template <typename T>
void mark_unused(T&&) {}

extern const std::array<std::string, 12> instructionList;

extern const std::array<std::string, 5> valueList;

class Instruction {
private:
    std::string command;
    std::string type;
    std::string value;

public:
	// Constructor
	Instruction(const std::string& cmd, const std::string& typ,
		const std::string& val)
		: command(cmd), type(typ), value(val) {}

	std::string getCommand() const { return command; }
	void setCommand(const std::string& cmd) { command = cmd; }

	std::string getType() const { return type; }
	void setType(const std::string& typ) { type = typ; }

	std::string getValue() const { return value; }
	void setValue(const std::string& val) { value = val; }
};

enum class eOperandType
{
  int8,
  int16,
  int32,
  Float,
  Double,
};


// future iteration: using a template
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

// class int8: public IOperand
// {
// private:
// 	int8_t value;
// 	std::string strValue;

// public:
// 	int8(int8_t val) : value(val), strValue(std::to_string(val)) {}

// 	std::string const & toString() const override {
// 		return strValue;
// 	}

// 	// int getPrecision() const override {}
// 	// eOperandType getType() const override {}

// 	IOperand * operator+(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator-(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator*(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator/(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator%(const IOperand &rhs) const override {
// 		return nullptr;
// 	}

// };

// class int16: public IOperand
// {
// private:
// 	int16_t value;
// 	std::string strValue;

// public:
// 	int16(int16_t val) : value(val), strValue(std::to_string(val)) {}

// 	std::string const& toString() const override {
// 		return strValue;
// 	}

// 	int getPrecision() const override {}
// 	eOperandType getType() const override {}

// 	IOperand * operator+(const IOperand &rhs) const override {}
// 	IOperand * operator-(const IOperand &rhs) const override {}
// 	IOperand * operator*(const IOperand &rhs) const override {}
// 	IOperand * operator/(const IOperand &rhs) const override {}
// 	IOperand * operator%(const IOperand &rhs) const override {}

// };

// class int32: public IOperand
// {
// private:
// 	int32_t value;
// 	std::string strValue;

// public:
// 	int32(int32_t val) : value(val), strValue(std::to_string(val)) {}

// 	std::string const& toString() const override {
// 		return strValue;
// 	}

// 	int getPrecision() const override {}
// 	eOperandType getType() const override {}

// 	IOperand * operator+(const IOperand &rhs) const override {}
// 	IOperand * operator-(const IOperand &rhs) const override {}
// 	IOperand * operator*(const IOperand &rhs) const override {}
// 	IOperand * operator/(const IOperand &rhs) const override {}
// 	IOperand * operator%(const IOperand &rhs) const override {}

// };

// class Float: public IOperand
// {
// private:
// 	float value;
// 	std::string strValue;

// public:
// 	Float(float val) : value(val), strValue(std::to_string(val)) {}

// 	std::string const& toString() const override {
// 		return strValue;
// 	}

// 	int getPrecision() const override {}
// 	eOperandType getType() const override {}

// 	IOperand * operator+(const IOperand &rhs) const override {}
// 	IOperand * operator-(const IOperand &rhs) const override {}
// 	IOperand * operator*(const IOperand &rhs) const override {}
// 	IOperand * operator/(const IOperand &rhs) const override {}
// 	IOperand * operator%(const IOperand &rhs) const override {}

// };

// class Double: public IOperand
// {
// private:
// 	double value;
// 	std::string strValue;

// public:
// 	Double(double val) : value(val), strValue(std::to_string(val)) {}

// 	std::string const& toString() const override {
// 		return strValue;
// 	}

// 	int getPrecision() const override { return EXIT_FAILURE; }
// 	eOperandType getType() const override {}

// 	IOperand * operator+(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator-(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator*(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator/(const IOperand &rhs) const override {
// 		return nullptr;
// 	}
// 	IOperand * operator%(const IOperand &rhs) const override {
// 		return nullptr;
// 	}

// };

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


// class Int8 : public IOperand {
//   private:
//     int8_t value;
//     std::string strValue;

//   public:
//     Int8(int8_t val) : value(val), strValue(std::to_string(val)) {}

//     std::string const& toString() const override {
//       return strValue;
//     }

//     int getPrecision() const override {
//       return eOperandType::Int8;
//     }

//     eOperandType getType() const override {
//       return eOperandType::Int8;
//     }

//     IOperand* operator+(const IOperand& rhs) const override {
//      // Assuming rhs is Int8 for simplicity; we'll need to handle other cases
//     if (rhs.getType() != eOperandType::Int8)
//       throw std::invalid_argument("Type mismatch");

//     int8_t result = value + static_cast<const Int8&>(rhs).value;
//     return std::make_unique<Int8>(result); 
//     }

//     IOperand* operator-(const IOperand& rhs) const override {}
//     IOperand* operator*(const IOperand& rhs) const override {}
//     IOperand* operator/(const IOperand& rhs) const override {}
//     IOperand* operator%(const IOperand& rhs) const override {}

// };
