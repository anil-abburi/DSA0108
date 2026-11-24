#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    std::string isbn;
    int copies;

    static int validateCopies(int c) {
        if (c < 0) {
            throw std::invalid_argument("Number of copies cannot be negative");
        }
        return c;
    }

public:
    Book(const std::string& t, const std::string& a, const std::string& i, int c)
        : title(t), author(a), isbn(i), copies(validateCopies(c)) {}

    explicit Book(const std::string& donatedTitle)
        : Book(donatedTitle, "Unknown", "UNASSIGNED", 1) {}

    Book()
        : Book("Untitled", "Unknown", "NONE", 0) {}

    void print() const {
        std::cout << "Title: " << title << " | Author: " << author
                  << " | ISBN: " << isbn << " | Copies: " << copies << '\n';
    }
};

void showBook(const Book& b) {
    b.print();
}

int main() {
    Book full("Clean C++", "Stephan Roth", "978-1484227923", 5);
    Book donated("Donated Algorithms Guide");
    Book emptyRecord;

    full.print();
    donated.print();
    emptyRecord.print();

    Book shelf[2];
    shelf[0].print();

    showBook(Book("Explicit Call Example"));

    try {
        Book invalid("Broken Book", "Author", "000", -3);
        invalid.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "Validation caught: " << e.what() << '\n';
    }
    return 0;
}
