#pragma once

#include <vector>
#include <string>
#include <exception>

namespace lexer {
class Position {
    public:
    unsigned int line = 1;
    unsigned int column = 0;

    operator std::string() const;
    bool operator ==(const Position &) const; // for tests
};

class SomeError : public std::exception {
    std::string message;
    
    public:
    SomeError(const Position &, const std::string &) noexcept;
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

    Token(Position, TokenType, const std::string &) noexcept;
    bool operator ==(const Token &) const; // for tests
};

std::vector<Token> lex(const std::string &) noexcept;
}