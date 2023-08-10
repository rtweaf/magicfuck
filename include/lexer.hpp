#pragma once

#include <vector>
#include <string>
#include <exception>

namespace lexer {
class Position {
    public:
    unsigned int line = 1;
    unsigned int column = 0;

    operator const char*();
};

class SomeError : public std::exception {
    char *message;
    
    public:
    SomeError(Position position, char *message) noexcept;
    const char *what() const noexcept;
};

enum TokenType {
    Separator,
    Operator
};

class Token {
    public:
    const Position position;
    const TokenType type;
    const std::string value;

    Token(Position position, TokenType type, std::string value) noexcept;
};

std::vector<Token> lex(std::string source) noexcept;
}