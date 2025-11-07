#include "token.hpp"

#include <any>
#include <format>
#include <string>
#include <utility>

Token::Token(int line, int column, TokenType token_type, std::string lexeme,
             std::any value)
    : line_(line), column_(column), token_type_(token_type),
      lexeme_(std::move(lexeme)), value_(value) {}

std::ostream &operator<<(std::ostream &os, Token token) {
  os << std::format("\n");

  return os;
}