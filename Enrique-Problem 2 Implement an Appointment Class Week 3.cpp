#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

/* ============================================================
   Base Class: Person
   ============================================================ */
class Person {
protected:
    string name;
    string phone;
    string email;

public:
    // Constructor
    Person(string n, string p, string e)
        : name(n), phone(p), email(e) {}

    // Virtual toString() method
    virtual string toString() const {
        return "Person named " + name +
               " has phone number " + phone +
               " and can be reached at " + email;
    }

    // Virtual destructor
    virtual ~Person() = default;
};

/* ============================================================
   Derived Class: Student
   ============================================================ */
class Student : public Person {
private:
    string yearInCollege;

public:
    Student(string n, string p, string e, string year)
        : Person(n, p, e), yearInCollege(year) {}

    string toString() const override {
        return Person::toString() + " is in the " + yearInCollege + " year";
    }
};

/* ============================================================
   Derived Class: Employee
   ============================================================ */
class Employee : public Person {
protected:
    double salary;

public:
    Employee(string n, string p, string e, double s)
        : Person(n, p, e), salary(s) {}

    string toString() const override {
        return Person::toString() + " earns " + to_string(salary) + " annually";
    }
};

/* ============================================================
   Derived Class: Faculty (inherits from Employee)
   ============================================================ */
class Faculty : public Employee {
private:
    string title;

public:
    Faculty(string n, string p, string e, double s, string t)
        : Employee(n, p, e, s), title(t) {}

    string toString() const override {
        return Employee::toString() + " is a/an " + title;
    }
};

/* ============================================================
   Derived Class: Staff (inherits from Employee)
   ============================================================ */
class Staff : public Employee {
private:
    string role;

public:
    Staff(string n, string p, string e, double s, string r)
        : Employee(n, p, e, s), role(r) {}

    string toString() const override {
        return Employee::toString() + " handles " + role;
    }
};

/* ============================================================
   Main Function: Test Program
   ============================================================ */
int main() {
    cout << "===== PERSON CLASS HIERARCHY TEST =====\n\n";

    // Vector of pointers to Person
    vector<Person*> people;

    // Add instances of each class type
    people.push_back(new Person("Susan", "800-555-1212", "susan@quirkymail.com"));
    people.push_back(new Student("Jerry", "123-456-7890", "jerjer@nat.edu", "sophomore"));
    people.push_back(new Employee("Larry", "333-444-5555", "larry@threestooges.org", 123456.00));
    people.push_back(new Faculty("Linda", "987-654-3210", "lindalou@whoknew.edu", 150000.00, "adjunct professor"));
    people.push_back(new Staff("Jane", "567-123-6565", "jane@whizkid.com", 100000.00, "registration"));

    // Display each object's info
    for (const auto& p : people) {
        cout << p->toString() << endl;
    }

    // Free allocated memory
    for (auto& p : people) {
        delete p;
    }

    cout << "\n===== END OF PROGRAM =====\n";
    return 0;
}
