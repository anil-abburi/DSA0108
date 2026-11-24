#include <iomanip>
#include <iostream>

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE = 5000;

long long getFare(int zone, bool peak) {
    long long f = BASE_PAISE[zone];
    return peak ? f + f * 20 / 100 : f;
}

bool canTravelProc(long long balance, long long fare) {
    return balance - fare >= MIN_BALANCE;
}

void deductProc(long long& balance, long long fare) {
    if (canTravelProc(balance, fare)) {
        balance -= fare;
    }
}

int main() {
    long long balance = 10000;
    long long f1 = getFare(2, true);
    deductProc(balance, f1);
    std::cout << "Procedural Balance after trip 1: Rs " << balance / 100 << '.'
              << std::setw(2) << std::setfill('0') << balance % 100 << '\n';

    long long f2 = getFare(1, false);
    if (!canTravelProc(balance, f2)) {
        std::cout << "Procedural Trip 2 Denied\n";
    }
    return 0;
}
