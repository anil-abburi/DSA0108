#include <iomanip>
#include <iostream>
#include <string>

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE = 5000;

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

long long computeFare(int zone, int hour) {
    if (zone < 0 || zone > 2 || hour < 0 || hour > 23) return -1;
    long long f = BASE_PAISE[zone];
    return isPeakHour(hour) ? f + f * 20 / 100 : f;
}

class SmartCard {
    long long balance;
public:
    explicit SmartCard(long long init) : balance(init >= 0 ? init : 0) {}
    bool recharge(long long amount) {
        if (amount <= 0) return false;
        balance += amount;
        return true;
    }
    bool travel(long long fare) {
        if (fare < 0 || balance - fare < MIN_BALANCE) return false;
        balance -= fare;
        return true;
    }
    long long getBalance() const { return balance; }
};

struct TestCase {
    std::string label;
    int zone;
    int hour;
    long long expectedFare;
};

int main() {
    TestCase tests[] = {
        {"Inner Off-Peak", 0, 11, 1000},
        {"Inner Peak 8:00", 0, 8, 1200},
        {"Middle Boundary 10:00", 1, 10, 2000},
        {"Outer Peak 17:00", 2, 17, 3600},
        {"Outer Boundary 20:00", 2, 20, 3000},
        {"Invalid Zone", 4, 9, -1}
    };

    for (const auto& tc : tests) {
        long long actual = computeFare(tc.zone, tc.hour);
        std::cout << std::left << std::setw(24) << tc.label
                  << " Expected: " << std::setw(5) << tc.expectedFare
                  << " Actual: " << std::setw(5) << actual
                  << (actual == tc.expectedFare ? " [PASS]\n" : " [FAIL]\n");
    }

    SmartCard exactCard(6000);
    std::cout << "Exact Rs 50 remaining allowed: " << std::boolalpha << exactCard.travel(1000)
              << " Balance: " << exactCard.getBalance() << '\n';
    std::cout << "Negative recharge rejected: " << (!exactCard.recharge(-500)) << '\n';

    long long totalFive = 0;
    int sampleZones[5] = {0, 1, 2, 0, 2};
    int sampleHours[5] = {9, 12, 18, 20, 14};
    for (int i = 0; i < 5; ++i) {
        totalFive += computeFare(sampleZones[i], sampleHours[i]);
    }
    std::cout << "5-Journey Total (paise): " << totalFive << " (Rs " << totalFive / 100 << '.'
              << std::setw(2) << std::setfill('0') << totalFive % 100 << ")\n";
    return 0;
}
