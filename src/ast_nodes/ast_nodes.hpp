#pragma once

#include <any>

#include "../compiler_utils/token.hpp"

class AstNode {
public:
};

class ProgramNode {
public:
  AstNode *function_definition_;
};

class FunctionDefinitionNode {
public:
  Token function_identifier_;
  AstNode *function_body_;
};

class ReturnStmt {
public:
  AstNode *expr_;
};

class ConstantExpr {
public:
  std::any value_;
};
