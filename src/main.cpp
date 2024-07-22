#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readFile(const std:: string& filename); // Read file
void readFromStdin(); // Read from stdin

int main(int argc, char* argv[])
{
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
        return EXIT_FAILURE;  
    } else if (argc > 1) {
        readFile(argv[1]);
    } else {
        readFromStdin();
    }

    return EXIT_SUCCESS;
}

void readFile(const std:: string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file" << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

void readFromStdin()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
    }
}