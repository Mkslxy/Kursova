#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Human.h"
#include <string>

class Employee : public Human {
private:
    int payment;

public:
    Employee(int age, const std::string &firstName, const std::string &hair, int height, const std::string &physique,
             const std::string &lastName, int payment)
            : Human(age, firstName, hair, height, physique, lastName), payment(payment) {
        logger.log("Employee created: " + firstName + " " + lastName);
    }

    Employee(const Employee &other)
            : Human(other), payment(other.payment) {
        logger.log("Employee copied: " + getFirstName() + " " + getLastName());
    }

    void Print() const override {
        Human::Print();
        std::cout << "Payment = " << payment << "\n";
    }



    ~Employee() override {
        logger.log("Employee destroyed: " + getFirstName() + " " + getLastName());
    }

    string getFirstName() const { return firstName; }

    string getLastName() const { return lastName; }

};

#endif  EMPLOYEE_H
