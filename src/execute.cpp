
#include "../inc/main.hpp"


Cmd stringToCmd(const std::string& instruction) {
    static const std::unordered_map<std::string, Cmd> cmdMap = {
        {"push", Cmd::Push},
        {"assert", Cmd::Assert},
        {"pop", Cmd::Pop},
        {"dump", Cmd::Dump},
        {"add", Cmd::Add},
        {"sub", Cmd::Sub},
        {"mul", Cmd::Mul},
        {"div", Cmd::Div},
        {"mod", Cmd::Mod},
        {"print", Cmd::Print},
    };

    auto iterator = cmdMap.find(instruction);
    if (iterator != cmdMap.end()) {
        return iterator->second; // key:value, second = value = enum
    } else {
        return Cmd::Error;
    }
}


void printLineNumber(int lineNumber){
    std::cout << "Line " << lineNumber + 1 << " : ";
}


int execute(std::vector<Instruction>& commands) 
{
    // execute the command here
    std::list <IOperand*> stack;
    int lineNumber = 0;
    for (; lineNumber < static_cast<int>(commands.size()); lineNumber++) {
        Cmd cmd = stringToCmd(commands[lineNumber].getCommand());
        switch (cmd) {
            case Cmd::Push:
                executePush(stack, commands[lineNumber].getType(), commands[lineNumber].getValue());
                break;
            case Cmd::Assert:
                if ((executeAssert(stack, commands[lineNumber].getType(), commands[lineNumber].getValue())) != 0){
                    printLineNumber(lineNumber);
                    return 8; 
                }
                break;
            case Cmd::Pop:
                if (stack.empty()) {
                    printLineNumber(lineNumber);
                    return 5;  // errorType::emptyStack
                }
                stack.pop_front();
                break;
            case Cmd::Dump:
                executeDump(stack);
                break;
            case Cmd::Print:
                // Verifies that the value at the top of the stack is an 8 bits integer. 
                // (If not, see the instruction assert), then interprets it as an ASCII value and 
                // displays the corresponding character on the standard output. ????
            case Cmd::Error:
                printLineNumber(lineNumber);
                return 3;   // errorType::instruction
            default:
                int result = executeArithmetic(stack, cmd);
                if (result) {
                    printLineNumber(lineNumber);
                    return result;
                }
        }
    }

    return EXIT_SUCCESS;
}

void executeDump(std::list<IOperand*>& stk) 
{
    // Display each value in stack, most recent to oldest, separated by a newline.
    for (const auto& op : stk) {
        IOperand& operandRef = *op;
        std::cout << operandRef.toString() << std::endl; 
    }
}

int executePush(std::list<IOperand*>& stk, std::string typ, std::string val)
{
    eOperandType type = stringToType(typ);
    IOperand* operand = nullptr;

    if (type == eOperandType::Int8)
        operand = new Operand<int8_t, eOperandType::Int8>(static_cast<int8_t>(std::stoi(val)));
    else if (type == eOperandType::Int16)
        operand = new Operand<int16_t, eOperandType::Int16>(static_cast<int16_t>(std::stoi(val)));
    else if (type == eOperandType::Int32)
        operand = new Operand<int32_t, eOperandType::Int32>(static_cast<int32_t>(std::stoi(val)));
    else if (type == eOperandType::Float)
        operand = new Operand<float, eOperandType::Float>(std::stof(val));
    else if (type == eOperandType::Double)
        operand = new Operand<double, eOperandType::Double>(std::stod(val));
    else errorHandler(errorType::invalidArg);
    
    stk.push_front(operand);
    // std::cout << stk.front()->toString() << std::endl;               // logging
    // std::cout << "Pushed: " << operand->toString() << std::endl;     // logging

    return EXIT_SUCCESS;
}

int executeAssert(std::list<IOperand*>& stk, std::string typ, std::string val)
{
    if (stk.front()->toString() == val && stk.front()->getType() == stringToType(typ)) return EXIT_SUCCESS;

    // (void)stk;
    // (void)typ;
    // (void)val;
    return EXIT_FAILURE;
}

int executeArithmetic(std::list<IOperand*>& stk, Cmd op)
{
    if (static_cast<int>(stk.size()) < 2) return 6;   // errorType::stackUnderflow

    IOperand* operand = nullptr;
    IOperand* lhs = stk.front();
    stk.pop_front();
    IOperand* rhs = stk.front();
    stk.pop_front();

    if (op == Cmd::Add) operand = *lhs + *rhs;
    else if (op == Cmd::Sub) operand = *lhs - *rhs;
    else if (op == Cmd::Mul) operand = *lhs * *rhs;
    else if (op == Cmd::Div) operand = *lhs / *rhs;
    else if (op == Cmd::Mod) operand = *lhs % *rhs;

    // TODO add an error check here, compare regular math to operand math
    stk.push_front(operand);
    
    return EXIT_SUCCESS;
}
