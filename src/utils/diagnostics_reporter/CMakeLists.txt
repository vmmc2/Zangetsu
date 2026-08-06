add_library(diagnostics_reporter STATIC
  "diagnostics_reporter.cpp"
  "diagnostics_reporter.hpp"
)

target_include_directories(diagnostics_reporter
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)