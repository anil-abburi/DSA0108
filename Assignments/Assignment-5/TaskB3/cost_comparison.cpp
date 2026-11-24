#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

struct VBill {
    virtual ~VBill() = default;
    virtual double total() const = 0;
};

struct VOP : VBill {
    double a, b;
    VOP(double x, double y) : a(x), b(y) {}
    double total() const override { return a + b; }
};

struct VIP : VBill {
    double a, b;
    VIP(double x, double y) : a(x), b(y) {}
    double total() const override { return a * 3.0 + b; }
};

struct SBill {
    int type;
    double a, b;
    double total() const {
        switch (type) {
            case 0: return a + b;
            case 1: return a * 3.0 + b;
            default: return 0.0;
        }
    }
};

void benchmarkBills(size_t n) {
    std::vector<std::unique_ptr<VBill>> vlist;
    std::vector<SBill> slist;
    vlist.reserve(n);
    slist.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            vlist.push_back(std::make_unique<VOP>(500.0, 1200.0));
            slist.push_back({0, 500.0, 1200.0});
        } else {
            vlist.push_back(std::make_unique<VIP>(2500.0, 40000.0));
            slist.push_back({1, 2500.0, 40000.0});
        }
    }

    auto t1 = std::chrono::steady_clock::now();
    double vsum = 0.0;
    for (const auto& b : vlist) vsum += b->total();
    auto t2 = std::chrono::steady_clock::now();

    auto t3 = std::chrono::steady_clock::now();
    double ssum = 0.0;
    for (const auto& b : slist) ssum += b.total();
    auto t4 = std::chrono::steady_clock::now();

    auto vUs = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto sUs = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "N=" << n << " | Match: " << std::boolalpha << (vsum == ssum)
              << " | Virtual: " << vUs << " us | Switch: " << sUs << " us\n";
}

bool validateReturnCode(double amount) {
    return amount >= 0.0;
}

double validateException(double amount) {
    if (amount < 0.0) throw std::invalid_argument("neg");
    return amount;
}

void benchmarkErrorRate(int invalidPercent) {
    const int N = 200000;
    std::vector<double> vals(N, 100.0);
    for (int i = 0; i < N; ++i) {
        if ((i % 100) < invalidPercent) vals[i] = -1.0;
    }

    auto t1 = std::chrono::steady_clock::now();
    int badRc = 0;
    for (double v : vals) {
        if (!validateReturnCode(v)) ++badRc;
    }
    auto t2 = std::chrono::steady_clock::now();

    auto t3 = std::chrono::steady_clock::now();
    int badEx = 0;
    for (double v : vals) {
        try {
            validateException(v);
        } catch (const std::invalid_argument&) {
            ++badEx;
        }
    }
    auto t4 = std::chrono::steady_clock::now();

    auto rcUs = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto exUs = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
    std::cout << "Invalid " << invalidPercent << "% (N=" << N << ") | RC: " << rcUs
              << " us (" << badRc << ") | Exception: " << exUs << " us (" << badEx << ")\n";
}

int main() {
    benchmarkBills(10);
    benchmarkBills(1000);
    benchmarkBills(100000);
    benchmarkErrorRate(0);
    benchmarkErrorRate(1);
    benchmarkErrorRate(50);
    return 0;
}
