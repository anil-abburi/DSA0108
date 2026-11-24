#include <iomanip>
#include <iostream>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

class SmartCard {
    long long balancePaise;
    static constexpr long long MIN_BALANCE = 5000;

public:
    explicit SmartCard(long long initialPaise)
        : balancePaise(initialPaise >= 0 ? initialPaise : 0) {}

    bool canTravel(long long farePaise) const {
        return farePaise >= 0 && (balancePaise - farePaise) >= MIN_BALANCE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const { return balancePaise; }
};

long long getFare(Zone z, bool peak) {
    constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
    long long f = BASE_PAISE[static_cast<int>(z)];
    return peak ? f + f * 20 / 100 : f;
}

int main() {
    SmartCard card(10000);
    long long f1 = getFare(Zone::Outer, true);
    if (card.deduct(f1)) {
        std::cout << "OOP Balance after trip 1: Rs " << card.getBalance() / 100 << '.'
                  << std::setw(2) << std::setfill('0') << card.getBalance() % 100 << '\n';
    }
    long long f2 = getFare(Zone::Middle, false);
    if (!card.deduct(f2)) {
        std::cout << "OOP Trip 2 Denied (balance protected at Rs "
                  << card.getBalance() / 100 << '.' << std::setw(2) << std::setfill('0')
                  << card.getBalance() % 100 << ")\n";
    }
    return 0;
}
