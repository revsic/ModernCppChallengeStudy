#include <gsl/gsl>
#include <iostream>
#include <regex>

int main() {
    std::string given;
    std::getline(std::cin, given);

    std::regex dot_sep("([0-9]{2})\\.([0-9]{2})\\.([0-9]{4})");
    std::regex line_sep("([0-9]{2})\\-([0-9]{2})\\-([0-9]{4})");

    std::string format = "$3-$2-$1";
    std::string repl_dotsep = std::regex_replace(given, dot_sep, format);
    std::string repl = std::regex_replace(repl_dotsep, line_sep, format);

    std::cout << repl << std::endl;
}