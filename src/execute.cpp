
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

    auto it = cmdMap.find(instruction);
    if (it != cmdMap.end()) {
        return it->second; // key:value, second = value = enum
    } else {
        return Cmd::Error;
    }
}


int execute(std::vector<Instruction> commands) 
{
    // execute the command here
    std::list <Number> stack;

    for (int i = 0; i < commands.size(); i++) {
        Cmd cmd = stringToCmd(commands[i].getCommand());
        switch (cmd) {
            case Cmd::Push:
                executePush(stack, commands[i].getType(), commands[i].getValue());
            case Cmd::Assert:
                executeAssert(stack, commands[i].getType(), commands[i].getValue());
            case Cmd::Pop:
                stack.pop_front();
                // TODO Add error message if stack is empty
            case Cmd::Dump:
                // Display each value in stack, most recent to oldest, separated by a newline.
            case Cmd::Add:
                // pop top 2 numbers and add, handle precision diff if any
            case Cmd::Sub:
            case Cmd::Mul:
            case Cmd::Div:
            case Cmd::Mod:
            case Cmd::Print:
                //Verifies that the value at the top of the stack is an 8 bits integer. 
                // (If not, see the instruction assert), then interprets it as an ASCII value and 
                // displays the corresponding character on the standard output. ????
            case Cmd::Error:
                std::cerr << "Invalid command string passed to execute()" << std::endl;
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int executePush(std::list <Number> stk, std::string typ, std::string val)
{
    // How do we add the numbers using the IOperand interface???
}

int executeAssert(std::list <Number> stk, std::string typ, std::string val)
{
    
}