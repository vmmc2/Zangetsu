#include "token_type.hpp"

#include <string>

std::string TokenTypeToString(TokenType token_type) {
  switch (token_type) {
  case TokenType::kLeftBrace:
    return "TokenType::kLeftBrace";
  case TokenType::kRightBrace:
    return "TokenType::kRightBrace";
  case TokenType::kLeftParen:
    return "TokenType::kLeftParen";
  case TokenType::kRightParen:
    return "TokenType::kRightParen";
  case TokenType::kSemicolon:
    return "TokenType::kSemicolon";
  case TokenType::kIdentifier:
    return "TokenType::kIdentifier";
  case TokenType::kIntegerConst:
    return "TokenType::kIntegerConst";
  case TokenType::kInt:
    return "TokenType::kInt";
  case TokenType::kReturn:
    return "TokenType::kReturn";
  case TokenType::kVoid:
    return "TokenType::kVoid";
  case TokenType::kFileEnd:
    return "TokenType::kFileEnd";
  }
}

std::ostream &operator<<(std::ostream &os, TokenType token_type) {
  os << TokenTypeToString(token_type);

  return os;
}
