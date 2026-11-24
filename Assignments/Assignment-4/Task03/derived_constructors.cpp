#include <iostream>
#include <string>

class Address {
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {
        std::cout << "  +Address(" << city << ")\n";
    }
    ~Address() { std::cout << "  -Address(" << city << ")\n"; }
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Course {
    std::string code;

public:
    explicit Course(const std::string& c) : code(c) {
        std::cout << "  +Course(" << code << ")\n";
    }
    ~Course() { std::cout << "  -Course(" << code << ")\n"; }
    std::string getCode() const { return code; }
};

class Person {
protected:
    std::string name;
    Address home;

public:
    Person(const std::string& n, const std::string& city, int pin)
        : name(n), home(city, pin) {
        std::cout << "+Person(" << name << ")\n";
    }
    virtual ~Person() { std::cout << "-Person(" << name << ")\n"; }
};

class Student : virtual public Person {
protected:
    Course major;

public:
    Student(const std::string& n, const std::string& city, int pin, const std::string& courseCode)
        : Person(n, city, pin), major(courseCode) {
        std::cout << "+Student(" << name << ")\n";
    }
    ~Student() override { std::cout << "-Student(" << name << ")\n"; }
};

class Staff : virtual public Person {
protected:
    std::string dept;

public:
    Staff(const std::string& n, const std::string& city, int pin, const std::string& d)
        : Person(n, city, pin), dept(d) {
        std::cout << "+Staff(" << name << ")\n";
    }
    ~Staff() override { std::cout << "-Staff(" << name << ")\n"; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, const std::string& city, int pin,
                      const std::string& courseCode, const std::string& d)
        : Person(n, city, pin), Student(n, city, pin, courseCode), Staff(n, city, pin, d) {
        std::cout << "+TeachingAssistant(" << name << ")\n";
    }
    ~TeachingAssistant() override { std::cout << "-TeachingAssistant(" << name << ")\n"; }
};

int main() {
    std::cout << "--- Creating TeachingAssistant ---\n";
    {
        TeachingAssistant ta("Kavya", "Chennai", 600001, "DSA01", "IT");
    }
    std::cout << "--- Destroyed ---\n";
    return 0;
}
