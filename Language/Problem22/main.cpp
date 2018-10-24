#include <gsl/gsl>
#include <iostream>

using ull = unsigned long long;

class Fahrenheit {
public:
    Fahrenheit() : m_degree(0) {
        // Do Nothing
    }

    Fahrenheit(ull degree) : m_degree(degree) {
        // Do Nothing
    }

    double degree() const {
        return m_degree;
    }

    double make_celsius() const {
        return (m_degree - 32) * 5 / 9;
    }

private:
    double m_degree;
};

class Kelvin {
public:
    Kelvin() : m_degree(0) {
        // Do Nothing
    }

    Kelvin(ull degree) : m_degree(degree) {
        // Do Nothing
    }

    double degree() const {
        return m_degree;
    }

    double make_celsius() const {
        return m_degree - 273.15;
    }

private:
    double m_degree;
};

class Celsius {
public:
    Celsius() : m_degree(0) {
        // Do Nothing
    }

    Celsius(ull degree) : m_degree(degree) {
        // Do Nothing
    }

    double degree() const {
        return m_degree;
    }

    double make_celsius() const {
        return m_degree;
    }

    operator Fahrenheit() const {
        return Fahrenheit(m_degree * 9 / 5 + 32);
    }

    operator Kelvin() const {
        return Kelvin(m_degree + 273.15);
    }

private:
    double m_degree;
};

Celsius operator ""_deg(ull degree) {
    return Celsius(degree);
}

Kelvin operator ""_k(ull degree) {
    return Kelvin(degree);
}

Fahrenheit operator ""_f(ull degree) {
    return Fahrenheit(degree);
}

template <typename FROM, typename TO>
TO convert(FROM from) {
    return Celsius(from.make_celsius());
}

int main() {
    Celsius cel = 100_deg;
    Fahrenheit fah = convert<Celsius, Fahrenheit>(cel);
    Kelvin kel = convert<Fahrenheit, Kelvin>(fah);

    std::cout << "Cel: " << cel.degree() 
              << " - Fah: " << fah.degree() 
              << " - Kel: " << kel.degree() << std::endl;
}
