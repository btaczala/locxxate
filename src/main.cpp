#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <cxxopts.hpp>
#include <experimental/filesystem>
#include <iostream>
#include "locxxate.h"
#include "timer.h"

int main(int argc, char *argv[]) {
    const std::experimental::filesystem::path execPath{argv[0]};

    const std::string homePath = std::getenv("HOME");
    cxxopts::Options opts(execPath.filename().string(), "Fast? file locate");
    // clang-format off
    opts.add_options("")
        ("h,help", "help")
        ("e,exclude", "what to exclude", cxxopts::value<std::string>() )
        ("r,root", "root dir", cxxopts::value<std::string>()->default_value(homePath) )
        ("s,search", "searched file/dir", cxxopts::value<std::string>() )
        ;
    // clang-format on
    opts.parse(argc, argv);

    if (opts.count("h")) {
        std::cout << opts.help({""}) << std::endl;
        return EXIT_SUCCESS;
    }

    if (opts.count("e")) {
        auto s = opts["e"].as<std::string>();
        std::cout << "excluded options " << s << std::endl;
    }

    auto t = jrd::time::make_time<std::chrono::milliseconds>();
    const auto fAll = fetchAllFiles(opts["r"].as<std::string>(), {".*modules.*"});
    const std::string searched =
        opts.count("s") ? opts["s"].as<std::string>() : "";

    auto it =
        std::find_if(fAll.begin(), fAll.end(), [&searched](const auto &v) {
            return boost::contains(v.filename().string(), searched);
        });

    while (it != fAll.end()) {
        std::cout << *it << std::endl;
        it = std::find_if(++it, fAll.end(), [&searched](const auto &v) {
            return boost::contains(v.filename().string(), searched);
        });
    }
    std::cout << std::fixed << t << std::endl;
}
