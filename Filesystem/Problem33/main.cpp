#include <gsl/gsl>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    std::string path;
    std::cin >> path;

    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        return 1;
    }

    std::string total;
    std::string result;
    while (std::getline(ifs, result)) {
        if (auto iter = std::find_if(result.begin(), result.end(), 
                                     [](char c) { return !std::iswspace(c); });
            iter != result.end())
        {
            total += result + '\n';
        }
    }
    ifs.close();

    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        return 1;
    }

    ofs << total;
    ofs.close();

    return 0;
}
    