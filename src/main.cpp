#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <cxxopts.hpp>
#include <experimental/filesystem>
#include <iostream>
#include "locxxate.h"
#include "timer.h"
#include "log.hpp"

std::shared_ptr<spdlog::logger> kDefaultLogger;

void setupLogger(bool verbose)
{
    kDefaultLogger = spdlog::stdout_color_mt("locxxate");
}

int main(int argc, char *argv[]) {
    const std::experimental::filesystem::path execPath{argv[0]};

    const std::string homePath = std::getenv("HOME");
    cxxopts::Options opts(execPath.filename().string(), "Fast? file locate");
    // clang-format off
    opts.add_options("")
        ("h,help", "help")
        ("v,verbose", "verbose")
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
    std::vector<std::string> splits;
    const bool verbose = opts["v"].as<bool>();
    setupLogger(verbose);

    if (opts.count("e")) {
        auto s = opts["e"].as<std::string>();
        std::cout << "excluded options " << s << std::endl;
        boost::split(splits, s, boost::is_any_of(","));
    }

    auto t = jrd::time::make_time<std::chrono::milliseconds>();

    info("Root path ={}", opts["r"].as<std::string>());

    const auto fAll = fetchAllFiles(opts["r"].as<std::string>(), splits);
    const std::string searched =
        opts.count("s") ? opts["s"].as<std::string>() : "";

    std::cout << fAll.size() << std::endl;

    auto it =
        std::find_if(fAll.begin(), fAll.end(), [&searched](const auto &v) {
            return boost::contains(v.filename().string(), searched);
        });

    while (it != fAll.end()) {
        if(verbose) {
            std::cout << *it << std::endl;
        }
        it = std::find_if(++it, fAll.end(), [&searched](const auto &v) {
            return boost::contains(v.filename().string(), searched);
        });
    }
    std::cout << std::fixed << t << " ms" << std::endl;
}
