#include <benchmark/benchmark.h>
#include "locxxate.h"

namespace fs = std::experimental::filesystem;

void fetch_home_dir(benchmark::State& state) {
    const std::string home{"/tmp"};
    while (state.KeepRunning()) {
        auto all = fetchAllFiles(home);
    }
}

BENCHMARK(fetch_home_dir);
BENCHMARK_MAIN()
