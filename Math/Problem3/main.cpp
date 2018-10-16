// #include <gsl/gsl>
#include <iostream>
#include <memory>
#include <numeric>

int main(int argc, char* argv[])
{
    int len = 0;
    std::cout << "len: ";
    std::cin >> len;

    if (len < 2) {
        std::cout << "[*] length should be bigger than two" << std::endl;
        return 1;
    }

    int num1 = 0;
    int num2 = 0;
    std::cout << "nums: ";
    std::cin >> num1 >> num2;

    auto log_negative_exception = [] { 
        std::cout << "[*] number should be positive" << std::endl; 
    };

    if (num1 <= 0 || num2 <= 0) {
        log_negative_exception();
        return 1;
    }

    int lcm = num1 * num2 / std::gcd(num1, num2);
    for (int i = 2; i < len; ++i) {
        std::cin >> num1;
        if (num1 <= 0) {
            log_negative_exception();
            return 1;
        }

        lcm = lcm * num1 / std::gcd(lcm, num1);
    }
    
    std::cout << "lcm: " << lcm << std::endl;
    return 0;
}
