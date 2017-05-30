
#include "db.h"
#include "locxxate.h"

DB::DB(const std::string& path) {
    impl->open(path);
}

void DB::search()
{
}
