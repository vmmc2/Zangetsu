#include "lexer.hpp"

#include <string>
#include <vector>

#include "../compiler_utils/token.hpp"
#include "../compiler_utils/token_type.hpp"

Lexer::Lexer(std::string source_code) : source_code_(source_code) {}

std::vector<Token> Lexer::Lex() {
  while (!IsAtEnd()) {
    start_ = current_;
    LexToken();
  }
  tokens_.emplace_back(Token(line_, column_, TokenType::kFileEnd, "", {}));

  return tokens_;
}

void Lexer::AddToken(TokenType token_type) {
  // TODO: Implement this.
}

void Lexer::AddToken(TokenType token_type, std::any value) {
  // TODO: Implement this.
}

char Lexer::Advance() {
  current_++;

  return source_code_.at(current_ - 1);
}

bool Lexer::IsAlpha(char c) const {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'));
}

bool Lexer::IsAlphaNumeric(char c) const { return (IsAlpha(c) || IsDigit(c)); }

bool Lexer::IsAtEnd() const { return current_ >= source_code_.length(); }

bool Lexer::IsDigit(char c) const { return (c >= '0' && c <= '9'); }

void Lexer::LexToken() {
  // TODO: Implement this.
}

bool Lexer::Match(char expected) {
  if (IsAtEnd()) {
    return false;
  }
  if (Peek(0) != expected) {
    return false;
  }
  current_++;

  return true;
}

char Lexer::Peek(int offset) const {
  if (current_ + offset >= source_code_.length()) {
    return '\0';
  }
  return source_code_.at(current_ + offset);
}
