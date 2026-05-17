#include "file_scanner.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <stdexcept>
#include <string>

std::string FileScanner::GetFileContent(std::string file_path) {
  std::filesystem::path source_code_file_path{file_path};

  if (source_code_file_path.extension() != ".c") {
    throw std::runtime_error{std::format(
        "The Zangetsu compiler is a compiler for the C programming language. "
        "Input files must have the '.c' extension. But the file has extension: "
        "{}.\n",
        source_code_file_path.extension().string())};
  }

  std::ifstream file{file_path,
                     std::ios::in | std::ios::binary | std::ios::ate};
  if (!file) {
    throw std::runtime_error{std::format(
        "An error has happened while trying to open the file: {}.\n",
        file_path)};
  }

  std::string file_content;
  file_content.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(file_content.data(), file_content.size());
  file.close();

  return file_content;
}
