#ifndef TYPES_HPP
#define TYPES_HPP


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
    IOperand _createint8(const std::string& value) {}
    IOperand _createint16(const std::string& value) {}
    IOperand _createint32(const std::string& value) {}
    IOperand _createFloat(const std::string& value) {}
    IOperand _createDouble(const std::string& value) {}

    typedef (*CreateOperand)(const std::string&);

    CreateOperand createOperand[] = {_createint8, _createint16, _createint32, _createFloat, _createDouble};    

  public:
    IOperand * createOperand(eOperandType type, const std::string& value) {}

}

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

class Int8: public IOperand
{
private:
	int8_t value;
	std::string strValue;

public:
	Int8(int8_t val) : value(val), strValue(std::to_string(val)) {}

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

class Int16: IOperand
{
private:
	int16_t value;
	std::string strValue;

public:
	Int16(int16_t val) : value(val), strValue(std::to_string(val)) {}

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

class Int32: IOperand
{
private:
	int32_t value;
	std::string strValue;

public:
	Int32(int32_t val) : value(val), strValue(std::to_string(val)) {}

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

class Float: IOperand
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

class Double: IOperand
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
