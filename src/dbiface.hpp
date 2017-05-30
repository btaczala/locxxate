#ifndef DBIFACE_HPP_B9X1TGFO
#define DBIFACE_HPP_B9X1TGFO

struct DBInterface {
    virtual ~DBInterface() = default;
    virtual void store(const std::string& filename, const std::string& path) = 0;

    virtual bool open(const std::string& path) = 0;
};

#endif /* end of include guard: DBIFACE_HPP_B9X1TGFO */
