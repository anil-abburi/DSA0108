#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
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
    double c, t;
public:
    OutPatientBill(const std::string& p, double cons, double tests) : Bill(p), c(cons), t(tests) {
        if (c < 0 || t < 0) throw std::invalid_argument("Negative OP charge");
    }
    double total() const override { return c + t; }
    std::string type() const override { return "OP"; }
};

class DiagnosticsBill : public Bill {
    double scanFee;
    double labFee;

public:
    DiagnosticsBill(const std::string& p, double scan, double lab)
        : Bill(p), scanFee(scan), labFee(lab) {
        if (scan < 0 || lab < 0) throw std::invalid_argument("Negative diagnostic charge");
    }
    double total() const override { return scanFee + labFee; }
    std::string type() const override { return "Diagnostics"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double cover(const Bill& b) const = 0;
};

class InsurancePayer : public Payer {
    double cap;
public:
    explicit InsurancePayer(double limit) : cap(limit) {}
    std::string name() const override { return "Insurance"; }
    double cover(const Bill& b) const override { return std::min(b.total() * 0.85, cap); }
};

class CorporatePayer : public Payer {
    double cap;
public:
    explicit CorporatePayer(double limit) : cap(limit) {}
    std::string name() const override { return "CorporateTieUp"; }
    double cover(const Bill& b) const override { return std::min(b.total() * 0.90, cap); }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    try {
        bills.push_back(std::make_unique<OutPatientBill>("Ravi", 500, 1200));
        bills.push_back(std::make_unique<DiagnosticsBill>("Priya", 4500, 1500));
        bills.push_back(std::make_unique<DiagnosticsBill>("InvalidCase", -100, 500));
    } catch (const std::invalid_argument& e) {
        std::cout << "Rejected invalid bill safely: " << e.what() << '\n';
    }

    CorporatePayer corp(50000.0);
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& b : bills) {
        double cov = corp.cover(*b);
        std::cout << b->type() << " (" << b->getPatient() << ") Total: Rs " << b->total()
                  << " | " << corp.name() << " covers: Rs " << cov << '\n';
    }
    return 0;
}
