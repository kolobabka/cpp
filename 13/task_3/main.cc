#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <iomanip>
#include <pwd.h>
#include <algorithm>
#include <cstring>

struct ProcInfo final {
    std::string Name;
    pid_t Pid;
    std::string Status;
    std::string Owner;
};

std::string getProcName(pid_t Pid) {
    std::ifstream PI("/proc/" + std::to_string(Pid) + "/comm");
    std::string Name;
    if (PI.is_open ())
        std::getline(PI, Name);

    return Name.empty () ? "Unknown" : Name;
}

std::string getProcStatus (pid_t Pid) {
    std::ifstream PI("/proc/" + std::to_string(Pid) + "/status");
    std::string Line;
    while (std::getline(PI, Line))
        if (Line.rfind("State:", 0) == 0)
            return Line.substr (std::strlen ("State: "));

    return "Unknown";
}

std::string getProcOwner (pid_t Pid) {
    struct stat StatBuf;
    std::string Path = "/proc/" + std::to_string(Pid);
    if (stat(Path.c_str(), &StatBuf) == 0) {
        auto* pw = getpwuid(StatBuf.st_uid);
        if (pw)
            return pw->pw_name;
    }

    return "Unknown";
}

std::vector<ProcInfo> getProcsInfo () {
    std::vector<ProcInfo> Res;
    DIR *Dir = opendir ("/proc");
    if (!Dir) {
        std::cerr << "Can't open /proc" << std::endl;
        return Res;
    }

    struct dirent* Entry = nullptr;
    while ((Entry = readdir (Dir)) != nullptr) {
        if (Entry->d_type == DT_DIR &&
          std::all_of(Entry->d_name, Entry->d_name + std::strlen(Entry->d_name), ::isdigit)) {
            ProcInfo Info;
            Info.Pid = static_cast<pid_t>(std::stoi(Entry->d_name));
            Info.Name = getProcName(Info.Pid);
            Info.Status = getProcStatus(Info.Pid);
            Info.Owner = getProcOwner(Info.Pid);

            Res.push_back(Info);
        }
    }

    closedir (Dir);
    return Res;
}

int main () {
    std::vector<ProcInfo> Procs = getProcsInfo ();
    std::cout << std::setw (40) << "Name"
              << std::setw (16) << "Pid"
              << std::setw (16) << "Status"
              << std::setw (32) << "Owner"
              << std::endl;
    for (auto &&Proc : Procs)
        std::cout << std::setw (40) << Proc.Name
                  << std::setw (16) << Proc.Pid
                  << std::setw (16) << Proc.Status
                  << std::setw (32) << Proc.Owner
                  << std::endl;
}

