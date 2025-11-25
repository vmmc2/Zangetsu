#pragma once

#include <any>
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
  virtual std::any Accept(AstVisitor &ast_visitor) = 0;
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

  std::any Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
    return {};
  }

  Token identifier() { return identifier_; }

  // The 'get' method only takes a look at the memory address stored within the
  // smart pointer ('std::unique_ptr') and returns A COPY of such memory address
  // (a StmtNode*). This is valid because returning a copy does not change the
  // smart pointer itself, that is stored within the class.
  StmtNode *body() const { return body_.get(); }

private:
  Token identifier_;
  std::unique_ptr<StmtNode> body_;
};

class ProgramNode : public AstNode {
public:
  ProgramNode(std::unique_ptr<FunctionDefinitionNode> function_definition)
      : function_definition_(std::move(function_definition)) {}

  std::any Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
    return {};
  }

  // This accessor cannot be marked with the "const" qualifier because here I am
  // returning a non-const reference.
  FunctionDefinitionNode *function_definition() const {
    return function_definition_.get();
  }

private:
  std::unique_ptr<FunctionDefinitionNode> function_definition_;
};

class ReturnStmtNode : public StmtNode {
public:
  ReturnStmtNode(std::unique_ptr<ExprNode> expr) : expr_(std::move(expr)) {}

  std::any Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
    return {};
  }

  ExprNode *expr() const { return expr_.get(); }

private:
  std::unique_ptr<ExprNode> expr_;
};

class ConstantExprNode : public ExprNode {
public:
  ConstantExprNode(int value) : value_(value) {}

  std::any Accept(AstVisitor &ast_visitor) override {
    // TODO: Implement this method.
    return {};
  }

  int value() { return value_; }

private:
  int value_;
};
