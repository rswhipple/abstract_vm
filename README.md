# abstract_vm
AbstractVM is a machine with a stack that is able to compute simple arithmetic expressions. These arithmetic expressions are provided to the machine as basic assembly programs.

Description

This is an example of an assembly program that your machine will be able to compute:
```
push int32(42)
push int32(33)

add

push float(44.55)

mul

push double(42.42)
push int32(42)

dump

pop

assert double(42.42)

exit
```
As for any assembly language, the language of MyAbstractVM is composed of a series of instructions, with one instruction per line. MyAbstractVM language has a type, which is a major difference from the others assembly languages.

Comments: Comments start with a ';' and finish with a newline. A comment can be either at the start of a line, or after an instruction.

push v: Stacks the value v at the top of the stack. The value v must have one of the following form:

int8(n): Creates an 8 bits integer with value n.
int16(n): Creates a 16 bits integer with value n.
int32(n): Creates a 32 bits integer with value n.
float(z): Creates a float with value z.
double(z): Creates a double with value z.
pop: Unstacks the value from the top of the stack. If the stack is empty, the program execution must stop with an error.

dump: Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack. Each value is separated from the next one by a newline.

assert v: Verifies that the value at the top of the stack is equal to the one passed as parameter for this instruction. If it is not the case, the program execution must stop with an error. The v has the same form that those passed as parameters to the instruction push.

add: Unstacks the first two values on the stack, adds them together and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

sub: Unstacks the first two values on the stack, subtracts them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

mul: Unstacks the first two values on the stack, multiplies them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.

div: Unstacks the first two values on the stack, divides them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover if the divisor is equal to 0, the program execution must stop with an error too.

mod: Unstacks the first two values on the stack, calculates the modulus, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover if the divisor is equal to 0, the program execution must stop with an error too.

print: Verifies that the value at the top of the stack is an 8 bits integer. (If not, see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output.

exit: Terminate the execution of the current program. If this instruction does not appears while all others instruction has been processes, the execution must stop with an error.

For non commutative operations, you must consider for the following stack: v1 on v2, the calculation in infix notation: v2 op v1.

When a calculation involves two operands from different types, the value returned has the type of the more precise operand. Please do note that because of the extensibility of the machine, the precision question is not a trivial one. This is covered more in details later in this document.

Grammar

The assembly language of MyAbstractVM is generated from the following grammar (# corresponds th the end of an entry, not to the character '#'):
```
S := [INSTR SEP]* #

INSTR :=
    push VALUE
  | pop
  | dump
  | assert VALUE
  | add
  | sub
  | mul
  | div
  | mod
  | print
  | exit

VALUE :=
   int8(N)
 | int16(N)
 | int32(N)
 | float(Z)
 | double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '
'
```
Errors

When one of the following case happens, MyAbstractVM must raise an exception and stop the execution of the program neatly. It is forbidden to raise scalar exceptions. Moreover exception classes must inherit from std::exception of the STL.

The assembly program includes one or several lexical errors or syntactic errors. An instruction is known Overflow on a value Underflow on a value Instruction pop on an empty stack Division/modulo by 0 Le program don't have an instruction exit An instruction assert is not checked The stack is composed of strictly less that two values when an arithmetic instruction is executed.

Perhaps there are others errors. However, you machine must never crash! (segfault, bus error, infinite loop ...)

You machine must be able to run programs from files passed as parameters or from the standard entry. When parameters are passed by the standard entry, the end of the program is indicated by the special symbol ;;.

Be very careful avoiding conflicts during lexical or syntactic analysis between ";;" (end of a program read on the standard input) and ; (beginning of a comment.)

Now let see some examples of execution:
```
>./avm
push int32(2)
push int32(3)
add
assert int32(5)
dump
exit
;;
5
>
>cat operation_1.avm
; -------------
; operation_1.avm -
; -------------

push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit
>./avm ./sample.avm
42
42.42
3341.25
>
>./avm
pop
;;
Line 1 : Error : Pop on empty stack
>
```
In order to help you with your code, we give you the following instructions that you have to respect. For each instruction, you must understand why this particular one is imposed. We are not providing these instructions randomly or to bore you to death!

IOperand interface

Each of your operand classes MUST implement the following IOperand interface:
```
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
```
Operand classes implementing the IOperand interface are the following ones: Int8: Representation of a signed integer coded on 8bits. Int16: Representation of a signed integer coded on 16bits. Int32: Representation of a signed integer coded on 32bits. Float: Representation of a float. Double: Representation of a double.

Important: It is FORBIDDEN to manipulate pointers or references on each of these 5 classes. You are allowed to manipulate pointers ONLY on IOperand.

Considering similarities between operand classes, it can be relevant to use template classes. However, this is not mandatory.

Creation of a new IOperand

You have to write a member function of a class relevant of your machine that will allows you to create new operands an a generic way. This function must have the following prototype:

IOperand * createOperand(eOperandType type, const std::string & value);

The type eOperandType is an enum that can accept the following values:

Int8
Int16
Int32
Float
Double
Depending on the value of the enum passed as a parameter, the member function createOperand creates a new IOperand by calling one of the following private member function:

IOperand _ createInt8(const std::string & value); IOperand _ createInt16(const std::string & value); IOperand _ createInt32(const std::string & value); IOperand _ createFloat(const std::string & value); IOperand * createDouble(const std::string & value);

In order to choose the right member function for the creation of the new IOperand, you MUST create and use an array (here, vector shows little interest) of pointers on member functions with enum values as index.

Precision

When an operation happens between two operands from the same type real, there is no problems. However, what about when the types real are different?

The usual method is to sequence types using their precision. For the machine you should use the following order: Int8 < Int16 < Int32 < Float < Double

To use this sequence for the machine, it is possible to associate an integer with each type to maintain the order, thanks to an enum for example.

The method pure getPrecision of the interface IOperand allows to get the precision of an operand. When an operation use two operands from two different types, the comparison of theirs precisions allows to figure out the result type of the operation.

For the project, the type returned is the more precise type of the two operands.

Stack

MyAbstractVM is a machine with a stack. It possesses a container behaving as a stack, or a stack itself. The choice seems obvious now, but perhaps you'll discover a subtlety later that will make you reconsider your choice.

The container must contain ONLY pointers on the abstract type IOperand! It is FORBIDDEN to store types real of operands in your container.