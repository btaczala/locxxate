#include "dbsimple_file.h"
#include "log.hpp"

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iterator>
#include <vector>

namespace fs = std::experimental::filesystem;

struct DBEntry {
    std::string _filename;
    std::string _filepath;
};

DBSimpleFile::DBSimpleFile(const std::string& path) : _path(path) {
    std::ifstream file;

    file.open(path.c_str());


    std::copy(std::istream_iterator<fs::path>(file),
              std::istream_iterator<fs::path>(), std::back_inserter(_database));

    debug("Read entries {}", _database.size());
}

void DBSimpleFile::store(
    const std::vector<std::experimental::filesystem::path>& paths) {
    debug("Storing entries in {}. Size = {}", _path, paths.size());

    std::ofstream f;
    f.open(_path, std::ios::trunc);
    std::copy(paths.begin(), paths.end(),
                   std::ostream_iterator<std::experimental::filesystem::path>(f));

    f.close();
}
