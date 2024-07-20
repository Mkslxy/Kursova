#include <iostream>

using namespace std;

class Employee {
private:
    int age;
    string name;
    string hair;
    int height;
    string physique;

public:

    Employee(int age, string name, string hair, int height, string phsique) : age(age), name(name), hair(hair),
                                                                              height(height), physique(phsique) {}

    void Print() {
        cout << " Age = " << age << ". Name = " << name << ". Hair = " << hair
        << ". Height = " << height << ". Physique = "<< physique << ".\n";
    }
};
