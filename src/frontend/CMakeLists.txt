add_subdirectory(ast)
add_subdirectory(lexer)
add_subdirectory(parser)

add_library(zangetsu_frontend 
  STATIC
    "token_type.cpp"
    "token_type.hpp"
    "token.cpp"
    "token.hpp"
)

target_link_libraries(zangetsu_frontend PUBLIC
  ast
  lexer
  parser
)
