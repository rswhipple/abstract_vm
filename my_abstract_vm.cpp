#include <iostream>
using namespace std;


template <typename T> class IOperand
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
