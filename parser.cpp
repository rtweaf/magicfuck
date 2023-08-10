#include "parser.hpp"
#include <iostream>

namespace parser {
Node::Node(lexer::Position position, NodeType type)
    noexcept : position(position), type(type) {}

Node::Node(lexer::Position position, NodeType type, std::vector<Node> children)
    noexcept(noexcept(type == NodeType::Loop)) : position(position), type(type),
        children(children) {}

std::vector<Node> parse(std::vector<lexer::Token> tokens) noexcept(false) {
    std::vector<Node> tree;
    int depth = 0;
    unsigned int local_i = 0;
    static unsigned int i = 0;
    for (; i<tokens.size(); ++i) {
        switch (tokens[i].value[0]) {
            case '[':
            i++;
            tree.push_back(Node(tokens[i].position, NodeType::Loop, parse(tokens)));
            depth++;
            break;
        
            case ']':
            depth--;
            goto end;

            case '>':
            tree.push_back(Node(tokens[i].position, NodeType::IncrementPtr));
            break;

            case '<':
            tree.push_back(Node(tokens[i].position, NodeType::DecrementPtr));
            break;

            case '+':
            tree.push_back(Node(tokens[i].position, NodeType::Increment));
            break;

            case '-':
            tree.push_back(Node(tokens[i].position, NodeType::Decrement));
            break;

            case '.':
            tree.push_back(Node(tokens[i].position, NodeType::Write));
            break;

            case ',':
            tree.push_back(Node(tokens[i].position, NodeType::Read));
            break;
        }
        local_i++;
    }

    end:
    if (depth > 0)
        throw lexer::SomeError(tree[i - local_i].position, (char*)"Expected `]`");
    else if (depth < 0)
        throw lexer::SomeError(tree[i - local_i].position, (char*)"Unexpected `[`");

    return tree;
}
}