#ifndef DBIFACE_HPP_B9X1TGFO
#define DBIFACE_HPP_B9X1TGFO

#include <string>
#include <vector>
#include <experimental/filesystem>

struct DBInterface {
    virtual ~DBInterface() = default;
    virtual void store(const std::vector<std::experimental::filesystem::path>& paths) = 0;
};

#endif /* end of include guard: DBIFACE_HPP_B9X1TGFO */
