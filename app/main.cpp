#include <iostream>
#include <string>
#include <vector>

#include "../src/compiler_utils/token.hpp"
#include "../src/file_scanner/file_scanner.hpp"
#include "../src/lexer/lexer.hpp"

int main(int argc, const char **argv) {
  if (argc > 1) {
    std::string file_path = std::string{argv[1]};

    FileScanner file_scanner;
    std::string file_content = file_scanner.GetFileContent(file_path);

    Lexer lexer(file_content);

    try {
      std::vector<Token> tokens = lexer.Lex();
      for (auto token : tokens) {
        std::cout << token << std::endl;
      }
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }

  return 0;
}
