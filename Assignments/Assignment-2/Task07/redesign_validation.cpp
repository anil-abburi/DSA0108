#include <chrono>
#include <iostream>

template <int K>
class ShiftLedger {
    double entries[K];
    int count = 0;

public:
    void add(double v) {
        if (count < K) {
            entries[count++] = v;
        } else {
            for (int i = 1; i < K; ++i) {
                entries[i - 1] = entries[i];
            }
            entries[K - 1] = v;
        }
    }
    double latest() const { return count > 0 ? entries[count - 1] : 0.0; }
};

template <int K>
class CircularLedger {
    double entries[K];
    int count = 0;
    int head = 0;

public:
    void add(double v) {
        entries[head] = v;
        head = (head + 1) % K;
        if (count < K) ++count;
    }
    double latest() const {
        if (count == 0) return 0.0;
        return entries[(head - 1 + K) % K];
    }
};

int main() {
    constexpr int WINDOW = 50;
    constexpr int OPS = 2000000;

    ShiftLedger<WINDOW> orig;
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < OPS; ++i) orig.add(static_cast<double>(i));
    auto t2 = std::chrono::steady_clock::now();

    CircularLedger<WINDOW> redesigned;
    auto t3 = std::chrono::steady_clock::now();
    for (int i = 0; i < OPS; ++i) redesigned.add(static_cast<double>(i));
    auto t4 = std::chrono::steady_clock::now();

    auto origUs = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto newUs = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();

    std::cout << "Latest value match: " << std::boolalpha << (orig.latest() == redesigned.latest()) << '\n';
    std::cout << "Original shift time (us)     : " << origUs << '\n';
    std::cout << "Redesigned circular time (us): " << newUs << '\n';
    return 0;
}
