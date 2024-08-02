#include <iostream>
#include "Human.h"

using namespace std;

class Employee : public Human {
private:
    string rank;
    int experience;
    string desire;

public:
    Employee(int age, string firstName, string hair, int height, string physique, string lastName, string rank,
             int experience, string desire) : Human(age, firstName, hair, height, physique, lastName), rank(rank),experience(experience),desire(desire) {}


};
