#include <iostream>
#include <asio.hpp>

int main(int argc, char* argv[])
{
    using resolver = asio::ip::tcp::resolver;

    asio::io_service io_service;
    resolver resolve(io_service);

    std::string input;
    std::cin >> input;

    resolve.async_resolve(input, "https", 
        [](asio::error_code const& err, resolver::iterator iter) {
            if (err) {
                std::cout << "Error occured: " << err << std::endl;
                return;
            }

            std::cout << "Result:" << std::endl;
            for(; iter != resolver::iterator(); ++iter) {
                asio::ip::tcp::endpoint endpoint = *iter;
                std::cout << endpoint << std::endl;
            }
        });

    io_service.run();
    return 0;
}
