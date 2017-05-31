#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <cstring>
#include <memory>
#include <iostream>

extern std::shared_ptr<spdlog::logger> kDefaultLogger;

namespace std {
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (const auto& o : v) os << o << std::endl ;
    return os;
}
}  // namespace std

#define __FILENAME__ \
    (std::strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define debug(fmt, ...)                                           \
    do {                                                          \
        kDefaultLogger->debug("[{}@{}] " fmt, __FILE__, __LINE__, \
                              ##__VA_ARGS__);                     \
    } while (0)
#define warn(fmt, ...)                                            \
    do {                                                          \
        kDefaultLogger->warn("[{}@{}] " fmt, __FILE__, ___LINE__, \
                             ##__VA_ARGS__);                      \
    } while (0)
#define error(fmt, ...)                                           \
    do {                                                          \
        kDefaultLogger->error("[{}@{}] " fmt, __FILE__, __LINE__, \
                              ##__VA_ARGS__);                     \
    } while (0)
#define info(fmt, ...)                                               \
    do {                                                             \
        kDefaultLogger->info("[{}@{}] " fmt, __FILENAME__, __LINE__, \
                             ##__VA_ARGS__);                         \
    } while (0)
