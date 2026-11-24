#include <chrono>
#include <cmath>
#include <iostream>

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend inline int minutesBetweenInline(const Time& a, const Time& b);
    friend int minutesBetweenNormal(const Time& a, const Time& b);
    friend inline bool earlier(const Time& a, const Time& b);
};

inline int minutesBetweenInline(const Time& a, const Time& b) {
    int ma = a.h * 60 + a.m;
    int mb = b.h * 60 + b.m;
    return ma >= mb ? ma - mb : mb - ma;
}

int minutesBetweenNormal(const Time& a, const Time& b) {
    int ma = a.h * 60 + a.m;
    int mb = b.h * 60 + b.m;
    return ma >= mb ? ma - mb : mb - ma;
}

inline bool earlier(const Time& a, const Time& b) {
    return (a.h * 60 + a.m) < (b.h * 60 + b.m);
}

int main() {
    Time t1(9, 45), t2(13, 10), t3(11, 30);
    std::cout << "9:45 to 13:10 -> " << minutesBetweenInline(t1, t2) << " min, earlier: "
              << std::boolalpha << earlier(t1, t2) << '\n';
    std::cout << "11:30 to 11:30 -> " << minutesBetweenInline(t3, t3) << " min, earlier: "
              << earlier(t3, t3) << '\n';

    const long long N = 10000000LL;
    volatile long long sink = 0;

    auto start1 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) {
        sink += minutesBetweenInline(t1, t2);
    }
    auto end1 = std::chrono::steady_clock::now();

    auto start2 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) {
        sink += minutesBetweenNormal(t1, t2);
    }
    auto end2 = std::chrono::steady_clock::now();

    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    std::cout << "Inline time (ms) : " << ms1 << '\n';
    std::cout << "Normal time (ms) : " << ms2 << '\n';
    return 0;
}
