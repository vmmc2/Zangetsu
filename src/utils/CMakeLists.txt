add_subdirectory(file_scanner)

add_library(zangetsu_utils INTERFACE)

target_link_libraries(zangetsu_utils INTERFACE
  file_scanner
)
