#include <atomic>
#include <iostream>

#include <asio.hpp>

using tcp = asio::ip::tcp;

struct Session {
    static std::atomic<int> ID;

    int id;
    tcp::socket socket;

    Session(tcp::socket socket) : socket(std::move(socket)), id(++ID) {
        // Do Nothing
    }

    template <typename... T>
    void log(T&&... msg) {
        std::cout << '[' << id << "] ";
        (std::cout << ... << msg);
        std::cout << std::endl;
    }

    bool run() {
        std::string input;
        input.resize(1024);

        size_t read = socket.read_some(asio::buffer(input.data(), 1024));
        if (read <= 0) {
            log("Session couldn't read buffer");
            return false;
        }

        int res = -1;
        try {
            res = std::stoi(input);
        } catch(std::invalid_argument& exception) {
            log("Session couldn't convert string to int: ", input);
            return false;
        }

        std::string output;
        if (res % 3 == 0 && res % 5 == 0) {
            output = "FizzBuzz";
        }
        else if (res % 3 == 0) {
            output = "Fizz";
        }
        else if (res % 5 == 0) {
            output = "Buzz";
        }
        else {
            output = input.c_str();
        }

        size_t write = asio::write(socket, asio::buffer(output.data(), output.size()));
        if (write != output.size()) {
            log("Sessino couldn't write buffer: ", output);
            return false;
        }

        return true;
    }
};

std::atomic<int> Session::ID = 0;

struct Server {
    asio::io_service io_service;

    tcp::acceptor acceptor;
    tcp::socket socket;

    Server(short port) :
        io_service(),
        acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
        socket(io_service)
    {
        accept();
    }

    void run() {
        io_service.run();
    }

    void accept() {
        acceptor.async_accept(socket, [&](asio::error_code const& err) {
            if (err) {
                std::cout << "[*] Server couldn't accept socket" << std::endl;
            }
            else {
                Session(std::move(socket)).run();
                accept();
            }
        });
    }
};

int main(int argc, char* argv[])
{
    short port = 333;

    Server server(port);
    server.run();

    return 0;
}
