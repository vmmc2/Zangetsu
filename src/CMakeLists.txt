add_subdirectory(backend)
add_subdirectory(frontend)
add_subdirectory(utils)

add_library(zangetsu_lib INTERFACE)

target_link_libraries(zangetsu_lib
  INTERFACE
    zangetsu_backend
    zangetsu_frontend
    zangetsu_utils
)
