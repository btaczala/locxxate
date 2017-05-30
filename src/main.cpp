#include <spdlog/fmt/ostr.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <cxxopts.hpp>
#include <experimental/filesystem>
#include <iostream>

#include "db.h"
#include "locxxate.h"
#include "log.hpp"
#include "timer.h"
#include "dbsimple_file.h"

namespace std {
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const auto& o : v) os << o << " ";
    return os;
}
}  // namespace std

void serverMode(cxxopts::Options& opts) {
    DB database { std::make_unique<DBSimpleFile>(opts["o"].as<std::string>()) };

    std::vector<std::string> splits;
    if (opts.count("e")) {
        auto s = opts["e"].as<std::string>();
        std::cout << "excluded options " << s << std::endl;
        boost::split(splits, s, boost::is_any_of(","));
    }

    info("Root path ={}", opts["r"].as<std::string>());

    info("Finding matches from {} with excludes {}",
         opts["r"].as<std::string>(), splits);
    database.create(opts["r"].as<std::string>(), splits);
}

void clientMode(cxxopts::Options& opts) {}

int main(int argc, char* argv[]) {
    namespace fs = std::experimental::filesystem;
    const std::experimental::filesystem::path execPath{argv[0]};

    const std::string homePath = std::getenv("HOME");
    const std::string defaultOutputDB =  homePath / fs::path(".locxxate");
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
        ("o,output", "database output path", cxxopts::value<std::string>()->default_value(defaultOutputDB) )
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

    if (opts["m"].as<std::string>() == "server") {
        serverMode(opts);
    } else {
        clientMode(opts);
    }

    return EXIT_SUCCESS;
}
