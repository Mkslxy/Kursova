#include <iostream>
#include "ProductManager.h"
#include <limits>
#include "Checkout.h"
#include "string"
#include "Employee.h"
#include "Logger.h"
#include <fstream>

using namespace std;

Logger logger;

void logAction(const string &username, const string &action) {
    ofstream logFile;
    if (username == "admin") {
        logFile.open("admin_log.txt", ios::app);
    } else {
        logFile.open("user_log.txt", ios::app);
    }
    if (logFile.is_open()) {
        logFile << action << endl;
        logFile.close();
    } else {
        cout << "Unable to open log file." << endl;
    }
}

//name = admin , password = 1
//name = user , password = 2

int main() {
    ProductManager manager;
    manager.load();
    Checkout reg(manager);


    string username, password;
    bool authenticated = false;

    while (!authenticated) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == "admin" && password == "1") {
            cout << "Authentication successful! You are logged in as an administrator.\n";
            authenticated = true;
        } else if (username == "user" && password == "2") {
            cout << "Authentication successful! You are logged in as a user.\n";
            authenticated = true;
        } else {
            cout << "Incorrect username or password. Please try again!\n";
        }
    }

    int choice;


    if (username == "admin") {

        do {
            cout << "\n";
            cout << "--------------------------------------------------\n";
            cout << "-----------------Electronics store----------------\n";
            cout << "--------------------------------------------------\n";
            cout << "\n";
            cout << "1. Add Electrical Product.\n";
            cout << "2. Edit Electrical Product.\n";
            cout << "3. Sort Products by Price.\n";
            cout << "4. Filter Products by Price.\n";
            cout << "5. Search Products by Key.\n";
            cout << "6. Add Product to Cart.\n";
            cout << "7. Print Receipt.\n";
            cout << "8. Clear Cart.\n";
            cout << "9. View All Products.\n";
            cout << "10. Delete Product.\n";
            cout << "11. Show Employee.\n";
            cout << "12. Information about store.\n";
            cout << "13. User assistant.\n";
            cout << "14. Exit.\n";

            try {
                cin >> choice;
                if (cin.fail()) {
                    throw invalid_argument("Invalid choice. Please enter a number between 1 and 13.");
                }
            } catch (const invalid_argument &e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << endl;
                continue;
            }

            switch (choice) {
                case 1: {
                    string name;
                    string unitOfMeasurement;
                    int cost;
                    int amount;
                    int lastDate;
                    int power;
                    cout << endl;

                    cout << "Enter the name of the product: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << endl;

                    cout << "Enter the cost: ";
                    while (!(cin >> cost)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << endl;
                        cout << "Invalid input. Please enter a valid cost: ";
                    }
                    cout << endl;

                    cout << "Enter the amount: ";
                    while (!(cin >> amount)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << endl;
                        cout << "Invalid input. Please enter a valid amount: ";
                    }
                    cout << endl;

                    cout << "Enter the unit of measurement: ";
                    cin.ignore();
                    getline(cin, unitOfMeasurement);
                    cout << endl;

                    cout << "Enter the power: ";
                    while (!(cin >> power)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << endl;
                        cout << "Invalid input. Please enter a valid power: ";
                    }
                    cout << endl;

                    ElectricalProduct newProduct(name, cost, amount, unitOfMeasurement, lastDate, power);
                    manager.add(newProduct);
                    manager.save();

                    logAction(username, "Added product: " + name);
                    break;
                }

                case 2: {
                    string name;
                    cout << "Enter the name of the product to edit: ";
                    cin.ignore();
                    getline(cin, name);
                    manager.edit(name);

                    logAction(username, "Edited product: " + name);
                    break;
                }
                case 3:
                    manager.sortPrice();
                    logAction(username, "Sorted products by price.");
                    break;
                case 4: {
                    int minPrice, maxPrice;


                    cout << "Enter minimum price: ";
                    while (!(cin >> minPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << endl;

                        cout << "Invalid input. Please enter a valid minimum price: ";
                    }
                    cout << endl;

                    cout << "Enter maximum price: ";
                    while (!(cin >> maxPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << endl;

                        cout << "Invalid input. Please enter a valid maximum price: ";
                    }

                    cout << endl;

                    manager.filterPrice(minPrice, maxPrice);
                    logAction(username, "Filtered products by price range: " + to_string(minPrice) + " to " +
                                        to_string(maxPrice));
                    break;
                }
                case 5: {
                    string key;
                    cout << "Enter the key to search (e.g., product name): ";
                    cin.ignore();
                    getline(cin, key);
                    cout << endl;
                    manager.search(key);
                    logAction(username, "Searched for product: " + key);
                    break;
                }
                case 6: {
                    string name;
                    int quantity;
                    cout << "Enter the name of the product to add to the cart: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "Enter quantity: ";
                    while (!(cin >> quantity)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid quantity: ";
                    }

                    bool found = false;
                    vector<std::pair<ElectricalProduct, int>> productsToAdd;
                    for (const auto& product : manager.getProducts()) {
                        if (product.getName() == name) {
                            productsToAdd.push_back(make_pair(product, quantity));
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Product not found.\n";
                    } else {
                        if (manager.updateProductQuantity(name, quantity)) {
                            reg.add(productsToAdd);
                            cout << "Product added!\n";
                            logAction(username, "Added product to cart: " + name + " (Quantity: " + to_string(quantity) + ")");
                        } else {
                            cout << "Failed to add product to cart: Insufficient stock or product not found.\n";
                        }
                    }
                    break;
                }



                case 7:
                    reg.print();
                    logAction(username, "Printed receipt.");
                    break;
                case 8:
                    reg.clear();
                    logAction(username, "Cleared cart.");
                    break;
                case 9: {
                    manager.viewAll();
                    logAction(username, "Viewed all products.");
                    break;
                }
                case 10: {
                    string name;
                    cout << "Enter the name of the product to delete: ";
                    cin.ignore();
                    getline(cin, name);
                    manager.deleteProduct(name);
                    logAction(username, "Deleted product: " + name);
                    break;
                }
                case 11: {
                    Employee emp1(30, "John", "Brown", 180, "Athletic", "Doe", 50000);
                    emp1.Print();
                    logAction(username, "Displayed employee information.");
                    break;
                }
                case 12: {
                    std::cout << std::string(80, '-') << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "This electronics store specializes in selling a wide range of electrical appliances and components."
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "The store offers various products, including household electronics, industrial components, and power tools,"
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "catering to both everyday consumers and professional contractors." << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "With a focus on quality, affordability, and cutting-edge technology," << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "the store ensures that customers have access to the latest electrical products,"
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "supported by excellent customer service and knowledgeable staff." << std::endl;
                    std::cout << std::string(80, '-') << std::endl;
                    logAction(username, "Displayed store information.");
                    break;
                    case 13: {
                        std::cout << std::string(80, '-') << std::endl;
                        std::cout << std::left << std::setw(75)
                                  << "This program, developed in C++ using the CLion environment, is an electronic product management system for a store."
                                  << std::endl;
                        std::cout << std::left << std::setw(75)
                                  << "It enables users to load, save, edit, and delete products, as well as view their details."
                                  << std::endl;
                        std::cout << std::left << std::setw(75)
                                  << "Users can add products to the cart, print receipts, and clear the cart."
                                  << std::endl;
                        std::cout << std::left << std::setw(75)
                                  << "The program also offers filtering and searching functions for products based on various criteria, such as price or name."
                                  << std::endl;
                        std::cout << std::left << std::setw(75)
                                  << "To track user actions, logging has been implemented, allowing the system to save information about completed actions."
                                  << std::endl;
                        std::cout << std::string(80, '-') << std::endl;
                        break;
                    }

                }
            }
        } while (choice != 14);

    } else {
        do {
            cout << "\n";
            cout << "--------------------------------------------------\n";
            cout << "-----------------Electronics store----------------\n";
            cout << "--------------------------------------------------\n";
            cout << "\n";
            cout << "1. Sort Products by Price.\n";
            cout << "2. Filter Products by Price.\n";
            cout << "3. Search Products by Key.\n";
            cout << "4. Add Product to Cart.\n";
            cout << "5. Print Receipt.\n";
            cout << "6. Clear Cart.\n";
            cout << "7. View All Products.\n";
            cout << "8. Information about store.\n";
            cout << "9. User assistant.\n";
            cout << "10. Exit\n";

            try {
                cin >> choice;
                if (cin.fail()) {

                    cout << endl;
                    throw invalid_argument("Invalid choice. Please enter a number between 1 and 13.");
                }
            } catch (const invalid_argument &e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << endl;
                continue;
            }

            switch (choice) {
                case 1:
                    manager.sortPrice();
                    logAction(username, "Sorted products by price.");
                    break;
                case 2: {
                    int minPrice, maxPrice;
                    cout << "Enter minimum price: ";
                    while (!(cin >> minPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << endl;
                        cout << "Invalid input. Please enter a valid minimum price: ";
                    }
                    cout << endl;

                    cout << "Enter maximum price: ";
                    while (!(cin >> maxPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << endl;
                        cout << "Invalid input. Please enter a valid maximum price: ";
                    }
                    cout << endl;

                    manager.filterPrice(minPrice, maxPrice);
                    logAction(username, "Filtered products by price range: " + to_string(minPrice) + " to " +
                                        to_string(maxPrice));
                    break;
                }
                case 3: {
                    string key;
                    cout << "Enter the key to search (e.g., product name): ";
                    cin.ignore();
                    getline(cin, key);
                    manager.search(key);
                    logAction(username, "Searched for product: " + key);
                    break;
                }
                case 4: {
                    string name;
                    int quantity;
                    cout << "Enter the name of the product to add to the cart: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "Enter quantity: ";
                    while (!(cin >> quantity)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid quantity: ";
                    }

                    bool found = false;
                    vector<std::pair<ElectricalProduct, int>> productsToAdd;
                    for (const auto &product: manager.getProducts()) {
                        if (product.getName() == name) {
                            productsToAdd.push_back(make_pair(product, quantity));
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Product not found.\n";
                    } else {

                        if (manager.updateProductQuantity(name, quantity)) {
                            reg.add(productsToAdd);
                            cout << "Product added!\n";
                            logAction(username,
                                      "Added product to cart: " + name + " (Quantity: " + to_string(quantity) + ")");
                        } else {
                            cout << endl;
                            cout << "Failed to add product to cart: Insufficient stock or product not found.\n";
                        }
                    }
                    break;
                }

                case 5:
                    cout << endl;

                    reg.print();
                    logAction(username, "Printed receipt.");
                    break;
                case 6:
                    cout << endl;

                    reg.clear();
                    logAction(username, "Cleared cart.");
                    break;
                case 7: {
                    cout << endl;

                    manager.viewAll();
                    logAction(username, "Viewed all products.");
                    break;
                }
                case 8: {
                    std::cout << std::string(80, '-') << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "This electronics store specializes in selling a wide range of electrical appliances and components."
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "The store offers various products, including household electronics, industrial components, and power tools,"
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "catering to both everyday consumers and professional contractors." << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "With a focus on quality, affordability, and cutting-edge technology," << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "the store ensures that customers have access to the latest electrical products,"
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "supported by excellent customer service and knowledgeable staff." << std::endl;
                    std::cout << std::string(80, '-') << std::endl;
                    logAction(username, "Displayed store information.");
                    break;
                }
                case 9: {
                    std::cout << std::string(80, '-') << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "This program, developed in C++ using the CLion environment, is an electronic product management system for a store."
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "Users can add products to the cart, print receipts, and clear the cart."
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "The program also offers filtering and searching functions for products based on various criteria, such as price or name."
                              << std::endl;
                    std::cout << std::left << std::setw(75)
                              << "To track user actions, logging has been implemented, allowing the system to save information about completed actions."
                              << std::endl;
                    std::cout << std::string(80, '-') << std::endl;
                }
            }
        } while (choice != 10);
    }

    logger.log("Program exited.");
    return 0;
}
