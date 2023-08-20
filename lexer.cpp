#include <string.h>
#include <format>

#include "lexer.hpp"

namespace lexer {
Position::operator std::string() const {
    return std::format("{}:{}", line, column);
}

SomeError::SomeError(const std::string &message) noexcept : message(message) {}

const char *SomeError::what() const noexcept {
    return message.c_str();
}

Token::Token(Position position, TokenType type, const std::string &value)
    noexcept : position(position), type(type), value(value) {}

std::vector<Token> lex(const std::string &source) noexcept {
    std::vector<Token> tokens;
    Position position;
    for (char c : source) {
        position.column++;
        switch (c) {
            case '[':
            case ']':
            tokens.push_back(Token(position, TokenType::Separator, std::string(1, c)));
            break;

            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            tokens.push_back(Token(position, TokenType::Operator, std::string(1, c)));
            break;

            case '\n':
            position.line++;
            position.column = 0;
        }
    }
    return tokens;
}
}