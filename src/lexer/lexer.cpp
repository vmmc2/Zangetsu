#include "lexer.hpp"

#include <format>
#include <stdexcept>
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

void Lexer::AddToken(TokenType token_type) { AddToken(token_type, {}); }

void Lexer::AddToken(TokenType token_type, std::any value) {
  std::string token_lexeme = source_code_.substr(start_, current_ - start_);
  tokens_.emplace_back(Token(line_, column_, token_type, token_lexeme, value));
}

char Lexer::Advance() {
  current_++;

  return source_code_.at(current_ - 1);
}

void Lexer::Identifier() {
  while (IsAlphaNumeric(Peek(0))) {
    Advance();
  }

  std::string token_lexeme = source_code_.substr(start_, current_ - start_);
  std::any token_value = token_lexeme;
  TokenType token_type;
  if (token_lexeme_to_token_type_map_.contains(token_lexeme)) {
    token_type = token_lexeme_to_token_type_map_.at(token_lexeme);
  } else {
    token_type = TokenType::kIdentifier;
  }

  AddToken(token_type, token_value);
}

void Lexer::IntegerConstant() {
  while (IsDigit(Peek(0))) {
    Advance();
  }

  if (IsAlpha(Peek(0))) {
    throw std::runtime_error{
        std::format("The character after the last digit is not a word boundary "
                    "that respects the regex '[0-9]+\\b': {}.",
                    Peek(0))};
  }

  std::string token_lexeme = source_code_.substr(start_, current_ - start_);
  std::any token_value = std::stoi(token_lexeme);
  TokenType token_type = TokenType::kIntegerConst;

  AddToken(token_type, token_value);
}

bool Lexer::IsAlpha(char c) const {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_'));
}

bool Lexer::IsAlphaNumeric(char c) const { return (IsAlpha(c) || IsDigit(c)); }

bool Lexer::IsAtEnd() const { return current_ >= source_code_.length(); }

bool Lexer::IsDigit(char c) const { return (c >= '0' && c <= '9'); }

void Lexer::LexToken() {
  // TODO: Think about how to deal with column displacement.
  char curr_char = Advance();

  switch (curr_char) {
  case ('{'):
    AddToken(TokenType::kLeftBrace);
    break;
  case ('}'):
    AddToken(TokenType::kRightBrace);
    break;
  case ('('):
    AddToken(TokenType::kLeftParen);
    break;
  case (')'):
    AddToken(TokenType::kRightParen);
    break;
  case (';'):
    AddToken(TokenType::kSemicolon);
    break;
  case (' '):
  case ('\r'):
  case ('\t'):
    break; // Since the C programming language does not care about whitespace
           // characters, the Lexer ignores them during the lexing process.
  case ('\n'):
    line_ = line_ + 1;
    column_ = 1;
    break;
  default:
    if (IsAlpha(curr_char)) {
      Identifier();
    } else if (IsDigit(curr_char)) {
      IntegerConstant();
    } else {
      throw std::runtime_error{std::format(
          "Unauthorized character present in the source code: {}.", curr_char)};
    }
    break;
  }
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
