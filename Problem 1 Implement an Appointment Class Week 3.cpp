#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Date {
public:
	int month;
	int day;
	int year;
	// Constructor accepts month, day, year to match MM DD YYYY format
	Date(int m=0, int d=0, int y=0): month(m), day(d), year(y)  {}
};

class Appointment {
protected:
	string description;
	Date date;
public:
	Appointment(const string &desc, const Date &d): description(desc), date(d) {}
	virtual ~Appointment() {}
	virtual bool occurs_on( int month, int day, int year) const = 0;
	virtual void print() const {
		cout << description << " (" << date.month << "/" << date.day << "/" << date.year << ")";
	}
	const string &getDescription() const { return description; }
};

class Day : public Appointment {
public:
	Day(const string &desc, const Date &d): Appointment(desc, d) {}
	bool occurs_on(int month, int day, int year) const override {
		return (month == date.month && day == date.day && year == date.year);
	}
	void print() const override {
		cout << "Day: ";
		Appointment::print();
		cout << '\n';
	}
};

class Monthly : public Appointment {
public:
	Monthly(const string &desc, const Date &d): Appointment(desc, d) {}
	bool occurs_on(int month, int day, int year) const override {
		// monthly appointment occurs each month on the same day
		return (day == date.day && year == date.year);
	}
	void print() const override {
		cout << "Monthly: ";
		Appointment::print();
		cout << " (This occurs every month on day " << date.day << ")\n";
	}
};

int main() {
	vector<unique_ptr<Appointment>> appts;

	//Mix of appointments
	appts.emplace_back(make_unique<Day>("Dentist Appointment", Date(10, 18, 2025)));
	appts.emplace_back(make_unique<Monthly>("Pay rent", Date(10, 1, 2025)));
	appts.emplace_back(make_unique<Day>("My friend's birthday", Date(11, 2, 2025)));
	appts.emplace_back(make_unique<Monthly>("Project sync", Date(10, 18, 2025))); // occurs every month on day 18
	appts.emplace_back(make_unique<Day>("Conference", Date(10, 18, 2024)));

	cout << "You have " << appts.size() << " appointments" << "\n"; 

	// find appointments usuing a sample date
	cout << "Enter a date to find appointments. Use format MM DD YYYY (e.g. 10 18 2025): ";
	int m, d, y;
	if (!(cin >> m >> d >> y)) {
		cerr << "Invalid input. Exiting.\n";
		return 1;
	}

	bool found = false;
	cout << "Appointments on " << m << "/" << d << "/" << y << ":\n";
	for (const auto &a : appts) {
		if (a->occurs_on(m, d, y)) {
			a->print();
			found = true;
		}
	}
	if (!found) cout << "(NO Appointments on this Date)\n";

	return 0;
}
