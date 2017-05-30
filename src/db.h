
#ifndef DB_H_Q3WAYG0M
#define DB_H_Q3WAYG0M

#include <memory>
#include <string>
#include <vector>
#include "dbiface.hpp"

struct DB {
    DB(std::unique_ptr<DBInterface>&& iface); 

    void create(const std::string& rootDir, const std::vector<std::string>& excludes);

   private:
    const std::unique_ptr<DBInterface> impl;
};

#endif /* end of include guard: DB_H_Q3WAYG0M */
