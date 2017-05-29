#ifndef LOCXXATE_H_B86LVQXX
#define LOCXXATE_H_B86LVQXX

#include <experimental/filesystem>
#include <string>
#include <vector>

std::vector<std::experimental::filesystem::path> fetchAllFiles(
    const std::string& defaultDir,
    const std::vector<std::string>& excluded = {});

#endif /* end of include guard: LOCXXATE_H_B86LVQXX */
