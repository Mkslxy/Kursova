#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <iostream>
#include "Logger.h"

class Human {
protected:
    int age;
    string firstName;
    string hair;
    int height;
    string physique;
    string lastName;

public:
    Human(int age, const std::string& firstName, const std::string& hair, int height, const std::string& physique, const std::string& lastName)
            : age(age), firstName(firstName), hair(hair), height(height), physique(physique), lastName(lastName) {
        logger.log("Human created: " + firstName + " " + lastName);
    }

    Human(const Human& other)
            : age(other.age), firstName(other.firstName), hair(other.hair), height(other.height), physique(other.physique), lastName(other.lastName) {
        logger.log("Human copied: " + firstName + " " + lastName);
    }


    virtual void Print() const {
        std::cout << "Age = " << age << "\n"
                  << "First Name = " << firstName << "\n"
                  << "Hair = " << hair << "\n"
                  << "Height = " << height << "\n"
                  << "Physique = " << physique << "\n"
                  << "Last Name = " << lastName << "\n";
    }

    virtual ~Human() {
        logger.log("Human destroyed: " + firstName + " " + lastName);
    }
};

#endif  HUMAN_H
