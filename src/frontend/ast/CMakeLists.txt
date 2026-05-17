add_library(ast STATIC
  "ast_nodes.cpp"
  "ast_nodes.hpp"
  "i_ast_visitor.hpp"
  "pretty_printer_visitor.cpp"
  "pretty_printer_visitor.hpp"
)

target_include_directories(ast
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
