#include <iomanip>
#include <iostream>
#include <string>

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };

class MonthlyPass {
    Zone zoneA;
    Zone zoneB;
    bool active;

public:
    MonthlyPass(Zone a, Zone b, bool isActive = true)
        : zoneA(a), zoneB(b), active(isActive) {}

    bool covers(Zone z) const {
        return active && (z == zoneA || z == zoneB);
    }
};

class RevisedFareEngine {
public:
    static constexpr long long BASE_PAISE[4] = {1000, 2000, 3000, 6000};
    static constexpr int PEAK_PERCENT = 20;
    static constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

    static bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long computeFare(Zone z, int hour, bool isWeekend, const MonthlyPass* pass = nullptr) {
        if (pass != nullptr && pass->covers(z)) {
            return 0;
        }
        long long fare = BASE_PAISE[static_cast<int>(z)];
        if (isWeekend) {
            fare -= fare * WEEKEND_DISCOUNT_PERCENT / 100;
        } else if (isPeak(hour)) {
            fare += fare * PEAK_PERCENT / 100;
        }
        return fare;
    }
};

class SmartCard {
    long long balancePaise;
public:
    explicit SmartCard(long long initPaise) : balancePaise(initPaise >= 0 ? initPaise : 0) {}
    bool deduct(long long farePaise) {
        if (farePaise == 0) return true;
        if (farePaise < 0 || balancePaise - farePaise < RevisedFareEngine::MIN_BALANCE_PAISE) {
            return false;
        }
        balancePaise -= farePaise;
        return true;
    }
    long long balance() const { return balancePaise; }
};

void showTrip(const std::string& label, SmartCard& card, long long fare) {
    bool ok = card.deduct(fare);
    std::cout << std::left << std::setw(28) << label
              << (ok ? "Allowed " : "Denied  ")
              << "Fare Rs " << std::right << std::setw(2) << fare / 100 << '.'
              << std::setw(2) << std::setfill('0') << fare % 100 << std::setfill(' ')
              << "  Balance Rs " << card.balance() / 100 << '.'
              << std::setw(2) << std::setfill('0') << card.balance() % 100 << std::setfill(' ') << '\n';
}

int main() {
    SmartCard card(20000);
    MonthlyPass pass(Zone::Inner, Zone::Middle, true);

    showTrip("Airport Weekday Peak", card, RevisedFareEngine::computeFare(Zone::Airport, 9, false));
    showTrip("Airport Weekend (9 AM)", card, RevisedFareEngine::computeFare(Zone::Airport, 9, true));
    showTrip("Middle with Monthly Pass", card, RevisedFareEngine::computeFare(Zone::Middle, 18, false, &pass));
    showTrip("Outer with Pass (uncovered)", card, RevisedFareEngine::computeFare(Zone::Outer, 12, false, &pass));
    return 0;
}
