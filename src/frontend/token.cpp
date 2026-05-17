#include "token.hpp"
#include "token_type.hpp"

#include <any>
#include <format>
#include <string>
#include <utility>

Token::Token(int line, int column, TokenType token_type, std::string lexeme,
             std::any value)
    : line_(line), column_(column), token_type_(token_type),
      lexeme_(std::move(lexeme)), value_(value) {}

int Token::line() const { return line_; }

int Token::column() const { return column_; }

TokenType Token::token_type() const { return token_type_; }

std::string Token::lexeme() const { return lexeme_; }

std::any Token::value() const { return value_; }

std::ostream &operator<<(std::ostream &os, Token token) {
  std::string token_type_str = TokenTypeToString(token.token_type());
  std::string token_value_str;

  switch (token.token_type()) {
  case (TokenType::kIdentifier):
    token_value_str = std::any_cast<std::string>(token.value());
    break;
  case (TokenType::kIntegerConst):
    token_value_str = std::to_string(std::any_cast<int>(token.value()));
    break;
  case (TokenType::kInt):
    token_value_str = std::any_cast<std::string>(token.value());
    break;
  case (TokenType::kReturn):
    token_value_str = std::any_cast<std::string>(token.value());
    break;
  case (TokenType::kVoid):
    token_value_str = std::any_cast<std::string>(token.value());
    break;
  default:
    token_value_str = "N/A";
    break;
  }

  os << std::format("[{:04}:{:04}] - TokenType: {} - Lexeme: {} - Value: {}",
                    token.line(), token.column(), token_type_str,
                    token.lexeme(), token_value_str);

  return os;
}
