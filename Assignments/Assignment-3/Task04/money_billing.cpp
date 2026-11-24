#include <cmath>
#include <iomanip>
#include <iostream>

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money res;
        res.paise = paise + other.paise;
        return res;
    }

    Money operator-(const Money& other) const {
        Money res;
        res.paise = paise - other.paise;
        return res;
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const { return paise == other.paise; }
    bool operator<(const Money& other) const { return paise < other.paise; }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long absVal = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) os << '-';
        os << "Rs " << (absVal / 100) << '.' << std::setw(2) << std::setfill('0')
           << (absVal % 100) << std::setfill(' ');
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Money& m) {
        long long r = 0;
        int p = 0;
        if (is >> r >> p) {
            m.paise = r * 100 + p;
        }
        return is;
    }
};

int main() {
    Money carry = Money(0, 75) + Money(0, 50);
    std::cout << "Carry test (0.75 + 0.50): " << carry << '\n';

    Money neg = Money(50, 0) - Money(75, 25);
    std::cout << "Negative diff           : " << neg << '\n';

    Money bill;
    bill += Money(120, 75);
    bill += Money(79, 25);
    bill += Money(45, 50);
    std::cout << "Total bill              : " << bill << '\n';
    std::cout << "bill < Rs 300.00?       : " << std::boolalpha << (bill < Money(300, 0)) << '\n';

    Money exactSum;
    double doubleSum = 0.0;
    for (int i = 0; i < 1000000; ++i) {
        exactSum += Money(0, 10);
        doubleSum += 0.10;
    }
    std::cout << "1,000,000 x 0.10 Money  : " << exactSum << '\n';
    std::cout << "1,000,000 x 0.10 double : Rs " << std::fixed << std::setprecision(6) << doubleSum << '\n';
    return 0;
}
