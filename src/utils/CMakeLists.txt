add_subdirectory(diagnostics_reporter)
add_subdirectory(file_scanner)

add_library(zangetsu_utils INTERFACE)

target_link_libraries(zangetsu_utils INTERFACE
  diagnostics_reporter
  file_scanner
)
