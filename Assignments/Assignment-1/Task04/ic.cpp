#include <iostream>

int main() {
    int totalPaise = 3550;
    int trips = 4;
    double wrongAvg = totalPaise / trips;
    double rightAvg = static_cast<double>(totalPaise) / trips;
    std::cout << "Integer division: " << wrongAvg << '\n';
    std::cout << "With static_cast: " << rightAvg << '\n';

    unsigned int minBalance = 5000U;
    int testBalance = -100;
    std::cout << "Safe signed comparison: "
              << (testBalance < static_cast<int>(minBalance) ? "below minimum" : "ok") << '\n';

    double rawFare{36.0};
    long long farePaise{static_cast<long long>(rawFare * 100.0)};
    std::cout << "Brace-initialized paise: " << farePaise << '\n';
    return 0;
}
