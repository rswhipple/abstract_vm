
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
        {"exit", Cmd::Exit},
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
                executePrint(stack);
                break;
            case Cmd::Error:
                printLineNumber(lineNumber);
                return 3;   // errorType::instruction
            case Cmd::Exit:
                if (lineNumber < static_cast<int>(commands.size()) - 1) {
                    printLineNumber(lineNumber);
                    return 9;
                }
                break;
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

    return EXIT_SUCCESS;
}

int executeAssert(std::list<IOperand*>& stk, std::string typ, std::string val)
{
    if (stk.front()->toString() == val && stk.front()->getType() == stringToType(typ)) return EXIT_SUCCESS;

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

    // Check for precision
    // Turn the operand that is a lower precision into the higher one
    // Perform arithmetic

    /* 
       For non commutative operations, you must consider for the following stack: 
       v1 on v2, the calculation in infix notation: v2 op v1.
    */ 
    if (op == Cmd::Add) operand = *rhs + *lhs;
    else if (op == Cmd::Sub) operand = *rhs - *lhs;
    else if (op == Cmd::Mul) operand = *rhs * *lhs;
    else if (op == Cmd::Div) operand = *rhs / *lhs;
    else if (op == Cmd::Mod) operand = *rhs % *lhs;

    // TODO add an error check here, compare regular math to operand math
    stk.push_front(operand);
    
    return EXIT_SUCCESS;
}


int executePrint(std::list<IOperand*>& stk)
{
    if (stk.front()->getType() == eOperandType::Int8) {
        std::cout << stk.front()->toString() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
