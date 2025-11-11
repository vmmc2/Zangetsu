#pragma once

#include <cstdint>
#include <map>
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
  void Identifier();
  void IntegerConstant();
  bool IsAlpha(char c) const;
  bool IsAlphaNumeric(char c) const;
  bool IsAtEnd() const;
  bool IsDigit(char c) const;
  void LexToken();
  bool Match(char expected);
  char Peek(int offset) const;
  void SingleLineComment();

  std::uint64_t current_{0};
  std::uint64_t start_{0};
  std::uint64_t line_{1};
  std::uint64_t column_{1};
  std::string source_code_;
  std::vector<Token> tokens_;
  // TODO: Give a better name to the attribute below.
  std::map<std::string, TokenType> token_lexeme_to_token_type_map_ = {
      {"int", TokenType::kInt},
      {"return", TokenType::kReturn},
      {"void", TokenType::kVoid},
  };
};