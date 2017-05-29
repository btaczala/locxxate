#include "locxxate.h"
#include <algorithm>
#include <experimental/filesystem>
#include <iostream>

std::vector<std::string> fetchAllFiles(const std::string& dir) {
    namespace fs = std::experimental::filesystem;
    const std::string actualDir = dir.empty() ? "" : dir;

    std::vector<std::string> dirs;
    fs::path p;
    std::transform(fs::recursive_directory_iterator(dir),
                   fs::recursive_directory_iterator(), std::back_inserter(dirs),
                   [](auto v) -> std::string { return v.path(); });
    std::cout << "entries " << dirs.size() << std::endl;
    return dirs;
}
