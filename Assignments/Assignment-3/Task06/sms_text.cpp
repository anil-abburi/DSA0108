#include <chrono>
#include <cstring>
#include <iostream>
#include <string>

class Text {
    size_t len;
    char* data;
    static int copyCount;

public:
    Text(const char* s = "") {
        len = s ? std::strlen(s) : 0;
        data = new char[len + 1];
        if (s) std::memcpy(data, s, len + 1);
        else data[0] = '\0';
    }

    Text(const Text& other) : len(other.len), data(new char[other.len + 1]) {
        ++copyCount;
        std::memcpy(data, other.data, len + 1);
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        char* fresh = new char[other.len + 1];
        std::memcpy(fresh, other.data, other.len + 1);
        delete[] data;
        len = other.len;
        data = fresh;
        return *this;
    }

    ~Text() {
        delete[] data;
    }

    Text operator+(const Text& other) const {
        Text res;
        delete[] res.data;
        res.len = len + other.len;
        res.data = new char[res.len + 1];
        std::memcpy(res.data, data, len);
        std::memcpy(res.data + len, other.data, other.len + 1);
        return res;
    }

    bool operator==(const Text& other) const {
        return len == other.len && std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        return os << t.data;
    }

    static void resetCopies() { copyCount = 0; }
    static int copies() { return copyCount; }
};

int Text::copyCount = 0;

int main() {
    Text a("OTP: "), b("482910"), c(" valid 5m");
    Text::resetCopies();
    Text msg = a + b + c;
    std::cout << "Message: " << msg << " | Copies during a+b+c: " << Text::copies() << '\n';

    Text empty("");
    Text& selfRef = msg;
    msg = selfRef;
    std::cout << "Self-assigned intact: " << std::boolalpha << (msg != empty) << '\n';

    const int N = 2000;
    auto t1 = std::chrono::steady_clock::now();
    Text tAcc("");
    Text unit("a");
    for (int i = 0; i < N; ++i) tAcc = tAcc + unit;
    auto t2 = std::chrono::steady_clock::now();

    auto t3 = std::chrono::steady_clock::now();
    std::string sAcc;
    for (int i = 0; i < N; ++i) sAcc += 'a';
    auto t4 = std::chrono::steady_clock::now();

    std::cout << "Text " << N << " concats (us)       : "
              << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << '\n';
    std::cout << "std::string " << N << " concats (us): "
              << std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count() << '\n';
    return 0;
}
