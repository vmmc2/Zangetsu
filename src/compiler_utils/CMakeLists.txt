add_library(compiler_utils
  "token_type.cpp"
  "token_type.hpp"
  "token.cpp"
  "token.hpp"
)

target_include_directories(compiler_utils
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)