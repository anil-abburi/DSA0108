#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int totalSeconds;

public:
    Time(int h = 0, int m = 0, int s = 0) : totalSeconds(h * 3600 + m * 60 + s) {}

    Time& operator++() {
        ++totalSeconds;
        return *this;
    }

    Time operator++(int) {
        Time old = *this;
        ++totalSeconds;
        return old;
    }

    bool operator==(const Time& other) const { return totalSeconds == other.totalSeconds; }
    bool operator<(const Time& other) const { return totalSeconds < other.totalSeconds; }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        int h = t.totalSeconds / 3600;
        int m = (t.totalSeconds % 3600) / 60;
        int s = t.totalSeconds % 60;
        os << h << ':' << std::setw(2) << std::setfill('0') << m << ':'
           << std::setw(2) << std::setfill('0') << s << std::setfill(' ');
        return os;
    }
};

class Playlist {
    std::vector<std::string> tracks;

public:
    void add(const std::string& track) { tracks.push_back(track); }
    int size() const { return static_cast<int>(tracks.size()); }

    std::string& operator[](int idx) {
        if (idx < 0 || idx >= size()) {
            throw std::out_of_range("Playlist index out of range");
        }
        return tracks[static_cast<size_t>(idx)];
    }

    const std::string& operator[](int idx) const {
        if (idx < 0 || idx >= size()) {
            throw std::out_of_range("Playlist index out of range");
        }
        return tracks[static_cast<size_t>(idx)];
    }
};

int main() {
    Time t(0, 59, 59);
    Time a = t++;
    Time b = ++t;
    std::cout << "a (old): " << a << " | b (new): " << b << " | t: " << t << '\n';
    std::cout << "a < b: " << std::boolalpha << (a < b) << " | b == t: " << (b == t) << '\n';

    Playlist pl;
    pl.add("Track 1 - Intro");
    pl.add("Track 2 - Melody");
    std::cout << "Playing: " << pl[0] << " and " << pl[1] << '\n';

    for (int bad : {-1, pl.size()}) {
        try {
            std::cout << pl[bad] << '\n';
        } catch (const std::out_of_range& e) {
            std::cout << "Caught for index " << bad << ": " << e.what() << '\n';
        }
    }

    const long long N = 10000000LL;
    Time tPre(0, 0, 0), tPost(0, 0, 0);
    auto s1 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) ++tPre;
    auto e1 = std::chrono::steady_clock::now();

    auto s2 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) tPost++;
    auto e2 = std::chrono::steady_clock::now();

    std::cout << "Prefix 10M (ms) : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(e1 - s1).count() << '\n';
    std::cout << "Postfix 10M (ms): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(e2 - s2).count() << '\n';
    return 0;
}
