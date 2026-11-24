#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ServiceDate {
    std::string date;

public:
    explicit ServiceDate(const std::string& d) : date(d) {}
    std::string str() const { return date; }
};

class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool rented;

public:
    Vehicle(const std::string& reg, double rate) : regNo(reg), dailyRate(rate), rented(false) {}
    virtual ~Vehicle() = default;

    virtual std::string type() const = 0;
    virtual double rentalCharge(int days, double usageUnits, int lateDays) const = 0;

    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }

    double returnVehicle(int days, double usageUnits, int lateDays) {
        rented = false;
        return rentalCharge(days, usageUnits, lateDays);
    }

    void display() const {
        std::cout << type() << " [" << regNo << "] Rate: Rs " << dailyRate
                  << "/day | Status: " << (rented ? "Rented" : "Available") << '\n';
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    std::string type() const override { return "Bicycle"; }
    double rentalCharge(int days, double, int lateDays) const override {
        return days * dailyRate + lateDays * (dailyRate * 1.2);
    }
};

class MotorVehicle : public Vehicle {
protected:
    double energyLevel;
    ServiceDate nextService;

public:
    MotorVehicle(const std::string& reg, double rate, double level, const std::string& svc)
        : Vehicle(reg, rate), energyLevel(level), nextService(svc) {}
};

class TwoWheeler : public MotorVehicle {
    double fuelRatePerLitre;

public:
    TwoWheeler(const std::string& reg, double rate, double fuel, const std::string& svc, double perLitre)
        : MotorVehicle(reg, rate, fuel, svc), fuelRatePerLitre(perLitre) {}
    std::string type() const override { return "TwoWheeler"; }
    double rentalCharge(int days, double litresUsed, int lateDays) const override {
        return days * dailyRate + litresUsed * fuelRatePerLitre + lateDays * (dailyRate * 1.5);
    }
};

class Car : public MotorVehicle {
protected:
    int seats;
    double fuelRatePerLitre;

public:
    Car(const std::string& reg, double rate, double fuel, const std::string& svc, int s, double perLitre)
        : MotorVehicle(reg, rate, fuel, svc), seats(s), fuelRatePerLitre(perLitre) {}
    std::string type() const override { return "Car"; }
    double rentalCharge(int days, double litresUsed, int lateDays) const override {
        return days * dailyRate + litresUsed * fuelRatePerLitre + lateDays * (dailyRate * 1.5);
    }
};

class ElectricCar : public Car {
    double batteryKWh;
    double ratePerKWh;

public:
    ElectricCar(const std::string& reg, double rate, double chargePct, const std::string& svc,
                int s, double capKWh, double kWhRate)
        : Car(reg, rate, chargePct, svc, s, 0.0), batteryKWh(capKWh), ratePerKWh(kWhRate) {}
    std::string type() const override { return "ElectricCar"; }
    double rentalCharge(int days, double kWhUsed, int lateDays) const override {
        return days * dailyRate + kWhUsed * ratePerKWh + lateDays * (dailyRate * 1.5);
    }
};

class ElectricBus : public MotorVehicle {
    int seats;
    double ratePerKWh;

public:
    ElectricBus(const std::string& reg, double rate, double chargePct, const std::string& svc,
                int s, double kWhRate)
        : MotorVehicle(reg, rate, chargePct, svc), seats(s), ratePerKWh(kWhRate) {}
    std::string type() const override { return "ElectricBus"; }
    double rentalCharge(int days, double kWhUsed, int lateDays) const override {
        return days * dailyRate + kWhUsed * ratePerKWh + lateDays * (dailyRate * 2.0);
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("CYC-01", 150.0));
    fleet.push_back(std::make_unique<TwoWheeler>("TN01-TW-10", 500.0, 80.0, "2027-01-15", 102.0));
    fleet.push_back(std::make_unique<Car>("TN01-CR-20", 1800.0, 75.0, "2027-02-20", 5, 102.0));
    fleet.push_back(std::make_unique<ElectricCar>("TN01-EV-30", 2200.0, 95.0, "2027-03-10", 5, 45.0, 12.0));
    fleet.push_back(std::make_unique<ElectricBus>("TN01-EB-40", 6500.0, 90.0, "2027-04-05", 32, 10.0));

    std::cout << std::fixed << std::setprecision(2);
    for (auto& v : fleet) {
        v->rent();
        v->display();
        double bill = v->returnVehicle(3, 15.0, 1);
        std::cout << "  Returned (3 days + 1 late day) -> Charge: Rs " << bill << '\n';
    }
    return 0;
}
