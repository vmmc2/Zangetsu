add_library(code_generation
  "codegen.cpp"
  "codegen.hpp"
)

target_include_directories(code_generation
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)