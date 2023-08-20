#pragma once

#include <vector>
#include <string>
#include <exception>
#include <format>

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
    SomeError(const std::string &) noexcept;
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

template <>
struct std::formatter<lexer::Position> : std::formatter<std::string> {
    auto format(const lexer::Position &p, std::format_context &ctx) const {
        return std::formatter<std::string>::format(std::format("{}:{}",
            p.line, p.column), ctx);
    }
};