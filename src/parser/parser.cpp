#include "parser.hpp"

#include <stdexcept>
#include <vector>

#include "../compiler_utils/token.hpp"
#include "../compiler_utils/token_type.hpp"

Parser::Parser(std::vector<Token> tokens) : tokens_(tokens) {}

std::unique_ptr<AstNode> Parser::Parse() { return Program(); }

Token Parser::Advance() {
  if (!IsAtEnd()) {
    current_++;
  }

  return Previous();
}

bool Parser::Check(TokenType token_type) {
  if (IsAtEnd()) {
    return false;
  }

  return Peek().token_type() == token_type;
}

Token Parser::Consume(TokenType token_type, std::string error_message) {
  if (Check(token_type)) {
    return Advance();
  }

  throw std::runtime_error{error_message};
}

bool Parser::IsAtEnd() { return Peek().token_type() == TokenType::kFileEnd; }

bool Parser::Match(TokenType token_type) {
  if (Check(token_type)) {
    Advance();
    return true;
  }

  return false;
}

Token Parser::Peek() { return tokens_[current_]; }

Token Parser::Previous() { return tokens_[current_ - 1]; }

std::unique_ptr<ExprNode> Parser::Expression() {
  if (Match(TokenType::kIntegerConst)) {
    int integer_constant = std::any_cast<int>(Previous().value());
    return std::make_unique<ConstantExprNode>(integer_constant);
  }

  throw std::runtime_error{"Expected token of type TokenType::kIntegerConst."};
}

std::unique_ptr<FunctionDefinitionNode> Parser::Function() {
  Consume(TokenType::kInt,
          "Expected the 'int' keyword as return type of the 'main' function.");
  Consume(TokenType::kIdentifier,
          "Expected an identifier after the function return type.");
  Token function_identifier = Previous();

  Consume(TokenType::kLeftParen, "Expected a '(' after the function name.");
  Consume(TokenType::kVoid,
          "Expected the 'void' keyword between after the '(' character.");
  Consume(TokenType::kRightParen, "Expected a ')' after the 'void' keyword.");

  Consume(TokenType::kLeftBrace,
          "Expected a '{' after the ')' in a function definition.");
  std::unique_ptr<StmtNode> function_body = Statement();
  Consume(TokenType::kRightBrace,
          "Expected a '}' after the last statement of the function body.");

  if (!IsAtEnd()) {
    throw std::runtime_error{"Unexpected sequence of tokens."};
  }

  return std::make_unique<FunctionDefinitionNode>(function_identifier,
                                                  std::move(function_body));
}

std::unique_ptr<AstNode> Parser::Program() { return Function(); }

std::unique_ptr<StmtNode> Parser::Statement() {
  Consume(TokenType::kReturn,
          "Expected the 'return' keyword starting a statement.");
  std::unique_ptr<ExprNode> expr = Expression();
  Consume(TokenType::kSemicolon, "Expected a ';' at the end of a statement.");

  return std::make_unique<ReturnStmtNode>(std::move(expr));
}
