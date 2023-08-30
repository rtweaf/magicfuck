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

BOOST_AUTO_TEST_SUITE(lexer_suite)

BOOST_AUTO_TEST_CASE(simple_case) {
    using namespace lexer;
    
    std::vector<Token> tokens = lex("----[---->+<]>++.+[-->+++<]>-.");
    
    std::vector<Token> valid_tokens = {
        Token(Position { .column = 1 }, TokenType::Operator, "-"),
        Token(Position { .column = 2 }, TokenType::Operator, "-"),
        Token(Position { .column = 3 }, TokenType::Operator, "-"),
        Token(Position { .column = 4 }, TokenType::Operator, "-"),
        Token(Position { .column = 5 }, TokenType::Separator, "["),
        Token(Position { .column = 6 }, TokenType::Operator, "-"),
        Token(Position { .column = 7 }, TokenType::Operator, "-"),
        Token(Position { .column = 8 }, TokenType::Operator, "-"),
        Token(Position { .column = 9 }, TokenType::Operator, "-"),
        Token(Position { .column = 10 }, TokenType::Operator, ">"),
        Token(Position { .column = 11 }, TokenType::Operator, "+"),
        Token(Position { .column = 12 }, TokenType::Operator, "<"),
        Token(Position { .column = 13 }, TokenType::Separator, "]"),
        Token(Position { .column = 14 }, TokenType::Operator, ">"),
        Token(Position { .column = 15 }, TokenType::Operator, "+"),
        Token(Position { .column = 16 }, TokenType::Operator, "+"),
        Token(Position { .column = 17 }, TokenType::Operator, "."),
        Token(Position { .column = 18 }, TokenType::Operator, "+"),
        Token(Position { .column = 19 }, TokenType::Separator, "["),
        Token(Position { .column = 20 }, TokenType::Operator, "-"),
        Token(Position { .column = 21 }, TokenType::Operator, "-"),
        Token(Position { .column = 22 }, TokenType::Operator, ">"),
        Token(Position { .column = 23 }, TokenType::Operator, "+"),
        Token(Position { .column = 24 }, TokenType::Operator, "+"),
        Token(Position { .column = 25 }, TokenType::Operator, "+"),
        Token(Position { .column = 26 }, TokenType::Operator, "<"),
        Token(Position { .column = 27 }, TokenType::Separator, "]"),
        Token(Position { .column = 28 }, TokenType::Operator, ">"),
        Token(Position { .column = 29 }, TokenType::Operator, "-"),
        Token(Position { .column = 30 }, TokenType::Operator, ".")};

    BOOST_TEST(tokens == valid_tokens);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(parser_suite)

BOOST_AUTO_TEST_CASE(simple_caase) {
    using namespace parser;

    std::vector<Node> tree = std::get<0>(parse(lexer::lex("++++++++++++++++++++"
        "+++++++++++++++++++++++++++++++++++++++++++++.>+++++++++++++++++++++++"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
        "+++++.>")));
   
    std::vector<Node> valid_tree;
   
    for (unsigned char i = 1; i <= 65; ++i)
        valid_tree.push_back(Node(lexer::Position { .column = i },
            NodeType::Increment));
   
    valid_tree.push_back(Node(lexer::Position { .column = 66 },
        NodeType::Write));

    valid_tree.push_back(Node(lexer::Position { .column = 67 },
        NodeType::IncrementPtr));
    
    for (unsigned char i = 68; i <= 165; ++i)
        valid_tree.push_back(Node(lexer::Position { .column = i },
            NodeType::Increment));
    
    valid_tree.push_back(Node(lexer::Position { .column = 166 },
        NodeType::Write));
        
    valid_tree.push_back(Node(lexer::Position { .column = 167 },
        NodeType::IncrementPtr));
    
    BOOST_TEST(tree == valid_tree);
}

BOOST_AUTO_TEST_CASE(loop_case) {
    using namespace parser;
    
    std::vector<Node> tree = std::get<0>(parse(lexer::lex(
        "----[---->+<]>++.+[-->+++<]>-.")));
    
    std::vector<Node> first_loop;
    std::vector<Node> second_loop = {};
    
    std::vector<Node> valid_tree;
    
    for (unsigned int i = 1; i <= 4; ++i)
        valid_tree.push_back(Node(lexer::Position { .column = i },
            NodeType::Decrement));

    for (unsigned int i = 6; i <= 9; ++i)
        first_loop.push_back(Node(lexer::Position { .column = i },
            NodeType::Decrement));
    first_loop.push_back(Node(lexer::Position { .column = 10 }, 
        NodeType::IncrementPtr));
    first_loop.push_back(Node(lexer::Position { .column = 11 }, 
        NodeType::Increment));
    first_loop.push_back(Node(lexer::Position { .column = 12 }, 
        NodeType::DecrementPtr));
    valid_tree.push_back(Node(lexer::Position { .column = 5 }, NodeType::Loop,
        first_loop));

    valid_tree.push_back(Node(lexer::Position { .column = 14 }, 
        NodeType::IncrementPtr));

    valid_tree.push_back(Node(lexer::Position { .column = 15 }, 
        NodeType::Increment));

    valid_tree.push_back(Node(lexer::Position { .column = 16 }, 
        NodeType::Increment));

    valid_tree.push_back(Node(lexer::Position { .column = 17 }, 
        NodeType::Write));

    valid_tree.push_back(Node(lexer::Position { .column = 18 }, 
        NodeType::Increment));

    second_loop.push_back(Node(lexer::Position { .column = 20 }, 
        NodeType::Decrement));
    second_loop.push_back(Node(lexer::Position { .column = 21 }, 
        NodeType::Decrement));
    second_loop.push_back(Node(lexer::Position { .column = 22 }, 
        NodeType::IncrementPtr));
    second_loop.push_back(Node(lexer::Position { .column = 23 }, 
        NodeType::Increment));
    second_loop.push_back(Node(lexer::Position { .column = 24 }, 
        NodeType::Increment));
    second_loop.push_back(Node(lexer::Position { .column = 25 }, 
        NodeType::Increment));
    second_loop.push_back(Node(lexer::Position { .column = 26 }, 
        NodeType::DecrementPtr));
    valid_tree.push_back(Node(lexer::Position { .column = 19 }, NodeType::Loop,
        second_loop));

    valid_tree.push_back(Node(lexer::Position { .column = 28 }, 
        NodeType::IncrementPtr));

    valid_tree.push_back(Node(lexer::Position { .column = 29 }, 
        NodeType::Decrement));

    valid_tree.push_back(Node(lexer::Position { .column = 30 }, 
        NodeType::Write));

    BOOST_TEST(tree == valid_tree);
}

BOOST_AUTO_TEST_SUITE_END()