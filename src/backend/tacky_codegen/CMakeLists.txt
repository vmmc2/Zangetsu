add_library(tacky_codegen STATIC
  "tacky_codegen_visitor.cpp"
  "tacky_codegen_visitor.hpp"
)

target_include_directories(tacky_codegen
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)