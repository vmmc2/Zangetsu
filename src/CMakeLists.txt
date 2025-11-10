add_subdirectory(ast_nodes)
add_subdirectory(code_generation)
add_subdirectory(compiler_utils)
add_subdirectory(file_scanner)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(static_analyzer)

add_library(zangetsu_lib INTERFACE)

target_link_libraries(zangetsu_lib
  INTERFACE
    ast_nodes
    code_generation
    compiler_utils
    file_scanner
    lexer
    parser
    static_analyzer
)