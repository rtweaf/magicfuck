#include <iostream>

#include "parser.hpp"

namespace parser {
Node::Node(const lexer::Position &position, NodeType type)
    noexcept : position(position), type(type) {}

Node::Node(const lexer::Position &position, NodeType type,
    const std::vector<Node> &children) noexcept(noexcept(type == NodeType::Loop))
        : position(position), type(type), children(children) {}

std::vector<Node> parse(const std::vector<lexer::Token> &tokens) noexcept(false) {
    std::vector<Node> tree;
    static int depth = 0;
    unsigned int local_i = 0;
    static unsigned int i = 0;
    for (; i<tokens.size(); ++i) {
        switch (tokens[i].value[0]) {
            case '[':
            {
                i++;
                depth++;
                lexer::Position position = tokens[i - 1].position; // compiler changed args execs order
                tree.push_back(Node(position, NodeType::Loop, parse(tokens)));
                break;
            }
        
            case ']':
            i++;
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
        throw lexer::SomeError(tokens[i - local_i].position, (char*)"Expected `]`");
    else if (depth < 0)
        throw lexer::SomeError(tree[i - local_i].position, (char*)"Unexpected `[`");

    return tree;
}
}