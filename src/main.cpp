#include <spdlog/fmt/ostr.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <cxxopts.hpp>
#include <experimental/filesystem>
#include <iostream>
#include "locxxate.h"
#include "log.hpp"
#include "timer.h"

std::shared_ptr<spdlog::logger> kDefaultLogger;

void setupLogger(bool verbose) {
    kDefaultLogger = spdlog::stdout_color_mt("locxxate");
}
namespace std {
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const auto& o : v) os << o << " ";
    return os;
}
} // namespace std

void serverMode(cxxopts::Options& opts)
{
    std::vector<std::string> splits;
    if (opts.count("e")) {
        auto s = opts["e"].as<std::string>();
        std::cout << "excluded options " << s << std::endl;
        boost::split(splits, s, boost::is_any_of(","));
    }
    auto t = jrd::time::make_time<std::chrono::milliseconds>();

    info("Root path ={}", opts["r"].as<std::string>());

    info("Finding matches from {} with excludes {}",
         opts["r"].as<std::string>(), splits);
    const auto fAll = fetchAllFiles(opts["r"].as<std::string>(), splits);
    const std::string searched =
        opts.count("s") ? opts["s"].as<std::string>() : "";

    debug("Found {} files ", fAll.size());

    auto it =
        std::find_if(fAll.begin(), fAll.end(), [&searched](const auto& v) {
            return boost::contains(v.filename().string(), searched);
        });

    while (it != fAll.end()) {
        std::cout << *it << std::endl;
        it = std::find_if(++it, fAll.end(), [&searched](const auto& v) {
            return boost::contains(v.filename().string(), searched);
        });
    }
    std::cout << std::fixed << t << " ms" << std::endl;
}

void clientMode(cxxopts::Options& opts)
{
}

int main(int argc, char* argv[]) {
    const std::experimental::filesystem::path execPath{argv[0]};

    const std::string homePath = std::getenv("HOME");
    cxxopts::Options opts(execPath.filename().string(), "Fast? file locate");
    // clang-format off
    opts.add_options("general")
        ("h,help", "help")
        ("v,verbose", "verbose")
        ("m,mode", "mode", cxxopts::value<std::string>()->default_value("server"));
    opts.add_options("server")
        ("e,exclude", "what to exclude", cxxopts::value<std::string>() )
        ("r,root", "root dir", cxxopts::value<std::string>()->default_value(homePath) )
        ("s,search", "searched file/dir", cxxopts::value<std::string>() )
        ("o,output", "database output path", cxxopts::value<std::string>() )
        ;
    opts.add_options("client")
        ("i,input", "database input path", cxxopts::value<std::string>());
    // clang-format on
    opts.parse(argc, argv);

    if (opts.count("h")) {
        std::cout << opts.help({"general", "server"}) << std::endl;
        return EXIT_SUCCESS;
    }
    const bool verbose = opts["v"].as<bool>();
    setupLogger(verbose);

    if ( opts["m"].as<std::string>() == "server") {
        serverMode(opts);
    } else {
        clientMode(opts);
    }

    return EXIT_SUCCESS;
}
