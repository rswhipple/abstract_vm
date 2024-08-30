#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <algorithm>
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
        if (readFile(argv[1], cmdPtr) != 0) return EXIT_FAILURE;
    } else {
        if (readFromStdin(cmdPtr) != 0) return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
