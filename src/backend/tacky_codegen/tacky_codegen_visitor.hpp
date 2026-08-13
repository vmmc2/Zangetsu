#pragma once

#include <any>
#include <string>

#include "../../frontend/ast/i_ast_visitor.hpp"

class TackyCodegenVisitor : public IAstVisitor {
public:
  std::any VisitFunctionDefinitionNode(FunctionDefinitionNode *node) override;
  std::any VisitProgramNode(ProgramNode *node) override;
  std::any VisitReturnStmtNode(ReturnStmtNode *node) override;
  std::any VisitConstantExprNode(ConstantExprNode *node) override;
  std::any VisitUnaryExprNode(UnaryExprNode *node) override;

private:
  int temp_var_counter_ = 0;

  std::string GetCurrTempVarName() {
    return "tmp." + std::to_string(temp_var_counter_++);
  }
};
