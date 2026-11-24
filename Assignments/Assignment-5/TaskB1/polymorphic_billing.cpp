#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Bill {
protected:
    std::string patient;

public:
    explicit Bill(const std::string& p) : patient(p) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    std::string getPatient() const { return patient; }
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(const std::string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days;
    double roomRate, procedures, medicines;
public:
    InPatientBill(const std::string& p, int d, double r, double pr, double m)
        : Bill(p), days(d), roomRate(r), procedures(pr), medicines(m) {}
    double total() const override { return days * roomRate + procedures + medicines; }
    std::string type() const override { return "IP"; }
};

class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(const std::string& p, double pkg) : Bill(p), packagePrice(pkg) {}
    double total() const override { return packagePrice; }
    std::string type() const override { return "DC"; }
};

class EmergencyBill : public Bill {
    double base, hours, rate;
public:
    EmergencyBill(const std::string& p, double b, double h, double r)
        : Bill(p), base(b), hours(h), rate(r) {}
    double total() const override { return base + hours * rate; }
    std::string type() const override { return "ER"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double amountCovered(const Bill& b) const = 0;
};

class SelfPay : public Payer {
public:
    std::string name() const override { return "SelfPay"; }
    double amountCovered(const Bill&) const override { return 0.0; }
};

class Insurance : public Payer {
    double limit, coPay;
public:
    Insurance(double l, double cp) : limit(l), coPay(cp) {}
    std::string name() const override { return "Insurance"; }
    double amountCovered(const Bill& b) const override {
        return std::min(b.total() * (100.0 - coPay) / 100.0, limit);
    }
};

class GovernmentScheme : public Payer {
    double fixedCap;
public:
    explicit GovernmentScheme(double cap) : fixedCap(cap) {}
    std::string name() const override { return "GovtScheme"; }
    double amountCovered(const Bill& b) const override {
        return std::min(b.total(), fixedCap);
    }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatientBill>("Meena", 3, 2500, 40000, 2500));
    bills.push_back(std::make_unique<DayCareBill>("Kiran", 15000));
    bills.push_back(std::make_unique<EmergencyBill>("Deepa", 2000, 5, 1000));

    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(40000, 10));
    payers.push_back(std::make_unique<GovernmentScheme>(20000));

    std::cout << std::fixed << std::setprecision(2);
    for (const auto& b : bills) {
        std::cout << b->type() << " " << b->getPatient() << " Total: " << b->total() << '\n';
        for (const auto& p : payers) {
            double cov = p->amountCovered(*b);
            std::cout << "  " << std::left << std::setw(12) << p->name()
                      << " Covered: " << cov << " | Payable: " << (b->total() - cov) << '\n';
        }
    }
    return 0;
}
