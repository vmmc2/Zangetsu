#pragma once

#include <memory>

#include "../compiler_utils/token.hpp"

class AstVisitor;

class AstNode {
public:
  // A virtual destructor for this base class is needed to ensure that when
  // you delete an AstNode*, the destructor of the correct class (e.g.,
  // ReturnNode) is called.
  virtual ~AstNode() = default;

  // To find out what an AstNode* actually is the standard solution when
  // implementing a compiler is the Visitor Pattern.
  virtual void Accept(AstVisitor &ast_visitor) = 0;
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

  void Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
  }

  Token identifier() { return identifier_; }
  // If the return type was "std::unique_ptr<StmtNode>" this code wouldn't
  // compile because we would be trying to return by value. This means that the
  // compiler would make a copy of this smart pointer and then return it.
  // However, the 'std::unique_ptr' pointer does not allow copies.
  // Hence, we return it by reference. This way, I am not creating a copy of the
  // smart pointer. Instead, I am just returning an alias to the smart pointer
  // that already exists within this class.
  std::unique_ptr<StmtNode> &body() { return body_; }

private:
  Token identifier_;
  std::unique_ptr<StmtNode> body_;
};

class ProgramNode : public AstNode {
public:
  ProgramNode(std::unique_ptr<FunctionDefinitionNode> function_definition)
      : function_definition_(std::move(function_definition)) {}

  void Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
  }

  // This accessor cannot be marked with the "const" qualifier because here I am
  // returning a non-const reference.
  std::unique_ptr<FunctionDefinitionNode> &function_definition() {
    return function_definition_;
  }

private:
  std::unique_ptr<FunctionDefinitionNode> function_definition_;
};

class ReturnStmtNode : public StmtNode {
public:
  ReturnStmtNode(std::unique_ptr<ExprNode> expr) : expr_(std::move(expr)) {}

  void Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
  }

  // TODO: Why can't I mark this method with the 'const' qualifier?
  std::unique_ptr<ExprNode> &expr() { return expr_; }

private:
  std::unique_ptr<ExprNode> expr_;
};

class ConstantExprNode : public ExprNode {
public:
  ConstantExprNode(int value) : value_(value) {}

  void Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
  }

  int value() { return value_; }

private:
  int value_;
};
