#include <any>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../src/backend/asm_ast/asm_ast_nodes.hpp"
#include "../src/backend/asm_codegen/asm_codegen_visitor.hpp"
#include "../src/backend/asm_emitter/asm_emitter.hpp"
#include "../src/frontend/ast/ast_nodes.hpp"
#include "../src/frontend/ast/pretty_printer_visitor.hpp"
#include "../src/frontend/lexer/lexer.hpp"
#include "../src/frontend/parser/parser.hpp"
#include "../src/frontend/token.hpp"
#include "../src/utils/diagnostics_reporter/diagnostics_reporter.hpp"
#include "../src/utils/file_scanner/file_scanner.hpp"

/*
The testing script per compilation stage written by Nora Sandler tests the
compiler through the following command:
./path/to/your/compiler --lex /path/to/file.c

In this scenario, the variable 'argc' is 3 and the variable 'argv' holds the
following values: argv[0] = "./path/to/your/compiler" argv[1] = "--lex" argv[2]
= "/path/to/file.c"

However, the testing script per chapter tests the compiler through the following
command:
./path/to/your/compiler /path/to/file.c

In this scenario, the variable 'argc' is 2 and the variable 'argv' holds the
following values: argv[0] = "./path/to/your/compiler" argv[1] =
"/path/to/file.c"
*/
int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cerr << std::format("Correct Use: {} [flags] <file.c>", argv[0])
              << std::endl;
    return 1;
  } else {
    // std::string file_path = std::string{argv[2]};
    std::string file_path;
    bool only_lex = false;
    bool only_parse = false;
    bool only_codegen = false;
    bool emit_assembly = false;

    for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];

      if (arg == "--lex") {
        only_lex = true;
      } else if (arg == "--parse") {
        only_parse = true;
      } else if (arg == "--codegen") {
        only_codegen = true;
      } else if (arg == "-S") {
        emit_assembly = true;
      } else {
        // If it isn't a flag, assume it is the source file.
        file_path = arg;
      }
    }

    if (file_path.empty()) {
      std::cerr << "[Error]: No source file was specified." << std::endl;
      return 1;
    }

    FileScanner file_scanner;
    std::string file_content = file_scanner.GetFileContent(file_path);

    Lexer lexer(file_content);

    try {
      std::vector<Token> tokens = lexer.Lex();
      for (auto token : tokens) {
        std::cout << token << std::endl;
      }
      if (only_lex) {
        return 0;
      }

      Parser parser{tokens};
      std::unique_ptr<ProgramNode> ast = parser.Parse();

      PrettyPrinterVisitor pretty_printer;
      pretty_printer.VisitProgramNode(ast.get());

      const std::string &pretty_ast = pretty_printer.ast();
      std::cout << pretty_ast << std::endl;
      if (only_parse) {
        return 0;
      }

      AssemblyCodeGenVisitor assembly_code_generator;
      Program assembly_program = std::any_cast<Program>(
          assembly_code_generator.VisitProgramNode(ast.get()));
      if (only_codegen) {
        return 0;
      }

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

      std::string exe_path = file_path;
      dot_pos = exe_path.find_last_of('.');
      if (dot_pos != std::string::npos) {
        exe_path = exe_path.substr(0, dot_pos);
      }

      std::string gcc_command =
          std::format("gcc {} -o {}", assembly_file_path, exe_path);
      int gcc_status = std::system(gcc_command.c_str());

      if (gcc_status != 0) {
        throw std::runtime_error{
            std::format("Could not generate the executable: {}", exe_path)};
      }

    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      return 1;
    }
  }

  return 0;
}
