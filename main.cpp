#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

int main() {
    std::string line;
    while (std::cin >> line) {
        parser::parse(lexer::lex(line));
    }
}