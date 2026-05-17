add_library(asm_emitter STATIC
  "asm_emitter.cpp"
  "asm_emitter.hpp"
)

target_include_directories(asm_emitter
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
