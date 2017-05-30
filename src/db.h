
#ifndef DB_H_Q3WAYG0M
#define DB_H_Q3WAYG0M

#include <memory>
#include <string>
#include "dbiface.hpp"

struct DB {
    DB(const std::string& path);

    void search();

   private:
    std::unique_ptr<DBInterface> impl;
};

#endif /* end of include guard: DB_H_Q3WAYG0M */
