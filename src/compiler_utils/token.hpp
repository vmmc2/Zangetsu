#pragma once

#include <any>
#include <string>

#include "token_type.hpp"

class Token {
public:
  Token(int line, int column, TokenType token_type, std::string lexeme,
        std::any value);

private:
  int line_;
  int column_;
  TokenType token_type_;
  std::string lexeme_;
  std::any value_;
};

std::ostream &operator<<(std::ostream &os, Token token);
