add_library(static_analyzer
  "static_analyzer.cpp"
  "static_analyzer.hpp"
)

target_include_directories(static_analyzer
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)