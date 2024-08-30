
#include "../inc/main.hpp"


int readFile(const std:: string& filename, const t_node*& cmdPtr)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file" << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "exit") {
            file.close();
            return EXIT_SUCCESS;
        }
        if (!isValidInstruction(line)) {
            return EXIT_FAILURE;
        }
        strToNode(line);
        std::cout << line << std::endl;
    }

    file.close();
    return EXIT_SUCCESS;
}

int readFromStdin(const t_node*& cmdPtr)
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ";;") {
		  return EXIT_SUCCESS;
		}
        if (!isValidInstruction(line)) {
            return EXIT_FAILURE;
        }
        strToNode(line);
        std::cout << line << std::endl;
    }
    return EXIT_SUCCESS;
}

void strToNode(std::string line)
{
    
}

// improve this later
bool isValidValue(const std::string& str, const std::unordered_set<std::string>& prefixes) 
{
    for (const auto& prefix : prefixes) {
        if (str.find(prefix) == 0) {
        return true;
        }
    }
    return false;
}

bool isValidInstruction(const std::string& line) 
{
    int spaceCount;
    if ((spaceCount = std::count(line.begin(), line.end(), ' ')) > 1){
        std::cerr << "Error: Invalid instruction" << std::endl;
        return false;
    }
    
        std::string str1, str2;
        std::stringstream ss(line);
        ss >> str1;

        if (instructionList.find(str1) != instructionList.end()) {

            if (str1 == "push" || str1 == "assert") {
            ss >> str2;
            if (isValidValue(str2, valueList)) {
            std::cout << "Valid instruction: " << str1 << " " << str2 << std::endl;
            return true;
            }
            } else if (spaceCount == 0) {
        std::cout << "Valid instruction: " << str1 << std::endl;
        return true;
        }
        
        }
    std::cerr << "Error: Invalid instruction" << std::endl;
    return false;
}



// t_node *read_file(FILE *fp, t_header **header, t_prog_size *size) {
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t nread;
//     t_node *head = NULL;

//     while ((nread = getline(&line, &len, fp)) != -1) {
//         if (my_strncmp(line, NAME_CMD_STRING, 5) == 0) { 
//             remove_line_title((*header)->prog_name, line, 7);
//         }
//         else if (my_strncmp(line, COMMENT_CMD_STRING, 8) == 0) { 
//             remove_line_title((*header)->comment, line, 10);
//         } 
//         else if (nread == 1 || my_strncmp(line, "/n", 1) == 0) {
//             continue;
//         } 
//         else {
//             size->num_inst++;
//             if (line[nread - 1] == '\n') line[nread - 1] = '\0';

//             if (!head) {
//                 head = string_to_node(line, size);
//                 head->id = size->num_inst;
//             } else {
//                 t_node *tmp = head;
//                 while (tmp->next) tmp = tmp->next;
//                 tmp->next = string_to_node(line, size);
//                 tmp->next->id = size->num_inst;

//                 // calculate offset
//                 if (tmp->next->id == 2) {
//                     tmp->next->offset += tmp->num_bytes;
//                 } else {
//                     tmp->next->offset += tmp->num_bytes + tmp->offset;
//                 }
//             }
//         }
//     }
//     print_nodes(head);  // TESTING
//     return head;
// }



