#include <iostream>
#include <string>

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    std::string passenger;

public:
    explicit BusTicket(const std::string& name) : seat(0), passenger(name) {
        if (issued < CAPACITY) {
            ++issued;
            seat = issued;
        }
    }

    static int count() { return issued; }

    void print() const {
        std::cout << passenger << ": "
                  << (seat > 0 ? "Seat " + std::to_string(seat) : std::string("Waiting List"))
                  << '\n';
    }
};

int BusTicket::issued = 0;

void bookBatch() {
    BusTicket batch[2] = {BusTicket("Kiran"), BusTicket("Latha")};
    for (const BusTicket& t : batch) t.print();
    std::cout << "Issued so far: " << BusTicket::count() << '\n';
}

int main() {
    bookBatch();
    bookBatch();
    return 0;
}
