add_subdirectory(asm_ast)
add_subdirectory(asm_codegen)
add_subdirectory(asm_emitter)
add_subdirectory(tacky_ast)
add_subdirectory(tacky_codegen)

add_library(zangetsu_backend INTERFACE)

target_link_libraries(zangetsu_backend INTERFACE
  asm_ast
  asm_codegen
  asm_emitter
  tacky_ast
  tacky_codegen
)