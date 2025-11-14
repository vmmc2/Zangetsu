#include "parser.hpp"

#include <stdexcept>
#include <vector>

#include "../compiler_utils/token.hpp"
#include "../compiler_utils/token_type.hpp"

Parser::Parser(std::vector<Token> tokens) : tokens_(tokens) {}

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
    Advance();
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

AstNode *Parser::Expression() {
  // Return a constant token with its value wrapped.
}

AstNode *Parser::Function() {
  Match(TokenType::kInt);
  Match(TokenType::kIdentifier);
  // Get Identifier Token.

  Match(TokenType::kLeftParen);
  Match(TokenType::kVoid);
  Match(TokenType::kRightParen);

  Match(TokenType::kLeftBrace);
  // Get statement node.
  Match(TokenType::kRightBrace);
}

AstNode *Parser::Program() { return Function(); }

AstNode *Parser::Statement() {
  Match(TokenType::kReturn);
  // Get expression node.
  Match(TokenType::kSemicolon);
}
