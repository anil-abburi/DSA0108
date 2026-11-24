#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int readIntInRange(const std::string& prompt, int lo, int hi) {
    int val = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val && val >= lo && val <= hi) {
            return val;
        }
        std::cout << "Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printMoney(long long paise) {
    std::cout << "Rs " << std::setw(4) << (paise / 100) << '.'
              << std::setw(2) << std::setfill('0') << (paise % 100) << std::setfill(' ');
}

int main() {
    int zone = readIntInRange("Enter Zone (0=Inner, 1=Middle, 2=Outer): ", 0, 2);
    int hour = readIntInRange("Enter Hour (0-23): ", 0, 23);

    constexpr long long BASE[] = {1000, 2000, 3000};
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long fare = peak ? BASE[zone] + BASE[zone] * 20 / 100 : BASE[zone];

    std::cout << "\n--- Journey Report ---\n";
    std::cout << std::left << std::setw(14) << "Zone" << ": " << zone << '\n';
    std::cout << std::left << std::setw(14) << "Hour" << ": " << std::right << std::setw(2)
              << std::setfill('0') << hour << ":00" << std::setfill(' ') << '\n';
    std::cout << std::left << std::setw(14) << "Peak" << ": " << (peak ? "Yes" : "No") << '\n';
    std::cout << std::left << std::setw(14) << "Fare" << ": ";
    printMoney(fare);
    std::cout << '\n';
    return 0;
}
