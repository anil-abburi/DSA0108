#include <exception>
#include <iostream>
#include <string>

class BillingError : public std::exception {
protected:
    std::string msg;

public:
    explicit BillingError(const std::string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class NegativeChargeError : public BillingError {
public:
    explicit NegativeChargeError(const std::string& m) : BillingError("NegativeCharge: " + m) {}
};

class ClaimError : public BillingError {
public:
    explicit ClaimError(const std::string& m) : BillingError("ClaimError: " + m) {}
};

class UnknownPackageError : public BillingError {
public:
    explicit UnknownPackageError(const std::string& m) : BillingError("UnknownPackage: " + m) {}
};

double validateCharge(double amount) {
    if (amount < 0.0) throw NegativeChargeError("charge cannot be negative");
    return amount;
}

double safeZeroFallback(double amount) noexcept {
    return amount < 0.0 ? 0.0 : amount;
}

int main() {
    try {
        validateCharge(-250.0);
    } catch (const BillingError& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
    std::cout << "noexcept fallback: " << safeZeroFallback(-250.0) << '\n';
    return 0;
}
