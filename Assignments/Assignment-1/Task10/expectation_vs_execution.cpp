#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

void runExperiment(long long n) {
    const double fareDouble = 12.10;
    const long long farePaise = 1210LL;

    double dTotal = 0.0;
    long long llTotal = 0;
    for (long long i = 0; i < n; ++i) {
        dTotal += fareDouble;
        llTotal += farePaise;
    }

    double exactRupees = static_cast<double>(llTotal) / 100.0;
    double diff = std::fabs(dTotal - exactRupees);

    std::cout << "Journeys: " << n << '\n';
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  double total    : " << dTotal << '\n';
    std::cout << "  long long exact : " << exactRupees << '\n';
    std::cout << "  difference (Rs) : " << diff << '\n';
    std::cout << "  int overflow?   : " << std::boolalpha << (llTotal > INT_MAX) << '\n';
}

int main() {
    runExperiment(20000LL);
    runExperiment(500000LL);
    runExperiment(3000000LL);
    return 0;
}
