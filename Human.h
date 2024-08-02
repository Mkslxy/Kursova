#include <iostream>

using namespace std;

class Human {
protected:
    int age;
    string firstName;
    string hair;
    int height;
    string physique;
    string lastName;

public:

    Human(int age, string firstName, string hair, int height, string phsique, string lastName) : age(age), firstName(
            firstName), hair(hair), height(height), physique(phsique), lastName(lastName) {}


    void Print() {
        cout << " Age = " << age << ". Name = " << firstName << ". Hair = " << hair
             << ". Height = " << height << ". Physique = " << physique << ". LastName = " << lastName << ".\n";
    }
};
