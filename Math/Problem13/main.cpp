#include <gsl/gsl>
#include <iostream>

int main(int argc, char* argv[])
{
    double sum = 1;
    for (int i = 1; i <= 1000; ++i) {
        double n = 1 / (2. * i + 1);
        
        if (i % 2) {
            sum -= n;
        }
        else {
            sum += n;
        }
    }

    std::cout << sum * 4. << std::endl;
    return 0;
}
