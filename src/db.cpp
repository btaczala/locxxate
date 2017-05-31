#include "db.h"
#include "dbsimple_file.h"
#include "locxxate.h"
#include "log.hpp"

DB::DB(std::unique_ptr<DBInterface>&& iface) : impl(std::move(iface)) {}

void DB::create(const std::string& rootDir,
                const std::vector<std::string>& excludes) {
    auto fAll = fetchAllFiles(rootDir, {});
    fAll = filter(fAll, excludes);

    debug("Found {} files ", fAll.size());
    impl->store(fAll);
}

std::vector<std::string> DB::search(const std::string& name) {
    auto paths = impl->search(name);

    std::vector<std::string> sPaths;

    std::transform(paths.begin(), paths.end(), std::back_inserter(sPaths),
                   [](auto v) { return v.string(); });

    return sPaths;
}
