// #include <gsl/gsl>
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

    while (num1 != num2) {
        int max = num1 > num2 ? num1 : num2;
        int min = num1 < num2 ? num1 : num2;

        num1 = max - min;
        num2 = min;
    }
    std::cout << num1 << std::endl;

    return 0;
}
