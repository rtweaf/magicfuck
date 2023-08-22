#pragma once

#include <vector>
#include <tuple>

#include "parser.hpp"

namespace executor {
void execute(std::vector<parser::Node>, std::vector<char> &, unsigned int &);
}