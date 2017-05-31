#include <benchmark/benchmark.h>
#include "dbsimple_file.h"
#include "locxxate.h"

namespace fs = std::experimental::filesystem;

void fetch_home_dir(benchmark::State& state) {
    const std::string home{"/tmp"};
    while (state.KeepRunning()) {
        auto all = fetchAllFiles(home);
    }
}

void fetch_simple_dev_db(benchmark::State& state) {
    const std::string home{"/tmp"};
    while (state.KeepRunning()) {
        const fs::path rootDBPath = fs::path(TEST_DIR) / "test_data" / "dev.db";
        benchmark::DoNotOptimize(DBSimpleFile{rootDBPath.string()});
    }
}

void search_simple(benchmark::State& state) {
    const std::string home{"/tmp"};
    const fs::path rootDBPath = fs::path(TEST_DIR) / "test_data" / "dev.db";
    DBSimpleFile db{rootDBPath.string()};
    while (state.KeepRunning()) {
        auto v = db.search("CMakeLists.txt");
        benchmark::DoNotOptimize(v);
    }
}

void search_simple_threaded(benchmark::State& state) {
    const std::string home{"/tmp"};
    const fs::path rootDBPath = fs::path(TEST_DIR) / "test_data" / "dev.db";
    ThreadedDBSimpleFile db{rootDBPath.string()};
    while (state.KeepRunning()) {
        auto v = db.search("CMakeLists.txt");
        benchmark::DoNotOptimize(v);
    }
}

BENCHMARK(fetch_home_dir);
BENCHMARK(fetch_simple_dev_db);
BENCHMARK(search_simple);
int main(int argc, char** argv) {
    setupLogger(false);
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
