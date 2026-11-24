#include <iostream>

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    std::cout << "Inside applyByValue: " << fee << '\n';
}

void applyByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= *fee * percent / 100;
    }
}

long long applyReturnNew(long long fee, int percent) {
    return fee - fee * percent / 100;
}

int main() {
    long long fee = 45000;
    applyByValue(fee, 10);
    std::cout << "After applyByValue     : " << fee << '\n';

    applyByReference(fee, 10);
    std::cout << "After applyByReference : " << fee << '\n';

    applyByPointer(&fee, 15);
    std::cout << "After applyByPointer   : " << fee << '\n';

    long long updated = applyReturnNew(45000, 25);
    std::cout << "Returned new fee (25%) : " << updated << '\n';
    return 0;
}
