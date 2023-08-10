#include <string.h>

#include "lexer.hpp"

namespace lexer {
Position::operator const char*() {
    char *buff = new char[1024];
    sprintf(buff, "%u:%u", line, column);
    return buff;
}

SomeError::SomeError(Position position, char *message) 
    noexcept : message(message) {
        strcat(message, position);
    }

const char *SomeError::what() const noexcept {
    return message;
}

Token::Token(Position position, TokenType type, std::string value) noexcept :
    position(position), type(type), value(value) {}

std::vector<Token> lex(std::string source) noexcept {
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
            position.column = 1;
        }
    }
    return tokens;
}
}