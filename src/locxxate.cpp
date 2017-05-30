#include "locxxate.h"
#include <regex.h>
#include <algorithm>
#include <iostream>

namespace fs = std::experimental::filesystem;
std::vector<std::experimental::filesystem::path> fetchAllFiles(
    const std::string& dir, const std::vector<std::string>& excluded) {
    const std::string actualDir = dir.empty() ? "" : dir;

    return filter(loadDirs(actualDir), excluded);
}

std::vector<std::experimental::filesystem::path> loadDirs(
    const std::string& dir) {
    std::vector<std::experimental::filesystem::path> dirs;
    try {
        std::copy(fs::recursive_directory_iterator(dir),
                  fs::recursive_directory_iterator(), std::back_inserter(dirs));
    } catch (const std::exception& ex) {
    }

    return dirs;
}
std::vector<std::experimental::filesystem::path> filter(
    const std::vector<std::experimental::filesystem::path>& entries,
    const std::vector<std::string>& excluded) {
    std::vector<std::experimental::filesystem::path> dirs;
    fs::path p;

    regex_t exp;
    regmatch_t match;
    const auto filter = [&excluded, &exp, &match](auto fs) {
        for (auto e : excluded) {
            auto s = fs.string();
            regcomp(&exp, e.c_str(), REG_EXTENDED);
            if (regexec(&exp, s.c_str(), 1, &match, 0) == 0) {
                return false;
            }
        }
        return true;
    };
    std::copy_if(entries.begin(), entries.end(), std::back_inserter(dirs),
                 filter);

    return dirs;
}
