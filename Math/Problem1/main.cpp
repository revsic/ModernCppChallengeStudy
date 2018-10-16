#include <gsl/gsl>
#include <iostream>

int main(int argc, char* argv[])
{
    int input = 0;
    std::cin >> input;

    for (int i = 1; i < input; ++i) {
        if (i % 3 == 0 || i % 5 == 0) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    return 0;
}
