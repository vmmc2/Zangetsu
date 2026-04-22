add_library(ast_nodes
  "assembly_ast_nodes.hpp"
  "assembly_emitter.cpp"
  "assembly_emitter.hpp"
  "assembly_generator_visitor.hpp"
  "assembly_generator_visitor.cpp"
  "ast_nodes.cpp"
  "ast_nodes.hpp"
  "i_ast_visitor.hpp"
  "pretty_printer_visitor.cpp"
  "pretty_printer_visitor.hpp"
)

target_include_directories(ast_nodes
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)