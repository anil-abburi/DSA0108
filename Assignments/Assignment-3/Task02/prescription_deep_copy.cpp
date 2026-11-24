#include <chrono>
#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;
    static int copyCount;

public:
    explicit Prescription(int count) : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {}

    Prescription(const Prescription& other)
        : n(other.n), medicines(other.n > 0 ? new std::string[other.n] : nullptr) {
        ++copyCount;
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
    }

    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this;
        std::string* fresh = other.n > 0 ? new std::string[other.n] : nullptr;
        for (int i = 0; i < other.n; ++i) {
            fresh[i] = other.medicines[i];
        }
        delete[] medicines;
        n = other.n;
        medicines = fresh;
        return *this;
    }

    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
    int size() const { return n; }

    static void resetCopyCount() { copyCount = 0; }
    static int getCopyCount() { return copyCount; }
};

int Prescription::copyCount = 0;

void passByValue(Prescription p) {
    (void)p.size();
}

void passByConstRef(const Prescription& p) {
    (void)p.size();
}

void benchmarkCopy(int count) {
    Prescription p(count);
    for (int i = 0; i < count; ++i) {
        p.set(i, "Medicine_" + std::to_string(i));
    }
    auto t1 = std::chrono::steady_clock::now();
    Prescription copy = p;
    auto t2 = std::chrono::steady_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Copy size " << count << " took " << us << " us\n";
}

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription::resetCopyCount();
    passByValue(p);
    passByConstRef(p);
    std::cout << "Copies made (1 by value, 1 by const ref): " << Prescription::getCopyCount() << '\n';

    Prescription q = p;
    q.set(1, "Cetirizine");
    Prescription& selfRef = p;
    p = selfRef;

    std::cout << "Original: " << p.get(0) << ", " << p.get(1) << '\n';
    std::cout << "Copy    : " << q.get(0) << ", " << q.get(1) << '\n';

    benchmarkCopy(10);
    benchmarkCopy(1000);
    benchmarkCopy(100000);
    return 0;
}
