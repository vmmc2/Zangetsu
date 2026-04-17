#pragma once

#include "i_ast_visitor.hpp"

#include <any>
#include <string>

class PrettyPrinterVisitor : public IAstVisitor {
public:
  std::any VisitFunctionDefinitionNode(FunctionDefinitionNode *node) override;
  std::any VisitProgramNode(ProgramNode *node) override;
  std::any VisitReturnStmtNode(ReturnStmtNode *node) override;
  std::any VisitConstantExprNode(ConstantExprNode *node) override;

  const std::string &ast() const;

private:
  void AppendUnindented(const std::string &content, bool add_endline = true);
  void AppendIndented(const std::string &content, bool add_endline = true);

  int indentation_level_ = 0;
  std::string ast_;
};
