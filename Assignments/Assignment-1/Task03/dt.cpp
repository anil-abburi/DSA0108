#include <climits>
#include <iomanip>
#include <iostream>

int main() {
    std::cout << "Sizes on this system (bytes):\n";
    std::cout << "bool: " << sizeof(bool) << '\n';
    std::cout << "char: " << sizeof(char) << '\n';
    std::cout << "int: " << sizeof(int) << " (max: " << INT_MAX << ")\n";
    std::cout << "unsigned int: " << sizeof(unsigned int) << " (max: " << UINT_MAX << ")\n";
    std::cout << "long long: " << sizeof(long long) << " (max: " << LLONG_MAX << ")\n";
    std::cout << "float: " << sizeof(float) << '\n';
    std::cout << "double: " << sizeof(double) << '\n';

    const long long journeys = 3000000LL;
    const long long farePaise = 3600LL;
    const double fareDouble = 36.10;
    const long long farePaiseExact = 3610LL;

    long long networkTotalPaise = journeys * farePaise;
    std::cout << "\n3,000,000 journeys at Rs 36.00 (paise): " << networkTotalPaise << '\n';
    std::cout << "Exceeds INT_MAX? " << std::boolalpha << (networkTotalPaise > INT_MAX) << '\n';

    double doubleSum = 0.0;
    long long intSum = 0;
    for (int i = 0; i < 1000000; ++i) {
        doubleSum += fareDouble;
        intSum += farePaiseExact;
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nPrecision check (1,000,000 x Rs 36.10):\n";
    std::cout << "double total    : " << doubleSum << '\n';
    std::cout << "long long total : " << (intSum / 100) << '.' << std::setw(2) << std::setfill('0') << (intSum % 100) << '\n';
    return 0;
}
