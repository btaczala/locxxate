#include "dbsimple_file.h"
#include "log.hpp"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iterator>
#include <vector>
#include <future>

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

DBInterface::Paths DBSimpleFile::search(const std::string& name) {
    if (not name.empty()) {
        debug("Searching for {}", name);
    } else {
        debug("List all files");
        return _database;
    }
    DBInterface::Paths filtered;

    std::copy_if(_database.begin(), _database.end(),
                 std::back_inserter(filtered), [&name](auto s) {
                     auto fName = s.filename().string();
                     return boost::contains(fName, name);
                 });

    if (filtered.empty()) debug("No entries found");
    return filtered;
}

std::size_t DBSimpleFile::count() const noexcept { return _database.size(); }

ThreadedDBSimpleFile::ThreadedDBSimpleFile(
    const std::string& path,
    std::experimental::optional<std::uint8_t> threadNumer)
    : DBSimpleFile(path) {}

DBInterface::Paths ThreadedDBSimpleFile::search(const std::string& name) {
    if (name.empty()) {
        return _database;
    }

    std::uint8_t threads;
    if (_threads) {
        threads = *_threads;
    } else {
        threads = std::thread::hardware_concurrency();
    }

    debug("Searching for {} on {} threads", name, threads);

    auto fn = [](auto begin, auto end, auto pred) -> DBInterface::Paths {
        DBInterface::Paths paths{};
        std::copy_if(begin, end, std::back_inserter(paths), pred);
        return paths;
    };
     // threads = 4

    auto i = _database.size() / threads;

    auto handle = std::async(std::launch::async);

    auto b = _database.begin();
    auto e = _database.begin() + i;

    return fn(b, e, [&name](auto s) {
        auto fName = s.filename().string();
        return boost::contains(fName, name);
    });
}
