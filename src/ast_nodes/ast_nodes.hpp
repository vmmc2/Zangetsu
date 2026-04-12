#pragma once

#include <any>
#include <memory>

#include "../compiler_utils/token.hpp"

class IAstVisitor;

class AstNode {
public:
  // A virtual destructor for this base class is needed to ensure that when
  // you delete an AstNode*, the destructor of the correct class (e.g.,
  // ReturnNode) is called.
  virtual ~AstNode() = default;

  // The standard solution to find out what an AstNode* actually is the
  // Visitor pattern.
  virtual std::any Accept(IAstVisitor &ast_visitor) = 0;
};

class ExprNode : public AstNode {
public:
};

class StmtNode : public AstNode {
public:
};

class FunctionDefinitionNode : public AstNode {
public:
  FunctionDefinitionNode(Token identifier, std::unique_ptr<StmtNode> body)
      : identifier_(identifier), body_(std::move(body)) {}

  std::any Accept(IAstVisitor &ast_visitor) override;
  Token identifier() const;
  StmtNode *body() const;

private:
  Token identifier_;
  std::unique_ptr<StmtNode> body_;
};

class ProgramNode : public AstNode {
public:
  ProgramNode(std::unique_ptr<FunctionDefinitionNode> function_definition)
      : function_definition_(std::move(function_definition)) {}

  std::any Accept(IAstVisitor &ast_visitor) override;
  FunctionDefinitionNode *function_definition() const;

private:
  std::unique_ptr<FunctionDefinitionNode> function_definition_;
};

class ReturnStmtNode : public StmtNode {
public:
  ReturnStmtNode(std::unique_ptr<ExprNode> expr) : expr_(std::move(expr)) {}

  std::any Accept(IAstVisitor &ast_visitor) override;
  ExprNode *expr() const;

private:
  std::unique_ptr<ExprNode> expr_;
};

class ConstantExprNode : public ExprNode {
public:
  ConstantExprNode(int value) : value_(value) {}

  std::any Accept(IAstVisitor &ast_visitor) override;
  int value();

private:
  int value_;
};
