add_library(file_scanner
  "file_scanner.cpp"
  "file_scanner.hpp"
)

target_include_directories(file_scanner
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)