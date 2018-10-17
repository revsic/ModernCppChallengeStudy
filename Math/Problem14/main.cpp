#include <gsl/gsl>
#include <iostream>

int main(int argc, char* argv[])
{
    std::string input;
    std::cin >> input;

    int num = 0;
    int unit = 1;
    int valid = -1;

    for (char c : input) {
        if (c >= '0' && c <= '9') {
            c -= '0';
            if (unit < 10) {
                num += unit * c;
                unit += 1;
            }
            else {
                valid = c;
                break;
            }
        }
        
    }

    if (unit != 10) {
        std::cout << "usage: [STR_CONTAINS_10_INT]" << std::endl;
        return 1;
    }

    const char* result = nullptr;
    if (valid == num % 11) {
        result = "valid";
    }
    else {
        result = "invalid";
    }

    std::cout << result << std::endl;
    return 0;
}
