
#include "../inc/main.hpp"



int main(int argc, char* argv[])
{
    t_node command = {"temp", 0, 0, NULL};
    const t_node* cmdPtr = &command;

    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return EXIT_FAILURE;  
    } else if (argc > 1) {
        parse(argv[1], cmdPtr);
    } else {
        parse(NULL, cmdPtr);
    }



    return EXIT_SUCCESS;
}

