#include <iomanip>
#include <iostream>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(double weightKg, bool express = false, bool insured = false) {
    double cost = weightKg * 50.0;
    if (express) cost += 100.0;
    if (insured) cost += 75.0;
    return cost;
}

double charge(int weightGrams, bool express = false, bool insured = false) {
    return charge(static_cast<double>(weightGrams) / 1000.0, express, insured);
}

double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "charge(2)                : " << charge(2) << '\n';
    std::cout << "charge(2.0f)             : " << charge(2.0f) << '\n';
    std::cout << "charge(2.5)              : " << charge(2.5) << '\n';
    std::cout << "charge(2.5, true)        : " << charge(2.5, true) << '\n';
    std::cout << "charge(1500, true, true) : " << charge(1500, true, true) << '\n';

    Parcel p{3.0, true, true};
    std::cout << "charge(Parcel)           : " << charge(p) << '\n';
    return 0;
}
