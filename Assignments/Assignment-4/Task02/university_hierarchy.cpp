#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p) : name(n), id(i), phone(p) {}
    virtual ~Person() = default;
    std::string getName() const { return name; }
    int getId() const { return id; }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p, const std::string& prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c) {}
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p, const std::string& dept, double sal)
        : Person(n, i, p), department(dept), salary(sal) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double c, const std::string& dept, double sal)
        : Person(n, i, p), Student(n, i, p, prog, c), Staff(n, i, p, dept, sal) {}

    void print() const {
        std::cout << "TA: " << name << " (ID " << id << ") | " << programme
                  << " CGPA " << cgpa << " | Dept: " << department << " | Stipend: " << salary << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double c, double f)
        : Person(n, i, p), Student(n, i, p, prog, c), fellowship(f) {}

    void print() const {
        std::cout << "Scholar: " << name << " (ID " << id << ") | Fellowship: " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta("Arjun", 501, "9876543210", "M.Tech IT", 9.1, "IT", 18000.0);
    ResearchScholar rs("Divya", 502, "9123456780", "PhD CS", 9.4, 35000.0);
    ta.print();
    rs.print();
    std::cout << "sizeof(TeachingAssistant): " << sizeof(TeachingAssistant) << " bytes\n";
    return 0;
}
