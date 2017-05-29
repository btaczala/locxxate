#include "locxxate.h"
#include <regex.h>
#include <algorithm>
#include <iostream>

std::vector<std::experimental::filesystem::path> fetchAllFiles(
    const std::string& dir, const std::vector<std::string>& excluded) {
    namespace fs = std::experimental::filesystem;
    const std::string actualDir = dir.empty() ? "" : dir;

    std::vector<std::experimental::filesystem::path> dirs;
    fs::path p;
    regex_t exp;
    regmatch_t match;
    const auto filter = [&excluded, &exp, &match](auto fs) {
        for (auto e : excluded) {
            auto s = fs.path().string();
            regcomp(&exp, e.c_str(), REG_EXTENDED);
            if (regexec(&exp, s.c_str(), 1, &match, 0) == 0) {
                return false;
            }
        }
        return true;
    };

    std::copy_if(fs::recursive_directory_iterator(dir),
                 fs::recursive_directory_iterator(), std::back_inserter(dirs),
                 filter);

    std::cout << "entries " << dirs.size() << std::endl;
    return dirs;
}
