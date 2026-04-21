#pragma once

#include "i_ast_visitor.hpp"

class AssemblyGeneratorVisitor : public IAstVisitor {
public:
  std::any VisitFunctionDefinitionNode(FunctionDefinitionNode *node) override;
  std::any VisitProgramNode(ProgramNode *node) override;
  std::any VisitReturnStmtNode(ReturnStmtNode *node) override;
  std::any VisitConstantExprNode(ConstantExprNode *node) override;
};
