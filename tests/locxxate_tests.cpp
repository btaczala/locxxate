#include <catch.hpp>
#include "fs_helpers.hpp"
#include "locxxate.h"
namespace fs = std::experimental::filesystem;

TEST_CASE("Simple load dirs", "[loadDirs]") {
    const std::vector<std::string> paths{"test", "test/one", "test/two"};
    fs::path base_dir{fs::current_path() / fs::path("test_data_445")};
    fs::create_directory(base_dir);
    createDirs(paths, base_dir);

    auto v = loadDirs(base_dir);

    REQUIRE(v.size() == paths.size());
}

TEST_CASE("filter dirs", "[loadDirs],[filter]") {
    const std::vector<std::string> paths{"test", "test/one", "test/two"};
    fs::path base_dir{fs::current_path() / fs::path("test_data_445")};
    fs::create_directory(base_dir);
    createDirs(paths, base_dir);

    auto v = loadDirs(base_dir);

    v = filter(v, {"one"});
    REQUIRE(v.size() == paths.size() - 1);

    v = filter(v, paths);
    REQUIRE(v.size() == 0);
}
