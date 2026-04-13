#include "ast_nodes.hpp"

#include <any>

#include "../compiler_utils/token.hpp"
#include "i_ast_visitor.hpp"

/***************************************************************************************************/
/*                                     FunctionDefinitionNode                                      */
/***************************************************************************************************/
std::any FunctionDefinitionNode::Accept(IAstVisitor &ast_visitor) {
  return ast_visitor.VisitFunctionDefinitionNode(this);
}

Token FunctionDefinitionNode::identifier() const { return identifier_; }

// The 'get' method only takes a look at the memory address stored within the
// smart pointer ('std::unique_ptr') and returns A COPY of such memory address
// (a StmtNode*). This is valid because returning a copy does not change the
// smart pointer that is stored within the class.
StmtNode *FunctionDefinitionNode::body() const { return body_.get(); }

/***************************************************************************************************/
/*                                           ProgramNode                                           */
/***************************************************************************************************/
std::any ProgramNode::Accept(IAstVisitor &ast_visitor) {
  return ast_visitor.VisitProgramNode(this);
}

// Same logic as explained in the 'FunctionDefinitionNode::body' method above.
// Also, This accessor cannot be marked with the "const" qualifier because here
// I am returning a non-const reference.
FunctionDefinitionNode *ProgramNode::function_definition() const {
  return function_definition_.get();
}

/***************************************************************************************************/
/*                                          ReturnStmtNode                                         */
/***************************************************************************************************/
std::any ReturnStmtNode::Accept(IAstVisitor &ast_visitor) {
  return ast_visitor.VisitReturnStmtNode(this);
}

ExprNode *ReturnStmtNode::expr() const { return expr_.get(); }

/***************************************************************************************************/
/*                                         ConstantExprNode                                        */
/***************************************************************************************************/
std::any ConstantExprNode::Accept(IAstVisitor &ast_visitor) {
  return ast_visitor.VisitConstantExprNode(this);
}

int ConstantExprNode::value() { return value_; }
