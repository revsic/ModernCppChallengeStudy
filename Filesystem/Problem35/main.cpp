#include <gsl/gsl>
#include <iostream>

#ifdef ENABLE_FS
#include <filesystem>

namespace fs = std::filesystem;

using ull = unsigned long long;

ull sizeof_dir(const fs::path& path) {
    if (fs::is_regular_file(path)) {
        return fs::file_size(path);
    }

    ull size = 0;
    if (fs::is_directory(path)) {
        for (auto& dir : fs::directory_iterator(path)) {
            if (dir.is_regular_file()) {
                size += dir.file_size();
            }
            else if (dir.is_directory()) {
                size += sizeof_dir(dir.path());
            }
        }
    }

    return size;
}

int main(int argc, char* argv[])
{
    std::string given;
    std::cin >> given;

    fs::path path(given);
    if (!fs::exists(path)) {
        std::cout << "invalid file path" << std::endl;
        return 1;
    }

    ull size = sizeof_dir(path);
    std::cout << "size: " << size << std::endl;

    return 0;
}
    
#else

int main() {
    std::cout << "set EnableFS in cmake" << std::endl;
    return 0;
}

#endif