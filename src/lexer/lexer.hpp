#pragma once

#include <string>
#include <vector>

#include "../compiler_utils/token.hpp"

class Lexer {
public:
  Lexer();
  std::vector<Token> Lex();

private:
  int current_{0};
  int start_{0};
  int line_{1};
  int column_{1};
  std::string source_code_;
  std::vector<Token> tokens_;
};