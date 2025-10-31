#pragma once

#include <map>
#include <string>

enum class TokenType {
  // Single-Character Tokens
  kLeftParen,
  kRightParen,
  kLeftBrace,
  kRightBrace,
  kSemicolon,

  // Multi-Character Tokens
  kIdentifier,
  kInteger,

  // Keyword Tokens
  kInt,
  kReturn,
  kVoid,
};
