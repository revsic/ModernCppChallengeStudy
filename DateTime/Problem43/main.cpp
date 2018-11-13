#include <gsl/gsl>
#include <chrono>
#include <iostream>
#include <iomanip>

#include <stdlib.h>

std::tm gen_time(int year, int month, int day, int hour, int min, int sec) {
    std::tm timeinfo;
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = min;
    timeinfo.tm_sec = sec;
    return timeinfo;
}

void print_time(std::tm& timeinfo, const std::vector<std::string>& vec) {
    std::time_t t = std::mktime(&timeinfo);
    std::cout << std::put_time(std::localtime(&t), "%c %Z") << '\n';

    std::string tz_env = "TZ=";
    for (auto const& tz : vec) {
        putenv((tz_env + tz).data());
        std::cout << std::put_time(std::localtime(&t), "%c %Z") << '\n';
    }
}

int main() {
    int year, month, day, hour, min, sec;
    std::cout << "Meeting time in kst: ";
    std::cin >> year >> month >> day >> hour >> min >> sec;

    int num;
    std::cout << "Num time zone: ";
    std::cin >> num;

    std::vector<std::string> vec;
    for (int i = 0; i < num; ++i) {
        std::string str;
        std::cin >> str;
        vec.emplace_back(std::move(str));
    }

    std::tm timeinfo = gen_time(year, month, day, hour, min, sec);
    print_time(timeinfo, vec);

    return 0;
}