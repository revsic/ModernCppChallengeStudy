#include <gsl/gsl>
#include <chrono>
#include <iostream>

struct Months {
    int tick;
    static int n_days[13]; 
};
int Months::n_days[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct Days {
    int tick;

    Days() : tick(0) {
        // Do Nothiing
    }

    Days(int tick) : tick(tick) {
        // Do Nothing
    }

    Days(const Months& months) : 
};

class Date {
public:
    Date() : days(0), months(0), years(0) {
        // Do Nothing
    }

    Date(int days, int months, int years) :
        days(days), months(months), years(years)
    {
        // Do Nothing
    }

    

private:
    int days;
    int months;
    int years;

};