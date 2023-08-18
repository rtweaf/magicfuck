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

    Node(const lexer::Position &, NodeType) noexcept;
    Node(const lexer::Position &, NodeType, const std::vector<Node> &)
        noexcept(noexcept(type == NodeType::Loop));

    bool operator ==(const parser::Node &) const;
};

std::vector<Node> parse(const std::vector<lexer::Token> &) noexcept(false);
}