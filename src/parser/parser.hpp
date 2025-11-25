#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "../ast_nodes/ast_nodes.hpp"
#include "../compiler_utils/token.hpp"
#include "../compiler_utils/token_type.hpp"

class Parser {
public:
  Parser(std::vector<Token> tokens);
  std::unique_ptr<AstNode> Parse();

private:
  std::unique_ptr<ExprNode> Expression();
  std::unique_ptr<FunctionDefinitionNode> Function();
  std::unique_ptr<AstNode> Program();
  std::unique_ptr<StmtNode> Statement();

  Token Advance();
  bool Check(TokenType token_type);
  Token Consume(TokenType token_type, std::string error_message);
  bool IsAtEnd();
  bool Match(TokenType token_type);
  Token Peek();
  Token Previous();

  std::size_t current_{0};
  std::vector<Token> tokens_;
};
