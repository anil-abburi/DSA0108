#include <iomanip>
#include <iostream>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

struct JourneyInput {
    int zoneCode;
    int hour;
};

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE_PAISE = 5000;

bool isPeak(int h) {
    return (h >= 8 && h < 10) || (h >= 17 && h < 20);
}

long long computeFare(int zoneCode, int hour) {
    long long base = 0;
    switch (zoneCode) {
        case 0: base = BASE_PAISE[0]; break;
        case 1: base = BASE_PAISE[1]; break;
        case 2: base = BASE_PAISE[2]; break;
        default: return -1;
    }
    return isPeak(hour) ? base + base * 20 / 100 : base;
}

int main() {
    JourneyInput log[] = {{0, 9}, {5, 11}, {2, 18}, {1, 20}, {2, 12}};
    long long balance = 12000;
    long long totalCollected = 0;

    for (const auto& item : log) {
        if (item.hour < 0 || item.hour > 23) {
            std::cout << "Skipping invalid hour\n";
            continue;
        }
        long long f = computeFare(item.zoneCode, item.hour);
        if (f < 0) {
            std::cout << "Skipping invalid zone: " << item.zoneCode << '\n';
            continue;
        }
        if (balance - f < MIN_BALANCE_PAISE) {
            std::cout << "Low balance. Stopping further trips.\n";
            break;
        }
        balance -= f;
        totalCollected += f;
        std::cout << "Zone " << item.zoneCode << " Hour " << item.hour
                  << " Fare Rs " << f / 100 << '.' << std::setw(2) << std::setfill('0') << f % 100
                  << " Balance Rs " << balance / 100 << '.' << std::setw(2) << balance % 100
                  << std::setfill(' ') << '\n';
    }
    std::cout << "Total Collected: Rs " << totalCollected / 100 << '.'
              << std::setw(2) << std::setfill('0') << totalCollected % 100 << '\n';
    return 0;
}
