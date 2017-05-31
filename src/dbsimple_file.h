#ifndef DBSIMPLE_FILE_H_P05XBQTN
#define DBSIMPLE_FILE_H_P05XBQTN

#include <experimental/optional>
#include "dbiface.hpp"

struct DBSimpleFile : public DBInterface {
    DBSimpleFile(const std::string& path);
    virtual void store(const Paths& paths) override;
    std::size_t count() const noexcept override;
    virtual Paths search(const std::string& name) override;

   protected:
    const std::string _path;
    std::vector<std::experimental::filesystem::path> _database;
};

struct ThreadedDBSimpleFile : public DBSimpleFile {
    ThreadedDBSimpleFile(
        const std::string& path,
        std::experimental::optional<std::uint8_t> threadNumer = {});
    virtual Paths search(const std::string& name) override;

   private:
    std::experimental::optional<std::uint8_t> _threads;
};

#endif /* end of include guard: DBSIMPLE_FILE_H_P05XBQTN */
