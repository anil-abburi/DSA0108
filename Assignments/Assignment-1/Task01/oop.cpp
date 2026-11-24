#include <iomanip>
#include <iostream>
#include <string>

enum class Zone { Inner, Middle, Outer };

class FareTable {
public:
    static constexpr long long BASE_PAISE[3] = {1000, 2000, 3000};
    static constexpr int PEAK_SURCHARGE_PERCENT = 20;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

    static long long computeFare(Zone z, bool peak, int concessionPercent) {
        long long base = BASE_PAISE[static_cast<int>(z)];
        if (peak) {
            base += base * PEAK_SURCHARGE_PERCENT / 100;
        }
        if (concessionPercent > 0) {
            base -= base * concessionPercent / 100;
        }
        return base;
    }
};

class Passenger {
    std::string name;
    std::string category;
    int concessionPercent;

public:
    Passenger(const std::string& n, const std::string& cat, int conc)
        : name(n), category(cat), concessionPercent(conc) {}

    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    int getConcession() const { return concessionPercent; }
};

class SmartCard {
    std::string cardId;
    long long balancePaise;

public:
    SmartCard(const std::string& id, long long initialPaise)
        : cardId(id), balancePaise(initialPaise >= 0 ? initialPaise : 0) {}

    bool canTravel(long long farePaise) const {
        return balancePaise - farePaise >= FareTable::MIN_BALANCE_PAISE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const { return balancePaise; }
    std::string getId() const { return cardId; }
};

class Journey {
    Zone zone;
    int hour;

public:
    Journey(Zone z, int h) : zone(z), hour(h) {}

    bool isPeak() const {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    Zone getZone() const { return zone; }
    int getHour() const { return hour; }
};

void printPaise(long long paise) {
    std::cout << "Rs " << paise / 100 << '.' << std::setw(2) << std::setfill('0') << paise % 100 << std::setfill(' ');
}

int main() {
    Passenger p("Ananya", "Student", 10);
    SmartCard card("NM-1001", 10000);
    Journey j(Zone::Outer, 9);

    long long fare = FareTable::computeFare(j.getZone(), j.isPeak(), p.getConcession());
    std::cout << "Passenger: " << p.getName() << " (" << p.getCategory() << ")\n";
    std::cout << "Card ID: " << card.getId() << "\n";
    std::cout << "Computed Fare: ";
    printPaise(fare);
    std::cout << "\n";

    if (card.deduct(fare)) {
        std::cout << "Journey Approved. Remaining Balance: ";
        printPaise(card.getBalance());
        std::cout << "\n";
    } else {
        std::cout << "Journey Denied (Minimum Rs 50.00 must remain).\n";
    }
    return 0;
}
