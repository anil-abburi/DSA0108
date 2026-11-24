#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Bill {
protected:
    std::string patientName;
    int billId;

public:
    Bill(const std::string& p, int id) : patientName(p), billId(id) {}
    virtual ~Bill() = default;

    virtual double total() const = 0;
    virtual std::string type() const = 0;

    virtual void print() const {
        std::cout << "[" << type() << "] #" << billId << " " << patientName
                  << " -> Rs " << std::fixed << std::setprecision(2) << total() << '\n';
    }
};

class OutPatientBill : public Bill {
    double consultation;
    double tests;

public:
    OutPatientBill(const std::string& p, int id, double c, double t)
        : Bill(p, id), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
    int days;
    double roomPerDay;
    double procedures;
    double medicines;

public:
    InPatientBill(const std::string& p, int id, int d, double room, double proc, double med)
        : Bill(p, id), days(d), roomPerDay(room), procedures(proc), medicines(med) {}
    double total() const override { return days * roomPerDay + procedures + medicines; }
    std::string type() const override { return "InPatient"; }
};

class DayCareBill : public Bill {
    double packagePrice;

public:
    DayCareBill(const std::string& p, int id, double pkg) : Bill(p, id), packagePrice(pkg) {}
    double total() const override { return packagePrice; }
    std::string type() const override { return "DayCare"; }
};

class EmergencyBill : public Bill {
    double baseCharge;
    double hours;
    double hourlyRate;

public:
    EmergencyBill(const std::string& p, int id, double base, double h, double rate)
        : Bill(p, id), baseCharge(base), hours(h), hourlyRate(rate) {}
    double total() const override { return baseCharge + hours * hourlyRate; }
    std::string type() const override { return "Emergency"; }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("Ravi", 1, 500, 1200));
    bills.push_back(std::make_unique<InPatientBill>("Meena", 2, 3, 2500, 40000, 3500));
    bills.push_back(std::make_unique<DayCareBill>("Suresh", 3, 18000));
    bills.push_back(std::make_unique<EmergencyBill>("Anita", 4, 2000, 4, 1500));

    double dayTotal = 0.0;
    for (const auto& b : bills) {
        b->print();
        dayTotal += b->total();
    }
    std::cout << "Day Total: Rs " << std::fixed << std::setprecision(2) << dayTotal << '\n';
    return 0;
}
