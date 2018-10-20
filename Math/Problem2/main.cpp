#include <gsl/gsl>
#include <iostream>

int main(int argc, char* argv[])
{
    int num1 = 0;
    int num2 = 0;
    std::cin >> num1 >> num2;

    if (num1 <= 0 || num2 <= 0) {
        std::cout << "usage: [POSITIVE_NUM] [POSITIVE_NUM]" << std::endl;
        return 1;
    }

    do {
        if (num1 > num2) {
            std::swap(num1, num2);
        }
        num2 %= num1;
    } while (num2 != 0);
    
    // std::gcd(num1, num2)
    std::cout << num1 << std::endl;
    return 0;
}
