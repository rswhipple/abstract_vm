
#include "../inc/main.hpp"



int main(int argc, char* argv[])
{
    t_node command = {"temp", 0, 0, NULL};
    const t_node* cmdPtr = &command;

    return EXIT_SUCCESS;
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return EXIT_FAILURE;  
    } else if (argc > 1) {
        readFile(argv[1], cmdPtr);
    } else {
        readFromStdin(cmdPtr);
    }



    return EXIT_SUCCESS;
}

