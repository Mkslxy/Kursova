#include <iostream>
#include "Employee.h"
#include <fstream>

using namespace std;

int main() {

    Employee Artem(25, "Artem", "Blond", 187, "Slim" , "Petykhachnyi");

    try {
        int choice, choice2, choice3, choice4;
        string password;
        bool pass;
        do {
            cout << "Please enter the password (Admin or User):" << endl;
            cin >> password;
            if (password != "Admin" && password != "User") {
                throw pass = false;
            }
        } while (password != "Admin" && password != "User");
        if (password == "User") {
            do {

                ofstream outFile("user_choice.txt", ios::app);
                if (!outFile.is_open()) {
                    cerr << "Error: Unable to open user_choice.txt\n";
                    return 1;
                }

                cout << " Please choose which animal you want take in your house \n";
                cout << " 1. DOG \n";
                cout << " 2. CAT \n";
                cout << " 3. RABBIT \n";
                cout << " 4. EXIT \n";


                cin >> choice;

                if (choice != 1 && choice != 2 && choice != 3) {
                    throw pass = false;
                } else {
                    switch (choice) {
                        case 1 :
                            outFile << "User selected option 1 - Take a dog\n";
                            cout << " Which one you want to take ?\n";
                            cout << endl;

                            cout << "1.\n";
                            doberman.print();
                            cout << endl;

                            cout << "2.\n";
                            german_shepherd.print();
                            cout << endl;

                            cout << "3.\n";

                            other.getName();
                            other.setName("Vasiliy");

                            other.getSize();
                            other.setSize(62);

                            other.print();

                            cout << endl;

                            cout << endl;
                            cin >> choice2;

                            if (choice2 != 1 && choice2 != 2 && choice != 3) {
                                throw pass = false;
                            } else {

                                switch (choice2) {
                                    case 1 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 2 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 3 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    default:
                                        cout << " We don't have these Dog !\n";
                                        break;
                                }
                                break;
                            }
                        case 2:
                            outFile << "User selected option 2 - Take a cat\n";
                            cout << "Which one you want to pick ?\n";

                            cout << "1.\n";
                            Cat().print();
                            cout << endl;

                            cout << "2.\n";
                            copy.print();
                            cout << endl;

                            cout << "3.\n";
                            special_cat.print();
                            cout << endl;

                            cin >> choice3;

                            if (choice3 != 1 && choice3 != 2 && choice3 != 3) {
                                throw pass = false;
                            } else {

                                switch (choice3) {
                                    case 1 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 2 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 3 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    default:
                                        cout << " We don't have these Cat !\n";
                                        break;
                                }
                                break;
                            }
                        case 3:
                            outFile << "User selected option 3 - Take a rabbit\n";
                            cout << " Which one you want to pick up ?\n";

                            cout << endl;

                            cout << "1.\n";
                            special_rabbit.print();
                            cout << endl;

                            cout << "2.\n";
                            Rabbit::setBehavior("Calm");
                            common_rabbit.print();
                            cout << endl;

                            cout << "3.\n";
                            Rabbit::setBehavior("Running");
                            middle_rabbit.print();

                            cout << endl;

                            cin >> choice4;

                            if (choice4 != 1 && choice4 != 2 && choice4 != 3) {
                                throw pass = false;
                            } else {

                                switch (choice4) {
                                    case 1 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 2 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 3 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    default:
                                        cout << " We don't have these Rabbit !\n";
                                        break;
                                }
                                break;
                            }
                    }
                }
            } while (choice != 4);
        } else {
            ofstream outFile("admin_choice.txt", ios::app);
            if (!outFile.is_open()) {
                cerr << "Error: Unable to open user_choice.txt\n";
                return 1;
            }
            do {
                cout << " Please choose which animal you want take in your house \n";
                cout << " 1. DOG \n";
                cout << " 2. OUR EMPLOYEES\n";
                cout << " 3. BUYERS\n";
                cout << " 4. YOUR CASHBOX \n";
                cout << " 5. UPDATING INFORMATION \n";
                cout << " 6. ADDING THE PRODUCT \n";
                cout << " 7. EXIT \n";

                cin >> choice;

                if (choice != 1 && choice != 2
                    && choice != 3 && choice != 4
                    && choice != 5 && choice != 6 && choice != 7) {
                    throw pass = false;
                } else {
                    switch (choice) {
                        case 1 :
                            outFile << "Admin selected option 1 - Take a dog\n";
                            cout << " Which one you want to take ?\n";
                            cout << endl;

                            cout << "1.\n";
                            doberman.print();
                            cout << endl;

                            cout << "2.\n";
                            german_shepherd.print();
                            cout << endl;

                            cout << "3.\n";

                            other.getName();
                            other.setName("Vasiliy");

                            other.getSize();
                            other.setSize(62);

                            other.print();

                            cout << endl;

                            if (!pDog) {

                            } else {
                                pDog->print();
                            }


                            cout << endl;
                            cin >> choice2;

                            if (choice2 != 1 && choice2 != 2 && choice != 3) {
                                throw pass = false;
                            } else {

                                switch (choice2) {
                                    case 1 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 2 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    case 3 :
                                        cout << " Thanks for buying !\n";
                                        break;

                                    default:
                                        cout << " We don't have these Dog !\n";
                                        break;
                                }
                                break;
                            }
                        case 2:
                            outFile << "Admin selected option 4 - View employees\n";
                            Artem.Print();
                            cout << endl;
                            break;

                        case 3:
                            outFile << "Admin selected option 5 - View buyers\n";
                            buyer.Print();
                            cout << endl;
                            cout << endl;
                            break;

                        case 4:
                            outFile << "Admin selected option 6 - View cashbox and news\n";

                            pCashbox->print();
                            cout << endl;

                            stufff.doSomeStuff();
                            second_stuff.doSomeStuff();

                            pb->doSomeStuff();

                            cout << endl;
                            break;

                        case 5: {
                            outFile << "Admin selected option 7 - Update information\n";
                            pCashbox->setIncome(100);
                            break;
                        }
                        case 6:
                            outFile << "Admin selected option 8 - Add a product\n";
                            cout << " You have been added a new dog!\n";
                            pDog->print();

                            break;

                    }
                }
            } while (choice != 7);
        }
    } catch (const bool pass) {
        cout << " Error\n";
    }

    Artem.Print();

    return 0;
}
