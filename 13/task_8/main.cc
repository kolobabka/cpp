#include <chrono>
#include <filesystem>
#include <iostream>
#include <system_error>

namespace {
bool removeOldFiles(const std::filesystem::path &DirPath,
                          const std::chrono::system_clock::time_point &CutoffTime) {
  std::error_code EC;
  bool HadErrors = false;

  for (const auto &Entry : std::filesystem::directory_iterator(DirPath, EC)) {
    if (EC) {
      std::cerr << "Error accessing " << Entry.path() << ": " << EC.message() << "\n";
      HadErrors = true;
      continue;
    }

    auto LastWriteTime = std::filesystem::last_write_time(Entry, EC);
    if (EC) {
      std::cerr << "Error getting mtime for " << Entry.path() << ": " << EC.message() << "\n";
      HadErrors = true;
      continue;
    }

    auto LastWriteTimeSys = std::chrono::file_clock::to_sys(LastWriteTime);
    if (LastWriteTimeSys < CutoffTime) {
      std::filesystem::remove_all(Entry.path(), EC);
      if (EC) {
        std::cerr << "Error removing " << Entry.path() << ": " << EC.message() << "\n";
        HadErrors = true;
      } else {
        std::cout << "Removed: " << Entry.path() << "\n";
      }
    }
  }

  return !HadErrors;
}
} // anonymous namespace

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <directory> <days> <hours>\n"
              << "Example: " << argv[0] << " /tmp/backups 30 0  (delete files older than 30 days)\n";
    return 1;
  }

  const std::filesystem::path DirPath(argv[1]);
  if (!std::filesystem::exists(DirPath)) {
    std::cerr << "Error: Directory does not exist: " << DirPath << "\n";
    return 1;
  }

  const int Days = std::stoi(argv[2]);
  const int Hours = std::stoi(argv[3]);
  const auto CutoffTime = std::chrono::system_clock::now() - std::chrono::hours(24 * Days + Hours);

  if (!removeOldFiles(DirPath, CutoffTime)) {
    return 1;
  }

  std::cout << "Cleanup completed.\n";
  return 0;
}