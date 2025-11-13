#pragma once

#include <vector>

#include "../ast_nodes/ast_nodes.hpp"
#include "../compiler_utils/token.hpp"

class Parser {
public:
  Parser(std::vector<Token> tokens);
  AstNode *Parse();

private:
  AstNode *Expression();
  AstNode *Function();
  AstNode *Program();
  AstNode *Statement();

  std::vector<Token> tokens_;
};
