#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Bill {
public:
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
};

class SampleBill : public Bill {
    std::string t;
    double amt;
public:
    SampleBill(const std::string& typeName, double a) : t(typeName), amt(a) {}
    double total() const override { return amt; }
    std::string type() const override { return t; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class SelfPay : public Payer {
public:
    std::string name() const override { return "SelfPay"; }
    double amountCovered(const Bill&) const override { return 0.0; }
};

class Insurance : public Payer {
    double coverLimit;
    double coPayPercent;

public:
    Insurance(double limit, double coPay) : coverLimit(limit), coPayPercent(coPay) {}
    std::string name() const override { return "Insurance"; }
    double amountCovered(const Bill& bill) const override {
        double eligible = bill.total() * (100.0 - coPayPercent) / 100.0;
        return std::min(eligible, coverLimit);
    }
};

class GovernmentScheme : public Payer {
    double fixedPackageRate;

public:
    explicit GovernmentScheme(double rate) : fixedPackageRate(rate) {}
    std::string name() const override { return "GovernmentScheme"; }
    double amountCovered(const Bill& bill) const override {
        return std::min(bill.total(), fixedPackageRate);
    }
};

class CorporateTieUp : public Payer {
    double maxReimbursement;

public:
    explicit CorporateTieUp(double cap) : maxReimbursement(cap) {}
    std::string name() const override { return "CorporateTieUp"; }
    double amountCovered(const Bill& bill) const override {
        return std::min(bill.total() * 0.90, maxReimbursement);
    }
};

int main() {
    SampleBill b("InPatient", 60000.0);
    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(50000.0, 10.0));
    payers.push_back(std::make_unique<GovernmentScheme>(35000.0));
    payers.push_back(std::make_unique<CorporateTieUp>(55000.0));

    std::cout << std::fixed << std::setprecision(2);
    for (const auto& p : payers) {
        double covered = p->amountCovered(b);
        std::cout << p->name() << " covers Rs " << covered
                  << " | Patient pays Rs " << (b.total() - covered) << '\n';
    }
    return 0;
}
