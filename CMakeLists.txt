# The minimum CMake version required to build this project 3.31.
# Otherwise, the whole process will fail.
cmake_minimum_required(VERSION 3.31)


# Project name and its version.
# The first command that actually finds and configures your C++ compiler.
# This is when CMake figures out which compiler is being used: GCC, Clang, or MSVC.
# This command assigns a value to the "CMAKE_CXX_COMPILER_ID" variable.
project(Zangetsu VERSION 1.0.0 LANGUAGES CXX)


# Sets up compiler flags that will be used during the compilation phase of the project.
# Compilation flags are like global rules for your project.
# You want to set them as early as possible, so that all your subdirectories (add_subdirectory)
# and all your targets (add_library, add_executable) inherit these rules.
# Specific flags for GCC and Clang:
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(
    -Wall           # This triggers a large set of warnings that the compiler developers (GCC/Clang) consider obvious and easy to fix.
    -Wextra         # Activates an extra set of warnings that are not covered by the "-Wall" flag.
    -Werror         # Any warning you encounter ("-Wall", "-Wextra", or another) is treated as an error. The compiler refuses to generate an executable.
    -Wswitch-enum   # If you use a "switch" statement in an enum class and forget to handle one of the values ​​(case) — and don't have a default — this flag will yell at you. Useful for the function that converts a TokenType value to its string equivalent.
  )
# Specific flags for MSCV (Microsoft Visual Studio Compiler):
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(
    /W4     # Equivalent to the "-Wall" and "-Wextra" flags.
    /WX     # Equivalent to the "-Werror" flag.
    /w14061 # Warning C4061, which is equivalent to the "-Wswitch-enum" flag from GCC/Clang.
  )
endif()


# Defines the C++ standard used in this project (C++20 in this case).
set(CMAKE_CXX_STANDARD 20)
# If the compiler being used does not support C++20, then the whole 
# project will fail during the configuration phase.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disables specific compiler extensions. It forces you to write "standard" and portable C++. 
# This is good practice to avoid relying on features that only exist in GCC, for example, and 
# which would break the build in Clang or MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)


# Integration with Vcpkg (requires CMAKE_TOOLCHAIN_FILE).
# VSCode will configure this automatically through the 'settings.json' file.
# find_package()


# Enable CTest (to run the tests).
enable_testing()


# Adds the main subdirectories.
# The 'src' subdirectory must come first so that its targets (libraries) are
# defined before 'app' and 'tests' attempt to link against them. In other words,
# the order matters.
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)