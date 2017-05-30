#include <spdlog/spdlog.h>
#include <cstring>
#include <memory>

extern std::shared_ptr<spdlog::logger> kDefaultLogger;

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
