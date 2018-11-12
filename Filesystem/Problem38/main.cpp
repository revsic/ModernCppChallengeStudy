#include <gsl/gsl>
#include <chrono>
#include <filesystem>
#include <functional>
#include <fstream>
#include <iterator>
#include <iostream>

namespace fs = std::filesystem;

struct Hasher {
    std::hash<unsigned long long> hasher;
    
    std::string operator()() const {
        using namespace std::chrono;
        using namespace std::literals;

        auto now = steady_clock::now();
        auto now_ms = now.time_since_epoch() - 0ms;
        return std::to_string(hasher(now_ms.count()));
    }
};

class Logger {
public:
    Logger() : m_filename(m_tmp + m_hasher()), m_ofs(m_filename) {
        // Do Nothing
    }

    ~Logger() {
        if (!m_moved) {
            m_ofs.close();
            fs::remove(m_filename);
        }
    }

    bool Move(const std::string& filepath) {
        m_ofs.close();
        // bool res = fs::copy_file(m_filename, filepath, 
        //                          fs::copy_options::overwrite_existing);
        
        m_ofs.open(filepath);

        std::ifstream ifs(m_filename);
        std::copy(std::istreambuf_iterator<char>(ifs),
                  std::istreambuf_iterator<char>(),
                  std::ostreambuf_iterator<char>(m_ofs));
        ifs.close();

        // if (res && m_ofs.is_open()) {
        if (m_ofs.is_open()) {
            fs::remove(m_filename);

            m_moved = true;
            m_filename = filepath;
        }
        else {
            m_ofs.open(m_filename);
        }
        
        return m_moved;
    }

    template <typename T>
    std::ofstream& operator<<(T&& obj) {
        m_ofs << std::forward<T>(obj);
        return m_ofs;
    }

    const std::string& GetFileName() const {
        return m_filename;
    }

    bool IsMoved() const {
        return m_moved;
    }

private:
    bool m_moved = false;

    std::string m_filename;
    std::ofstream m_ofs;

    static Hasher m_hasher;
    static std::string m_tmp;
};

Hasher Logger::m_hasher;
std::string Logger::m_tmp = "/tmp/log";

int main() {
    std::string filename;
    std::string move_filename = "./moved_log.txt";
    std::string msg = "Hello World !";
    {
        Logger log1;
        filename = log1.GetFileName();
        std::cout << "Log start: " << filename << std::endl;
    }

    if (!fs::exists(filename)) {
        std::cout << filename << " successfully removed" << std::endl;
    }

    {
        Logger log2;
        filename = log2.GetFileName();
        std::cout << "Log start: " << filename << std::endl;

        log2 << msg << std::endl;

        {
            std::string res;
            std::ifstream ifs(filename);

            std::getline(ifs, res);
            std::cout << "Writed msg: " << res << std::endl;
        }

        if (log2.Move(move_filename)) {
            std::cout << "successfully moved" << std::endl;
        }
    }

    if (!fs::exists(filename)) {
        std::cout << filename << " successfully removed" << std::endl;
    }

    if (fs::exists(move_filename)) {
        std::ifstream ifs(move_filename);
        std::cout << "Moved content: " << std::endl;

        std::string res;
        while (std::getline(ifs, res)) {
            std::cout << res << std::endl;
        }
        ifs.close();
    }

    return 0;
}
