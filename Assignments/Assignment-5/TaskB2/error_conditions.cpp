#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class PackageError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct ResourceGuard {
    std::string tag;
    explicit ResourceGuard(const std::string& t) : tag(t) {}
    ~ResourceGuard() { std::cout << "  [RAII cleaned: " << tag << "]\n"; }
};

double processClaim(const std::string& chargeText, double cover, const std::string& pkg) {
    ResourceGuard g("ClaimSession");
    double amount = std::stod(chargeText);
    if (amount < 0) throw std::invalid_argument("negative charge");
    if (pkg != "STD" && pkg != "SURG") throw PackageError("unknown package: " + pkg);
    if (amount > cover) throw ClaimError("claim exceeds policy cover");
    return amount;
}

int main() {
    struct Case { std::string amt; double cover; std::string pkg; };
    Case tests[] = {
        {"-500", 50000, "STD"},
        {"75000", 50000, "STD"},
        {"12000", 50000, "XYZ"},
        {"abc", 50000, "STD"},
        {"15000", 50000, "SURG"}
    };

    for (const auto& t : tests) {
        try {
            double ok = processClaim(t.amt, t.cover, t.pkg);
            std::cout << "Approved: Rs " << ok << '\n';
        } catch (const ClaimError& e) {
            std::cout << "ClaimError: " << e.what() << '\n';
        } catch (const PackageError& e) {
            std::cout << "PackageError: " << e.what() << '\n';
        } catch (const std::invalid_argument& e) {
            std::cout << "InvalidArgument: " << e.what() << '\n';
        } catch (...) {
            std::cout << "Unknown error caught\n";
        }
    }

    try {
        ResourceGuard memGuard("AllocationCheck");
        volatile size_t huge = static_cast<size_t>(-1) / 2;
        char* ptr = new char[huge];
        delete[] ptr;
    } catch (const std::bad_alloc& e) {
        std::cout << "Caught bad_alloc: " << e.what() << '\n';
    }
    return 0;
}
