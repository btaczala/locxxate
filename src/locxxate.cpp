#include "locxxate.h"
#include <algorithm>
#include <iostream>
#include <regex>

std::vector<std::experimental::filesystem::path> fetchAllFiles(
    const std::string& dir, const std::vector<std::string>& excluded) {
    namespace fs = std::experimental::filesystem;
    const std::string actualDir = dir.empty() ? "" : dir;

    std::vector<std::experimental::filesystem::path> dirs;
    fs::path p;
    auto filter = [&excluded](auto fs) {
        for (auto e : excluded) {
            const std::regex reg{e, std::regex_constants::basic};
            auto s = fs.path().string();
            if (std::regex_search(s, reg)) {
                return true;
            }
        }
        return false;
    };
    std::copy_if(fs::recursive_directory_iterator(dir),
                 fs::recursive_directory_iterator(), std::back_inserter(dirs),
                 filter);

    std::cout << "entries " << dirs.size() << std::endl;
    return dirs;
}
