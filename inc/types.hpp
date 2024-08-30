#ifndef TYPES_HPP
#define TYPES_HPP

#include <unordered_set>

std::unordered_set<std::string> instructionList =
{
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
	";;"
};

std::unordered_set<std::string> valueList =
{
  "int8",
  "int16",
  "int32",
  "float",
  "double"
};

typedef struct s_node t_node;

struct t_node {
    const char* command;
    int type;
    int value;
    t_node* next;
};

enum class eOperandType
{
  int8,
  int16,
  int32,
  Float,
  Double,
};

class Executor
{
  private:
	IOperand* _createint8(const std::string& value) {}
	IOperand* _createint16(const std::string& value) {}
	IOperand* _createint32(const std::string& value) {}
	IOperand* _createFloat(const std::string& value) {}
	IOperand* _createDouble(const std::string& value) {}

	typedef IOperand* (Executor::*CreateOperand)(const std::string&);

	// Array of member function pointers
	std::array<CreateOperand, 5> createOperand = {
		&Executor::_createint8,
		&Executor::_createint16,
		&Executor::_createint32,
		&Executor::_createFloat,
		&Executor::_createDouble
	}; 

  public:
	IOperand* createOperand(eOperandType type, const std::string& value) {
			return (this->*createOperand[static_cast<size_t>(type)])(value);
		}

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

class int8: public IOperand
{
private:
	int8_t value;
	std::string strValue;

public:
	int8(int8_t val) : value(val), strValue(std::to_string(val)) {}

	std::string const & toString() const override {
		return strValue;
	}

	int getPrecision() const override {}
	eOperandType getType() const override {}

	IOperand * operator+(const IOperand &rhs) const override {}
	IOperand * operator-(const IOperand &rhs) const override {}
	IOperand * operator*(const IOperand &rhs) const override {}
	IOperand * operator/(const IOperand &rhs) const override {}
	IOperand * operator%(const IOperand &rhs) const override {}

};

class int16: public IOperand
{
private:
	int16_t value;
	std::string strValue;

public:
	int16(int16_t val) : value(val), strValue(std::to_string(val)) {}

	std::string const& toString() const override {
		return strValue;
	}

	int getPrecision() const override {}
	eOperandType getType() const override {}

	IOperand * operator+(const IOperand &rhs) const override {}
	IOperand * operator-(const IOperand &rhs) const override {}
	IOperand * operator*(const IOperand &rhs) const override {}
	IOperand * operator/(const IOperand &rhs) const override {}
	IOperand * operator%(const IOperand &rhs) const override {}

};

class int32: public IOperand
{
private:
	int32_t value;
	std::string strValue;

public:
	int32(int32_t val) : value(val), strValue(std::to_string(val)) {}

	std::string const& toString() const override {
		return strValue;
	}

	int getPrecision() const override {}
	eOperandType getType() const override {}

	IOperand * operator+(const IOperand &rhs) const override {}
	IOperand * operator-(const IOperand &rhs) const override {}
	IOperand * operator*(const IOperand &rhs) const override {}
	IOperand * operator/(const IOperand &rhs) const override {}
	IOperand * operator%(const IOperand &rhs) const override {}

};

class Float: public IOperand
{
private:
	float value;
	std::string strValue;

public:
	Float(float val) : value(val), strValue(std::to_string(val)) {}

	std::string const& toString() const override {
		return strValue;
	}

	int getPrecision() const override {}
	eOperandType getType() const override {}

	IOperand * operator+(const IOperand &rhs) const override {}
	IOperand * operator-(const IOperand &rhs) const override {}
	IOperand * operator*(const IOperand &rhs) const override {}
	IOperand * operator/(const IOperand &rhs) const override {}
	IOperand * operator%(const IOperand &rhs) const override {}

};

class Double: public IOperand
{
private:
	double value;
	std::string strValue;

public:
	Double(double val) : value(val), strValue(std::to_string(val)) {}

	std::string const& toString() const override {
		return strValue;
	}

	int getPrecision() const override {}
	eOperandType getType() const override {}

	IOperand * operator+(const IOperand &rhs) const override {}
	IOperand * operator-(const IOperand &rhs) const override {}
	IOperand * operator*(const IOperand &rhs) const override {}
	IOperand * operator/(const IOperand &rhs) const override {}
	IOperand * operator%(const IOperand &rhs) const override {}

};


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