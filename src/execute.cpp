
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
    OperandFactory factory;

    // Create Operand using factory pattern
    IOperand* operand = factory.createOperand(type, val);
    
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

    OperandFactory factory;
    IOperand* operand = nullptr;
    /* 
       For non commutative operations, you must consider for the following stack: 
       v1 on v2, the calculation in infix notation: v2 op v1.
    */ 
    IOperand* rhs = stk.front(); // store v1 in the rhs
    stk.pop_front();
    IOperand* lhs = stk.front(); // store v2 in the lhs
    stk.pop_front();

    // Check for precision
    // Turn the operand that is a lower precision into the higher one
    if (lhs->getType() != rhs->getType()) {
        if (!lhsIsMostPrecise(lhs, rhs)) {
            eOperandType e = rhs->getType();
            lhs = factory.createOperand(e, lhs->toString());
        } else {
            eOperandType e = lhs->getType();
            rhs = factory.createOperand(e, rhs->toString());
        }
    }

    if (op == Cmd::Add) operand = *lhs + *rhs;
    else if (op == Cmd::Sub) operand = *lhs - *rhs;
    else if (op == Cmd::Mul) operand = *lhs * *rhs;
    else if (op == Cmd::Div) operand = *lhs / *rhs;
    else if (op == Cmd::Mod) operand = *lhs % *rhs;

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
