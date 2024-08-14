
#include "../inc/main.hpp"


void readFile(const std:: string& filename, const t_node*& cmdPtr)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file" << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        strToNode(line);
        std::cout << line << std::endl;
    }

    file.close();
}

void readFromStdin(const t_node*& cmdPtr)
{
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
    }
}

void strToNode(std::string line)
{
    
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



