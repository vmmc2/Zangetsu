#include "pretty_printer_visitor.hpp"

#include <any>
#include <format>
#include <string>

std::any PrettyPrinterVisitor::VisitProgramNode(ProgramNode *node) {
  AppendIndented("Program(");

  indentation_level_++;
  if (node->function_definition()) {
    node->function_definition()->Accept(*this);
  }
  indentation_level_--;

  AppendIndented(")");

  return {};
}

std::any PrettyPrinterVisitor::VisitFunctionDefinitionNode(
    FunctionDefinitionNode *node) {
  AppendIndented("Function(");

  indentation_level_++;

  AppendIndented(std::format("name={},", node->identifier().lexeme()));
  AppendIndented("body=", false);

  if (node->body()) {
    node->body()->Accept(*this);
  }
  indentation_level_--;

  AppendIndented(")");

  return {};
}

std::any PrettyPrinterVisitor::VisitReturnStmtNode(ReturnStmtNode *node) {
  AppendUnindented("Return(");

  indentation_level_++;
  if (node->expr()) {
    node->expr()->Accept(*this);
  }
  indentation_level_--;

  AppendIndented(")");

  return {};
}

std::any PrettyPrinterVisitor::VisitConstantExprNode(ConstantExprNode *node) {
  AppendIndented(std::format("Constant({})", node->value()));

  return {};
}

const std::string &PrettyPrinterVisitor::ast() const { return ast_; }

void PrettyPrinterVisitor::AppendUnindented(const std::string &content,
                                            bool add_endline) {
  ast_ += content;

  if (add_endline) {
    ast_ += "\n";
  }
}

void PrettyPrinterVisitor::AppendIndented(const std::string &content,
                                          bool add_endline) {
  std::string indented(indentation_level_ * 2, ' ');
  ast_ += indented + content;

  if (add_endline) {
    ast_ += "\n";
  }
}
