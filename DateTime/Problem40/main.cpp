#include <gsl/gsl>
#include <iostream>

int clip(int input, int min_val, int max_val) {
    return input > max_val ? max_val
         : input < min_val ? min_val
         : input;
}

struct Year {
    int year;

    Year(int year) : year(year) {
        // Do Nothing
    }

    int n_day() const {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        {
            return 366;
        }
        else {
            return 365;
        }
    }

    Year& operator++() {
        year += 1;
        return *this;
    }

    Year operator+(const Year& other) const {
        return { year + other.year };
    }

    bool operator<(const Year& other) const {
        return year < other.year;
    }

    bool operator<=(const Year& other) const {
        return year <= other.year;
    }
};

struct Month {
    int month;
    int year;
    static int table[13];

    Month(int month) : month(month), year(1) {
        // Do Nothing
    }

    Month(int month, int year) : month(clip(month, 1, 12)), year(year) {
        // Do Nothing
    }

    int n_day() const {
        if (month == 2) {
            if (Year(year).n_day() == 366) {
                return 29;
            }
            else {
                return 28;
            }
        }
        return table[month];
    }

    Month& operator++() {
        month += 1;
        return *this;
    }

    Month operator+(const Month& other) const {
        int new_month = month + other.month;
        int new_year = year;
        if (month > 12) {
            new_year += 1;
            new_month = 1;
        }
        return { new_month, new_year };
    }

    bool operator<(const Month& other) const {
        return month < other.month;
    }

    bool operator<=(const Month& other) const {
        return month <= other.month;
    }
};
int Month::table[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
public:
    Date() : days(1), months(1, 2000), years(2000) {
        // Do Nothing
    }

    Date(int p_years, int p_months, int p_days) :
        years(p_years), months(p_months, p_years), days(clip(p_days, 1, months.n_day()))
    {
        // Do Nothing
    }

    int n_day(const Date& other) {
        if (*this < other) {
            return day_between(*this, other);
        }
        else {
            return day_between(other, *this);
        }
    }

    int repr() const {
        return years.year * 10000 + months.month * 100 + days;
    }

    bool operator<(const Date& other) const {
        return repr() < other.repr();
    }

    static int day_between(const Date& start, const Date& end) {
        int num = start.months.n_day() - start.days;
        for (Month m = start.months + 1; m <= 12; ++m) {
            num += m.n_day();
        }
        for (Year y = start.years + 1; y < end.years; ++y) {
            num += y.n_day();
        }
        for (Month m(1, end.years.year); m < end.months; ++m) {
            num += m.n_day();
        }
        num += end.days;
        return num;
    }

private:
    Year years;
    Month months;
    int days;
};

int main() {
    int y1, m1, d1;
    int y2, m2, d2;

    std::cin >> y1 >> m1 >> d1;
    std::cin >> y2 >> m2 >> d2;

    int days = Date(y1, m1, d1).n_day(Date(y2, m2, d2));
    std::cout << days << std::endl;

    return 0;
}
