#ifndef FS_HELPERS_HPP_BAQ48BEL
#define FS_HELPERS_HPP_BAQ48BEL

#include <vector>
#include <experimental/filesystem>

void createDirs(const std::vector<std::string>& paths, const std::string& baseDir)
{
    namespace fs = std::experimental::filesystem;
    for(auto v: paths)
    {
        fs::path p = fs::path(baseDir) / fs::path(v);
        fs::create_directories(p);
    }
}

#endif /* end of include guard: FS_HELPERS_HPP_BAQ48BEL */
