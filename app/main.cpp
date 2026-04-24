#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../src/ast_nodes/assembly_ast_nodes.hpp"
#include "../src/ast_nodes/assembly_emitter.hpp"
#include "../src/ast_nodes/assembly_generator_visitor.hpp"
#include "../src/ast_nodes/ast_nodes.hpp"
#include "../src/ast_nodes/pretty_printer_visitor.hpp"
#include "../src/compiler_utils/token.hpp"
#include "../src/file_scanner/file_scanner.hpp"
#include "../src/lexer/lexer.hpp"
#include "../src/parser/parser.hpp"

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

      Parser parser{tokens};
      std::unique_ptr<ProgramNode> ast = parser.Parse();

      PrettyPrinterVisitor pretty_printer;
      pretty_printer.VisitProgramNode(ast.get());

      const std::string &pretty_ast = pretty_printer.ast();
      std::cout << pretty_ast << std::endl;

      AssemblyGeneratorVisitor assembly_generator;
      Program assembly_program = std::any_cast<Program>(
          assembly_generator.VisitProgramNode(ast.get()));

      AssemblyEmitter assembly_emitter;
      std::string assembly_code = assembly_emitter.Emit(assembly_program);

      std::cout << assembly_code << std::endl;

      std::string assembly_file_path = file_path;
      auto dot_pos = assembly_file_path.find_last_of('.');
      if (dot_pos != std::string::npos) {
        assembly_file_path = assembly_file_path.substr(0, dot_pos) + ".s";
      } else {
        assembly_file_path += ".s";
      }

      std::ofstream assembly_file{assembly_file_path};
      if (assembly_file.is_open()) {
        assembly_file << assembly_code << "\n";
        assembly_file.close();
      } else {
        throw std::runtime_error{std::format(
            "Could not create the Assembly file: {}", assembly_file_path)};
      }
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      return 1;
    }
  }

  return 0;
}
