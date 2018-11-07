#include <gsl/gsl>
#include <iostream>

int main(int argc, char* argv[])
{
    int arr[10] = { 1, };
    for (int i = 1; i <= 10; ++i) {
        for (int j = i - 1; j > 0; --j) {
            arr[j] = arr[j] + arr[j - 1];
        }

        for (int j = 0; j < i; ++j) {
            std::cout << arr[j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
    