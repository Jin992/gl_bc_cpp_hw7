#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

class AbstractEmployee {
private:
	std::string first_name_;
	std::string last_name_;
	std::string job_;

public:
	AbstractEmployee()
	: first_name_("none"), last_name_("none"), job_("vagabond")
	{}
	AbstractEmployee(const std::string& fn, const std::string& ln, const std::string& j)
	: first_name_(fn), last_name_(ln), job_(j)
	{}
	virtual void showAll() const { // prints all data with names
		std::cout << first_name_ << " " << last_name_ << " job " << job_ << std::endl;
	}

	virtual void setAll() { // gets data for class fields from user)
		std::cout << "Please enter credentials:" << std::endl;
		std::cout << "Enter name: ";
		std::cin >> first_name_;
		std::cout << "Enter last name: ";
		std::cin >> last_name_;
		std::cout << "Enter job: ";
		std::cin >> job_;
	}
	friend std::ostream& operator<<(std::ostream& os, const AbstractEmployee& e); // prints first name & last name
	virtual ~AbstractEmployee() = 0;
};

inline AbstractEmployee::~AbstractEmployee() = default;

class Employee : public AbstractEmployee {
public:
	Employee()
	: AbstractEmployee()
	{}

	Employee(const std::string &fn, const std::string &ln, const std::string &j)
	: AbstractEmployee(fn, ln, j)
	{}

	void showAll() const override {
		std::cout << "Employee: ";
		AbstractEmployee::showAll();
	}
	void setAll() override {
		std::cout << "Employee registration." << std::endl;
		AbstractEmployee::setAll();
	}

};

class Manager : virtual public AbstractEmployee {
private:
	int in_charge_of_; // number of employees manager is in charge of

protected:
	int inChargeOf() const { return in_charge_of_; } // output
	void setInChargeOf(int employees){ in_charge_of_ = employees; } // input

public:
	Manager()
	: AbstractEmployee(), in_charge_of_(0)
	{}

	Manager(const std::string &fn, const std::string &ln, const std::string &j, int ico)
	: AbstractEmployee(fn, ln, j), in_charge_of_(ico)
	{}

	Manager(const AbstractEmployee &e, int ico)
	: AbstractEmployee(e), in_charge_of_(ico)
	{}

	Manager(const Manager &m)
	: AbstractEmployee(m), in_charge_of_(m.in_charge_of_)
	{}

	~Manager() override = default;

	void showAll() const override{
		std::cout << "Manager: ";
		AbstractEmployee::showAll();
		std::cout << "In charge of: " << in_charge_of_ << std::endl;
	}

	void setAll() override{
		std::cout << "Manager registration." << std::endl;
		AbstractEmployee::setAll();
		std::cout << "Quantity of employees responsible for: ";
		std::cin >> in_charge_of_;
	}
};

class Fink: virtual public AbstractEmployee { // strikebreaker
private:
	std::string reports_to_; // person, who he reports to

protected:
	const std::string reportsTo() const { return reports_to_; }
	void setReportsTo(const std::string head) { reports_to_ = head; }

public:
	Fink()
	: AbstractEmployee(), reports_to_("none")
	{}

	Fink(const std::string &fn, const std::string &ln, const std::string &j, const std::string &rpo)
	: AbstractEmployee(fn, ln, j), reports_to_(rpo)
	{}


	Fink(const AbstractEmployee &e, const std::string &rpo)
	: AbstractEmployee(e), reports_to_(rpo)
	{}

	Fink(const Fink &e)
	: AbstractEmployee(e), reports_to_(e.reports_to_)
	{}

	void showAll()  const override {
		std::cout << "Fink: ";
		AbstractEmployee::showAll();
		std::cout << "Supervisor: " << reports_to_ << std::endl;
	}

	void setAll() override {
		std::cout << "Fink registration." << std::endl;
		AbstractEmployee::setAll();
		std::cout << "name of supervisor : ";
		std::cin >> reports_to_;
	}
};

class HighFink: public Manager, public Fink { // fink supervisor
public:
	HighFink()
	: AbstractEmployee(), Manager(), Fink()
	{}

	HighFink(const std::string &fn, const std::string &ln, const std::string &j, const std::string &rpo, int ico)
	: AbstractEmployee(fn, ln, j), Manager(fn, ln, j, ico), Fink(fn, ln, j, rpo)
	{}

	HighFink(const AbstractEmployee &e, const std::string &rpo, int ico)
	: AbstractEmployee(e), Manager(e, ico), Fink(e, rpo)
	{}

	HighFink(const Fink &f, int ico)
	: AbstractEmployee(f), Manager(f, ico), Fink(f)
	{}

	HighFink(const Manager &m, const std::string &rpo)
	: AbstractEmployee(m), Manager(m), Fink(m, rpo)
	{}

	HighFink(const HighFink &h)
	: AbstractEmployee(h), Manager(h), Fink(h)
	{}

	void showAll() const override {
		std::cout << "HighFink: ";
		AbstractEmployee::showAll();
		std::cout << "Supervisor: " << Fink::reportsTo() << std::endl;
		std::cout << "In charge of: " << Manager::inChargeOf() << " employee." << std::endl;
	}
	void setAll() override
	{
		std::string head;
		int ico = 0;

		std::cout << "High Fink registration." << std::endl;
		AbstractEmployee::setAll();
		std::cout << "Name of supervisor : ";
		std::cin >> head;
		Fink::setReportsTo(head);
		std::cout << "Quantity of employees responsible for: ";
		std::cin >> ico;
		Manager::setInChargeOf(ico);
	}
};

std::ostream& operator<<(std::ostream &os, const AbstractEmployee &e){
	os << "ostream overload: "  << e.first_name_ << " " << e.last_name_ << " job " <<  e.job_;
	return os;
}
#endif // EMPLOYEE_H