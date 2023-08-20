#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

int main() {
    std::string line;
    std::cin >> line;
    try {
        parser::parse(lexer::lex(line));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}