#ifndef DBIFACE_HPP_B9X1TGFO
#define DBIFACE_HPP_B9X1TGFO

#include <experimental/filesystem>
#include <string>
#include <vector>

struct DBInterface {
    typedef std::vector<std::experimental::filesystem::path> Paths;

    virtual ~DBInterface() = default;
    virtual void store(const Paths& paths) = 0;
    virtual Paths search(const std::string& name) = 0;
    virtual std::size_t count() const noexcept = 0;
};

#endif /* end of include guard: DBIFACE_HPP_B9X1TGFO */
