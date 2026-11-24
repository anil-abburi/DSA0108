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

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long absVal = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) os << '-';
        os << "Rs " << (absVal / 100) << '.' << std::setw(2) << std::setfill('0')
           << (absVal % 100) << std::setfill(' ');
        return os;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    Money d = Money(0, 75) + Money(0, 50);
    std::cout << d << '\n';
    return 0;
}
