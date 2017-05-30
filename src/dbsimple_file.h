#ifndef DBSIMPLE_FILE_H_P05XBQTN
#define DBSIMPLE_FILE_H_P05XBQTN

#include "dbiface.hpp"

struct DBSimpleFile : public DBInterface {
    DBSimpleFile(const std::string& path);
    virtual void store(
        const std::vector<std::experimental::filesystem::path>& paths) override;

   private:
    const std::string _path;
};

#endif /* end of include guard: DBSIMPLE_FILE_H_P05XBQTN */
