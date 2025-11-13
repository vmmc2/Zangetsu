#include "parser.hpp"

#include <vector>

#include "../compiler_utils/token.hpp"

Parser::Parser(std::vector<Token> tokens) : tokens_(tokens) {}
