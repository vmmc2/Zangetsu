add_library(asm_codegen STATIC
  "asm_codegen_visitor.cpp"
  "asm_codegen_visitor.hpp"
)

target_include_directories(asm_codegen
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
