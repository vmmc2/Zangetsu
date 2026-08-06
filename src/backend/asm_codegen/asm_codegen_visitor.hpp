#pragma once

#include <any>

#include "../../frontend/ast/i_ast_visitor.hpp"

class AssemblyCodeGenVisitor : public IAstVisitor {
public:
  std::any VisitFunctionDefinitionNode(FunctionDefinitionNode *node) override;
  std::any VisitProgramNode(ProgramNode *node) override;
  std::any VisitReturnStmtNode(ReturnStmtNode *node) override;
  std::any VisitConstantExprNode(ConstantExprNode *node) override;
};
