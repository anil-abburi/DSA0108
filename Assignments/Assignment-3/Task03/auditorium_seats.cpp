#include <iostream>
#include <string>

class AuditoriumEvent {
    std::string name;
    int rows;
    int cols;
    char** seats;
    int bookedCount;

public:
    AuditoriumEvent(const std::string& eventName, int r, int c)
        : name(eventName), rows(r > 0 ? r : 0), cols(c > 0 ? c : 0), seats(nullptr), bookedCount(0) {
        if (rows > 0 && cols > 0) {
            seats = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                seats[i] = new char[cols];
                for (int j = 0; j < cols; ++j) {
                    seats[i][j] = 'O';
                }
            }
        }
        std::cout << "[Construct] " << name << " (" << rows << "x" << cols << ")\n";
    }

    AuditoriumEvent(const AuditoriumEvent&) = delete;
    AuditoriumEvent& operator=(const AuditoriumEvent&) = delete;

    ~AuditoriumEvent() {
        for (int i = 0; i < rows; ++i) {
            delete[] seats[i];
        }
        delete[] seats;
        std::cout << "[Destroy] " << name << " | Booked seats: " << bookedCount
                  << "/" << (rows * cols) << '\n';
    }

    bool bookSeat(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || seats[r][c] == 'X') return false;
        seats[r][c] = 'X';
        ++bookedCount;
        return true;
    }

    bool cancelSeat(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || seats[r][c] == 'O') return false;
        seats[r][c] = 'O';
        --bookedCount;
        return true;
    }

    size_t estimatedBytes() const {
        return static_cast<size_t>(rows) * sizeof(char*) +
               static_cast<size_t>(rows) * static_cast<size_t>(cols) * sizeof(char);
    }
};

int main() {
    AuditoriumEvent stackEvent("Annual Convocation", 10, 20);
    stackEvent.bookSeat(0, 0);
    stackEvent.bookSeat(2, 5);
    stackEvent.cancelSeat(0, 0);
    std::cout << "10x20 memory (bytes): " << stackEvent.estimatedBytes() << '\n';

    {
        AuditoriumEvent blockEvent("Seminar", 100, 200);
        std::cout << "100x200 memory (bytes): " << blockEvent.estimatedBytes() << '\n';
    }

    AuditoriumEvent* heapEvent = new AuditoriumEvent("Concert", 1000, 2000);
    std::cout << "1000x2000 memory (bytes): " << heapEvent->estimatedBytes() << '\n';
    delete heapEvent;

    AuditoriumEvent zeroEvent("Empty Hall", 0, 10);
    return 0;
}
