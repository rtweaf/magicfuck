#include <cstdio>

#include "executor.hpp"

namespace executor {
void execute(std::vector<parser::Node> tree, std::vector<char> &tape,
        unsigned int &index) {
    for (parser::Node node : tree) {
        switch (node.type) {
            case parser::NodeType::Loop:
            while (tape[index])
                execute(node.children, tape, index);
            break;

            case parser::NodeType::IncrementPtr:
            tape.push_back(0);
            index++;
            break;

            case parser::NodeType::DecrementPtr:
            index--;
            break;

            case parser::NodeType::Increment:
            tape[index]++;
            break;

            case parser::NodeType::Decrement:
            tape[index]--;
            break;

            case parser::NodeType::Write:
            putchar(tape[index]);
            break;

            case parser::NodeType::Read:
            tape[index] = getchar();
            break;
        }
    }
}
}