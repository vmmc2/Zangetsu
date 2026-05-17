#pragma once

#include <any>

#include "ast_nodes.hpp"

class IAstVisitor {
public:
  virtual ~IAstVisitor() = default;

  virtual std::any
  VisitFunctionDefinitionNode(FunctionDefinitionNode *node) = 0;
  virtual std::any VisitProgramNode(ProgramNode *node) = 0;
  virtual std::any VisitReturnStmtNode(ReturnStmtNode *node) = 0;
  virtual std::any VisitConstantExprNode(ConstantExprNode *node) = 0;
};
