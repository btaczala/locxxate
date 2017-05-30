#include "locxxate.h"
#include "log.hpp"

#include <regex.h>
#include <algorithm>
#include <iostream>

std::shared_ptr<spdlog::logger> kDefaultLogger;
namespace fs = std::experimental::filesystem;
std::vector<std::experimental::filesystem::path> fetchAllFiles(
    const std::string& dir, const std::vector<std::string>& excluded) {
    const std::string actualDir = dir.empty() ? "" : dir;

    return filter(loadDirs(actualDir), excluded);
}

std::vector<std::experimental::filesystem::path> loadDirs(
    const std::string& dir) {
    std::vector<std::experimental::filesystem::path> dirs;
    auto it = fs::recursive_directory_iterator(dir);
    try {
        std::copy(it,
                  fs::recursive_directory_iterator(), std::back_inserter(dirs));
    } catch (const std::exception& ex) {
        error("Exception {} thrown while iterating over {}", ex.what(), dir);
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

void setupLogger(bool verbose) {
    kDefaultLogger = spdlog::stdout_color_mt("locxxate");

    if (verbose) {
        kDefaultLogger->set_level(spdlog::level::trace);
    } else {
        kDefaultLogger->set_level(spdlog::level::off);
    }
}
