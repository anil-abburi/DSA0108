#include <iomanip>
#include <iostream>
#include <string>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

class FareConfig {
public:
    static constexpr long long BASE_PAISE[3] = {1000, 2000, 3000};
    static constexpr int PEAK_PERCENT = 20;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

    static bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long fare(Zone z, int hour, int concessionPercent = 0) {
        long long amount = BASE_PAISE[static_cast<int>(z)];
        if (isPeak(hour)) {
            amount += amount * PEAK_PERCENT / 100;
        }
        if (concessionPercent > 0 && concessionPercent <= 100) {
            amount -= amount * concessionPercent / 100;
        }
        return amount;
    }
};

class SmartCard {
    std::string id;
    long long balancePaise;

public:
    SmartCard(const std::string& cardId, long long initPaise)
        : id(cardId), balancePaise(initPaise >= 0 ? initPaise : 0) {}

    bool deduct(long long farePaise) {
        if (farePaise < 0 || balancePaise - farePaise < FareConfig::MIN_BALANCE_PAISE) {
            return false;
        }
        balancePaise -= farePaise;
        return true;
    }

    long long balance() const { return balancePaise; }
    std::string cardId() const { return id; }
};

int main() {
    SmartCard card("METRO-2026-01", 15000);
    long long f = FareConfig::fare(Zone::Outer, 9, 10);
    bool ok = card.deduct(f);
    std::cout << "Card: " << card.cardId() << " | Approved: " << std::boolalpha << ok
              << " | Fare: Rs " << f / 100 << '.' << std::setw(2) << std::setfill('0') << f % 100
              << " | Balance: Rs " << card.balance() / 100 << '.' << std::setw(2)
              << card.balance() % 100 << '\n';
    return 0;
}
