#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name;
    int id;
    static constexpr double DA_RATE = 0.42;

public:
    Staff(const std::string& n, int staffId) : name(n), id(staffId) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    std::string getName() const { return name; }
    int getId() const { return id; }
};

class Professor : public Staff {
    double basic;
    double researchAllowance;

public:
    Professor(const std::string& n, int staffId, double b, double res)
        : Staff(n, staffId), basic(b), researchAllowance(res) {}
    double pay() const override { return basic + basic * DA_RATE + researchAllowance; }
};

class LabAssistant : public Staff {
    double basic;

public:
    LabAssistant(const std::string& n, int staffId, double b)
        : Staff(n, staffId), basic(b) {}
    double pay() const override { return basic + basic * DA_RATE; }
};

class GuestFaculty : public Staff {
    double hours;
    double rate;

public:
    GuestFaculty(const std::string& n, int staffId, double h, double r)
        : Staff(n, staffId), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    std::vector<Staff*> payroll;
    payroll.push_back(new Professor("Dr. Meera", 101, 80000.0, 15000.0));
    payroll.push_back(new LabAssistant("Ramesh", 205, 35000.0));
    payroll.push_back(new GuestFaculty("Karthik", 309, 24.0, 1500.0));

    double total = 0.0;
    std::cout << std::fixed << std::setprecision(2);
    for (const Staff* s : payroll) {
        double p = s->pay();
        total += p;
        std::cout << s->getId() << " | " << s->getName() << " | Pay: Rs " << p << '\n';
    }
    std::cout << "Total Payroll: Rs " << total << '\n';

    for (Staff* s : payroll) delete s;
    return 0;
}
