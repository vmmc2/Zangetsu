add_library(parser
  "parser.cpp"
  "parser.hpp"
)

target_include_directories(parser
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)