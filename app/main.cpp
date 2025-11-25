#include <iostream>
#include <string>
#include <vector>

#include "../src/compiler_utils/token.hpp"
#include "../src/file_scanner/file_scanner.hpp"
#include "../src/lexer/lexer.hpp"
#include "../src/parser/parser.hpp"

int main(int argc, const char **argv) {
  // TODO: Separate the main program into two: One for personal use and another
  // to run the tests from the book.
  // TODO: Fix the column displacement issue inside the Lexer.
  if (argc > 1) {
    // If working by youself, use 'argv[1]'.
    // If working with the tests from the 'writing-a-c-compiler-tests' repo, use
    // 'argv[2]'.
    std::string file_path = std::string{argv[2]};

    FileScanner file_scanner;
    std::string file_content = file_scanner.GetFileContent(file_path);

    Lexer lexer(file_content);

    try {
      std::vector<Token> tokens = lexer.Lex();
      for (auto token : tokens) {
        std::cout << token << std::endl;
      }

      Parser parser{tokens};
      std::unique_ptr<AstNode> ast = parser.Parse();

    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      return 1;
    }
  }

  return 0;
}
