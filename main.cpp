#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"
#include "executor.hpp"

int main() {
    std::string line;
    std::getline(std::cin, line);
    try {
        std::vector<char> tape = {0};
        unsigned int index = 0;
        executor::execute(std::get<0>(parser::parse(lexer::lex(line))), tape,
            index);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}