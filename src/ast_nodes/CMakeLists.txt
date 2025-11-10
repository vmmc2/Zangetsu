add_library(ast_nodes
  "ast_nodes.cpp"
  "ast_nodes.hpp"
)

target_include_directories(ast_nodes
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)