#pragma once

#include <string>
#include <vector>

#include "../compiler_utils/token.hpp"

class Lexer {
public:
  Lexer(std::string source_code);
  std::vector<Token> Lex();

private:
  void AddToken(TokenType token_type);
  void AddToken(TokenType token_type, std::any value);
  char Advance();
  bool IsAlpha(char c) const;
  bool IsAlphaNumeric (char c) const;
  bool IsAtEnd() const;
  bool IsDigit(char c) const;
  void LexToken();
  bool Match(char expected);
  char Peek(int offset) const;

  int current_{0};
  int start_{0};
  int line_{1};
  int column_{1};
  std::string source_code_;
  std::vector<Token> tokens_;
};