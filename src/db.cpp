#include "db.h"
#include "dbsimple_file.h"
#include "locxxate.h"
#include "log.hpp"

DB::DB(std::unique_ptr<DBInterface>&& iface)
    : impl(std::move(iface)) {
}

void DB::create(const std::string& rootDir,
                const std::vector<std::string>& excludes) {
    auto fAll = fetchAllFiles(rootDir, {});
    fAll = filter(fAll, excludes);

    debug("Found {} files ", fAll.size());
    
    impl->store(fAll);

    // auto it =
    // std::find_if(fAll.begin(), fAll.end(), [&searched](const auto& v) {
    // return boost::contains(v.filename().string(), searched);
    //});

    // while (it != fAll.end()) {
    // it = std::find_if(++it, fAll.end(), [&searched](const auto& v) {
    // return boost::contains(v.filename().string(), searched);
    //});
    //}
    // std::cout << std::fixed << t << " ms" << std::endl;
}
