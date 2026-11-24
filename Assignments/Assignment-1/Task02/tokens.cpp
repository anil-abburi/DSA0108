#include <iomanip>
#include <iostream>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

constexpr long long ZONE_BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int MORNING_PEAK_START = 8;
constexpr int MORNING_PEAK_END = 10;
constexpr int EVENING_PEAK_START = 17;
constexpr int EVENING_PEAK_END = 20;

long long calculateFare(Zone z, bool peak) {
    long long fare = ZONE_BASE_PAISE[static_cast<int>(z)];
    if (peak) {
        fare += fare * PEAK_SURCHARGE_PERCENT / 100;
    }
    return fare;
}

int main() {
    const Zone sampleZones[] = {Zone::Inner, Zone::Middle, Zone::Outer};
    const char* zoneNames[] = {"Inner", "Middle", "Outer"};

    for (int i = 0; i < 3; ++i) {
        long long offPeak = calculateFare(sampleZones[i], false);
        long long peak = calculateFare(sampleZones[i], true);
        std::cout << zoneNames[i] << " | Off-Peak: Rs " << offPeak / 100 << '.'
                  << std::setw(2) << std::setfill('0') << offPeak % 100
                  << " | Peak: Rs " << peak / 100 << '.'
                  << std::setw(2) << std::setfill('0') << peak % 100 << '\n';
    }
    std::cout << "Minimum Remaining Balance: Rs " << MIN_BALANCE_PAISE / 100 << ".00\n";
    std::cout << "Peak Windows: " << MORNING_PEAK_START << ":00-" << MORNING_PEAK_END
              << ":00 and " << EVENING_PEAK_START << ":00-" << EVENING_PEAK_END << ":00\n";
    return 0;
}
