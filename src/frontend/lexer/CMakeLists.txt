add_library(lexer STATIC
  "lexer.cpp"
  "lexer.hpp"
)

target_include_directories(lexer
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
