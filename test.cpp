#define BOOST_TEST_MODULE tests
#include <boost/test/included/unit_test.hpp>

#include "lexer.hpp"
#include "parser.hpp"

bool lexer::Position::operator ==(const lexer::Position &p) const {
    return (line == p.line && column == p.column);
}

bool lexer::Token::operator ==(const lexer::Token &t) const {
    return (position == t.position && type == t.type && value == t.value);
}

bool parser::Node::operator ==(const parser::Node &n) const {
    return (position == n.position && type == n.type && children == n.children);
}

BOOST_AUTO_TEST_CASE(lexer_test) {
    using namespace lexer;
    std::vector<Token> tokens = lex(">><++++---[,.\n]");
    std::vector<Token> valid_tokens = {
        Token(Position { .column = 1 }, TokenType::Operator, ">"),
        Token(Position { .column = 2 }, TokenType::Operator, ">"),
        Token(Position { .column = 3 }, TokenType::Operator, "<"),
        Token(Position { .column = 4 }, TokenType::Operator, "+"),
        Token(Position { .column = 5 }, TokenType::Operator, "+"),
        Token(Position { .column = 6 }, TokenType::Operator, "+"),
        Token(Position { .column = 7 }, TokenType::Operator, "+"),
        Token(Position { .column = 8 }, TokenType::Operator, "-"),
        Token(Position { .column = 9 }, TokenType::Operator, "-"),
        Token(Position { .column = 10 }, TokenType::Operator, "-"),
        Token(Position { .column = 11 }, TokenType::Separator, "["),
        Token(Position { .column = 12 }, TokenType::Operator, ","),
        Token(Position { .column = 13 }, TokenType::Operator, "."),
        Token(Position { .line = 2, .column = 1 }, TokenType::Separator, "]")};

    BOOST_TEST(tokens == valid_tokens);
}

BOOST_AUTO_TEST_CASE(parser_test) {
    using namespace parser;
    std::vector<Node> tree = std::get<0>(parse(lexer::lex(">><++++---[,.\n]")));
    std::vector<Node> valid_tree = {
        Node(lexer::Position { .column = 1 }, NodeType::IncrementPtr),
        Node(lexer::Position { .column = 2 }, NodeType::IncrementPtr),
        Node(lexer::Position { .column = 3 }, NodeType::DecrementPtr),
        Node(lexer::Position { .column = 4 }, NodeType::Increment),
        Node(lexer::Position { .column = 5 }, NodeType::Increment),
        Node(lexer::Position { .column = 6 }, NodeType::Increment),
        Node(lexer::Position { .column = 7 }, NodeType::Increment),
        Node(lexer::Position { .column = 8 }, NodeType::Decrement),
        Node(lexer::Position { .column = 9 }, NodeType::Decrement),
        Node(lexer::Position { .column = 10 }, NodeType::Decrement),
        Node(lexer::Position { .column = 11 }, NodeType::Loop, std::vector {
            Node(lexer::Position { .column = 12 }, NodeType::Read),
            Node(lexer::Position { .column = 13 }, NodeType::Write)
        })};
    
    BOOST_TEST(tree == valid_tree);
}