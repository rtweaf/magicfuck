#pragma once

#include <vector>

#include "lexer.hpp"

namespace parser {
enum NodeType {
    Loop,
    IncrementPtr, DecrementPtr,
    Increment, Decrement,
    Write, Read
};

class Node {
    public:
    const lexer::Position position;
    const NodeType type;
    const std::vector<Node> children;

    Node(lexer::Position position, NodeType type) noexcept;
    Node(lexer::Position position, NodeType type, std::vector<Node> children)
        noexcept(noexcept(type == NodeType::Loop));
};

std::vector<Node> parse(std::vector<lexer::Token> tokens) noexcept(false);
}