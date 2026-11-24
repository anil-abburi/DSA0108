#include <iostream>

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

int main() {
    int testHours[] = {7, 8, 9, 10, 17, 19, 20};
    for (int h : testHours) {
        std::cout << "Hour " << h << ": " << (isPeakHour(h) ? "Peak" : "Off-Peak") << '\n';
    }

    long long base = 3000;
    bool peak = isPeakHour(9);
    int concession = 10;
    long long surcharge = peak ? (base * 20 / 100) : 0;
    long long fare = base + surcharge;
    fare -= fare * concession / 100;
    std::cout << "Base: " << base << " Surcharge: " << surcharge << " Final: " << fare << '\n';

    int a = 5;
    int pre = ++a;
    int b = 5;
    int post = b++;
    std::cout << "Prefix: " << pre << " (a=" << a << "), Postfix: " << post << " (b=" << b << ")\n";
    std::cout << "-10 / 3 = " << (-10 / 3) << ", -10 % 3 = " << (-10 % 3) << '\n';
    return 0;
}
