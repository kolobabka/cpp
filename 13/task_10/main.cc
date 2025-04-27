#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <system_error>

namespace {
std::string toUpperFilename(const std::string &Filename) {
  std::string Result;
  Result.reserve(Filename.size());
  for (char C : Filename) {
    Result.push_back(std::toupper(static_cast<unsigned char>(C)));
  }
  return Result;
}

bool renameFiles(const std::filesystem::path &DirPath) {
  std::error_code EC;
  bool HadErrors = false;

  for (const auto &Entry : std::filesystem::directory_iterator(DirPath, EC)) {
    if (EC) {
      std::cerr << "Error accessing " << Entry.path() << ": " << EC.message() << "\n";
      HadErrors = true;
      continue;
    }

    if (!Entry.is_regular_file()) {
      continue;
    }

    const std::filesystem::path OldPath = Entry.path();
    const std::filesystem::path NewPath = OldPath.parent_path() / toUpperFilename(OldPath.filename().string());

    if (OldPath == NewPath) {
      continue;
    }

    std::filesystem::rename(OldPath, NewPath, EC);
    if (EC) {
      std::cerr << "Error renaming " << OldPath << ": " << EC.message() << "\n";
      HadErrors = true;
    } else {
      std::cout << "Renamed: " << OldPath << " → " << NewPath << "\n";
    }
  }

  return !HadErrors;
}
} // anonymous namespace

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <directory>\n"
              << "Example: " << argv[0] << " /tmp/files\n";
    return 1;
  }

  const std::filesystem::path DirPath(argv[1]);
  if (!std::filesystem::exists(DirPath)) {
    std::cerr << "Error: Directory does not exist: " << DirPath << "\n";
    return 1;
  }

  if (!renameFiles(DirPath)) {
    return 1;
  }

  std::cout << "Renaming completed.\n";
  return 0;
}