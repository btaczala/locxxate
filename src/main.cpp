#include "db.h"
#include "dbsimple_file.h"
#include "locxxate.h"
#include "log.hpp"
#include "timer.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <cxxopts.hpp>
#include <experimental/filesystem>
#include <iostream>

void serverMode(cxxopts::Options& opts) {
    DB database{std::make_unique<DBSimpleFile>(opts["o"].as<std::string>())};

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

void clientMode(cxxopts::Options& opts) {
    const std::string searchFile = opts["s"].as<std::string>();
    DB database{std::make_unique<DBSimpleFile>(opts["i"].as<std::string>())};

    debug("Searching for file {}", searchFile);
    auto f = database.search(searchFile);
    std::cout << f << std::endl;
}

int main(int argc, char* argv[]) {
    namespace fs = std::experimental::filesystem;
    const std::experimental::filesystem::path execPath{argv[0]};

    const std::string homePath = std::getenv("HOME");
    const std::string defaultDBPath = homePath / fs::path(".locxxate");
    cxxopts::Options opts(execPath.filename().string(), "Fast? file locate");
    // clang-format off
    opts.add_options("general")
        ("h,help", "help")
        ("v,bVerbose", "bVerbose")
        ("m,mode", "mode", cxxopts::value<std::string>()->default_value("server"));
    opts.add_options("server")
        ("e,exclude", "what to exclude", cxxopts::value<std::string>() )
        ("r,root", "root dir", cxxopts::value<std::string>()->default_value(homePath) )
        ("o,output", "database output path", cxxopts::value<std::string>()->default_value(defaultDBPath));
    opts.add_options("client")
        ("i,input", "database input path", cxxopts::value<std::string>()->default_value(defaultDBPath))
        ("s,search", "searched file/dir", cxxopts::value<std::string>()->default_value("") );
    // clang-format on
    opts.parse(argc, argv);

    if (opts.count("h")) {
        std::cout << opts.help({"general", "server"}) << std::endl;
        return EXIT_SUCCESS;
    }
    const bool bVerbose = opts["v"].as<bool>();
    setupLogger(bVerbose);

    if (opts["m"].as<std::string>() == "server") {
        serverMode(opts);
    } else {
        clientMode(opts);
    }

    return EXIT_SUCCESS;
}
