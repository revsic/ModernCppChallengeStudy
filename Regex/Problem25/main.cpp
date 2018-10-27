#include <gsl/gsl>
#include <iostream>

int main() {
    std::string given;
    std::getline(std::cin, given);

    bool capital = true;
    for (auto& chr : given) {
        if (chr == ' ') {
            capital = true;
        }
        else if (capital) {
            chr = std::toupper(chr);
            capital = false;
        }
        else {
            chr = std::tolower(chr);
        }
    }

    std::cout << given << std::endl;
    return 0;
}