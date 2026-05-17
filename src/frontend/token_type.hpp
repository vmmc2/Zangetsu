#pragma once

#include <string>

enum class TokenType {
  // Single-Character Tokens
  kLeftBrace,
  kRightBrace,
  kLeftParen,
  kRightParen,
  kSemicolon,

  // Multi-Character Tokens
  kIdentifier,
  kIntegerConst,

  // Keyword Tokens
  kInt,
  kReturn,
  kVoid,

  // End of File Token
  kFileEnd
};

std::string TokenTypeToString(TokenType token_type);

std::ostream &operator<<(std::ostream &os, TokenType token_type);
