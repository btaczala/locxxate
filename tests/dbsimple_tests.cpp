#include <catch.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <iterator>
#include <map>

#include "dbsimple_file.h"

namespace fs = std::experimental::filesystem;

TEST_CASE("Empty ctor does not throw", "[dbsimple]") {
    REQUIRE_NOTHROW(DBSimpleFile{""});
}

TEST_CASE("simple db from /tmp ", "[dbsimple]") {
    const fs::path rootDBPath = fs::temp_directory_path();
    const fs::path dbFilename = fs::current_path() / "db.db";

    std::ofstream dbFile{dbFilename.c_str()};

    try {
        std::copy(fs::recursive_directory_iterator(rootDBPath),
                  fs::recursive_directory_iterator(),
                  std::ostream_iterator<fs::path>(dbFile));
    } catch (const std::exception&) {
    }

    REQUIRE_FALSE(fs::is_empty(dbFilename));

    DBSimpleFile db{dbFilename.string()};
    CHECK(db.count() != 0);
}

TEST_CASE("simple db from mine dev ", "[dbsimple]") {
    const fs::path rootDBPath = fs::path(TEST_DIR) / "test_data" / "dev.db";
    const std::map<std::string, std::size_t> howMany{{"CMakeLists.txt", 38}};

    REQUIRE_FALSE(fs::is_empty(rootDBPath));

    DBSimpleFile db{rootDBPath.string()};
    REQUIRE(db.count() == 3099);

    for (auto p : howMany) {
        auto filtered = db.search(p.first);
        CHECK(filtered.size() == p.second);
    }
}
