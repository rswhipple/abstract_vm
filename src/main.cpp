
#include "../inc/main.hpp"



int main(int argc, char* argv[])
{
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return EXIT_FAILURE;  
    } else if (argc > 1) {
        parse(argv[1]);
    } else {
        parse(NULL);
    }

    return EXIT_SUCCESS;
}

