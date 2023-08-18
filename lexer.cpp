#include <string.h>

#include "lexer.hpp"

namespace lexer {
Position::operator std::string() const {
    return std::to_string(line) + ":" + std::to_string(column);
}

SomeError::SomeError(const Position &position, const std::string &message) 
    noexcept : message(message) {
        this->message.insert(0, std::string(position));
    }

const char *SomeError::what() const noexcept {
    return message.c_str();
}

Token::Token(Position position, TokenType type, const std::string &value)
    noexcept : position(position), type(type), value(value) {}

std::vector<Token> lex(const std::string &source) noexcept {
    std::vector<Token> tokens;
    Position position;
    for (char c : source) {
        switch (c) {
            case '[':
            case ']':
            position.column++;
            tokens.push_back(Token(position, TokenType::Separator, std::string(1, c)));
            break;

            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            position.column++;
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