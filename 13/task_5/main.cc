#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>
#include <filesystem>
#include <string_view>

namespace {
bool isBlank(std::string_view Line) {
  if (Line.empty())
    return true;
  return std::all_of(Line.begin(), Line.end(), [](char C) {
    return std::isspace(static_cast<unsigned char>(C));
  });
}

bool removeBlankLines(const std::filesystem::path &FilePath) {
  const std::filesystem::path TempPath = FilePath.parent_path() / "temp_file.txt";

  std::ifstream InputFile(FilePath);
  if (!InputFile.is_open()) {
    std::cerr << "Error: Could not open file " << FilePath << "\n";
    return false;
  }

  std::ofstream TempFile(TempPath);
  if (!TempFile.is_open()) {
    std::cerr << "Error: Could not create temporary file\n";
    InputFile.close();
    return false;
  }

  std::string Line;
  while (std::getline(InputFile, Line)) {
    if (!isBlank(Line))
      TempFile << Line << "\n";
  }

  InputFile.close();
  TempFile.close();

  std::error_code EC;
  std::filesystem::remove(FilePath, EC);
  if (EC) {
    std::cerr << "Error: Could not remove original file: " << EC.message() << "\n";
    return false;
  }

  std::filesystem::rename(TempPath, FilePath, EC);
  if (EC) {
    std::cerr << "Error: Could not rename temp file: " << EC.message() << "\n";
    return false;
  }

  return true;
}
} // anonymous namespace

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file>\n";
    return EXIT_FAILURE;
  }

  const std::filesystem::path FilePath(argv[1]);
  if (!std::filesystem::exists(FilePath)) {
    std::cerr << "Error: File does not exist: " << FilePath << "\n";
    return EXIT_FAILURE;
  }

  if (!removeBlankLines(FilePath)) {
    return EXIT_FAILURE;
  }

  std::cout << "Successfully processed: " << FilePath << "\n";
  return 0;
}