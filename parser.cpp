#include <iostream>
#include <format>
#include <tuple>

#include "parser.hpp"

namespace parser {
Node::Node(const lexer::Position &position, NodeType type)
    noexcept : position(position), type(type) {}

Node::Node(const lexer::Position &position, NodeType type,
    const std::vector<Node> &children) noexcept(noexcept(type == NodeType::Loop))
        : position(position), type(type), children(children) {}

std::tuple<std::vector<Node>, int> parse(const std::vector<lexer::Token> &tokens,
        unsigned int i, int depth) noexcept(false) {
    std::vector<Node> tree;
    unsigned int local_i = 0;

    for (; i<tokens.size(); i++) {
        switch (tokens[i].value[0]) {
            case '[':
            {
                if (!(i+1<tokens.size())) {
                    depth++;
                    break;
                }
                i++;
                lexer::Position position = tokens[i - 1].position; // compiler changed args execs order
                std::tuple<std::vector<Node>, int> parsed_loop = parse(tokens, i, 1);
                i = std::get<1>(parsed_loop);
                tree.push_back(Node(position, NodeType::Loop, std::get<0>(parsed_loop)));
                continue;
            }
        
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
    if (depth > 0 || depth < 0) 
        throw lexer::SomeError(std::format("\033[1m{}\033[0m: unmatched separator",
            tokens[i - local_i].position));

    return {tree, i};
}
}