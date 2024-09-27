#include <iostream>
#include "ProductManager.h"
#include <limits>
#include "Checkout.h"
#include "string"
#include "Employee.h"
#include "Logger.h"
#include <fstream>  // Include fstream for file operations

using namespace std;

Logger logger;

void logAction(const string& username, const string& action) {
    ofstream logFile;
    if (username == "admin") {
        logFile.open("admin_log.txt", ios::app); // Append mode for admin log
    } else {
        logFile.open("user_log.txt", ios::app); // Append mode for user log
    }
    if (logFile.is_open()) {
        logFile << action << endl; // Log the action
        logFile.close();
    } else {
        cout << "Unable to open log file." << endl;
    }
}

int main() {
    ProductManager manager;
    manager.load();
    Checkout reg(manager);

    string username, password;
    bool authenticated = false;

    // Authentication loop
    while (!authenticated) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Check credentials
        if (username == "admin" && password == "1") {
            cout << "Authentication successful! You are logged in as an administrator.\n";
            authenticated = true; // Set authentication flag
        } else if (username == "user" && password == "2") {
            cout << "Authentication successful! You are logged in as a user.\n";
            authenticated = true; // Set authentication flag
        } else {
            cout << "Incorrect username or password. Please try again!\n";
        }
    }

    int choice;

    // Check user type
    if (username == "admin") {
        // Loop for administrator
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
            cout << "13. Exit.\n";

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

                    cout << "Enter the name of the product: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "Enter the cost: ";
                    while (!(cin >> cost)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid cost: ";
                    }

                    cout << "Enter the amount: ";
                    while (!(cin >> amount)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid amount: ";
                    }

                    cout << "Enter the unit of measurement: ";
                    cin.ignore();
                    getline(cin, unitOfMeasurement);

                    cout << "Enter the power: ";
                    while (!(cin >> power)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid power: ";
                    }

                    ElectricalProduct newProduct(name, cost, amount, unitOfMeasurement, lastDate, power);
                    manager.add(newProduct);
                    manager.save();

                    logAction(username, "Added product: " + name); // Log the action
                    break;
                }
                case 2: {
                    string name;
                    cout << "Enter the name of the product to edit: ";
                    cin.ignore();
                    getline(cin, name);
                    manager.edit(name);

                    logAction(username, "Edited product: " + name); // Log the action
                    break;
                }
                case 3:
                    manager.sortPrice();
                    logAction(username, "Sorted products by price."); // Log the action
                    break;
                case 4: {
                    int minPrice, maxPrice;
                    cout << "Enter minimum price: ";
                    while (!(cin >> minPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid minimum price: ";
                    }
                    cout << "Enter maximum price: ";
                    while (!(cin >> maxPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid maximum price: ";
                    }
                    manager.filterPrice(minPrice, maxPrice);
                    logAction(username, "Filtered products by price range: " + to_string(minPrice) + " to " + to_string(maxPrice)); // Log the action
                    break;
                }
                case 5: {
                    string key;
                    cout << "Enter the key to search (e.g., product name): ";
                    cin.ignore();
                    getline(cin, key);
                    manager.search(key);
                    logAction(username, "Searched for product: " + key); // Log the action
                    break;
                }
                case 6: {
                    string name;
                    int quantity;
                    cout << "Enter the name of the product to add to cart: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "Enter quantity: ";
                    while (!(cin >> quantity)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid quantity: ";
                    }

                    bool found = false;
                    for (const auto &product: manager.getProducts()) {
                        if (product.getName() == name) {
                            reg.add(product, quantity);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Product not found.\n";
                    } else {
                        logAction(username, "Added product to cart: " + name + " (Quantity: " + to_string(quantity) + ")"); // Log the action
                    }
                    break;
                }
                case 7:
                    reg.print();
                    logAction(username, "Printed receipt."); // Log the action
                    break;
                case 8:
                    reg.clear();
                    logAction(username, "Cleared cart."); // Log the action
                    break;
                case 9: {
                    manager.viewAll();
                    logAction(username, "Viewed all products."); // Log the action
                    break;
                }
                case 10: {
                    string name;
                    cout << "Enter the name of the product to delete: ";
                    cin.ignore();
                    getline(cin, name);
                    manager.deleteProduct(name);
                    logAction(username, "Deleted product: " + name); // Log the action
                    break;
                }
                case 11: {
                    Employee emp1(30, "John", "Brown", 180, "Athletic", "Doe", 50000);
                    emp1.Print();
                    logAction(username, "Displayed employee information."); // Log the action
                    break;
                }
                case 12: {
                    cout
                            << "This electronics store specializes in selling a wide range of electrical appliances and components. The store offers various products, "
                               "including household electronics, industrial components, and power tools, catering to both everyday consumers and professional contractors. "
                               "With a focus on quality, affordability, and cutting-edge technology, the store ensures that customers have access to the latest electrical products,"
                               " supported by excellent customer service and knowledgeable staff.\n";
                    logAction(username, "Displayed store information."); // Log the action
                    break;
                }
            }
        } while (choice != 13);

    } else {
        // Loop for user
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
            cout << "9. Exit.\n";

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
                case 1:
                    manager.sortPrice();
                    logAction(username, "Sorted products by price."); // Log the action
                    break;
                case 2: {
                    int minPrice, maxPrice;
                    cout << "Enter minimum price: ";
                    while (!(cin >> minPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid minimum price: ";
                    }
                    cout << "Enter maximum price: ";
                    while (!(cin >> maxPrice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid maximum price: ";
                    }
                    manager.filterPrice(minPrice, maxPrice);
                    logAction(username, "Filtered products by price range: " + to_string(minPrice) + " to " + to_string(maxPrice)); // Log the action
                    break;
                }
                case 3: {
                    string key;
                    cout << "Enter the key to search (e.g., product name): ";
                    cin.ignore();
                    getline(cin, key);
                    manager.search(key);
                    logAction(username, "Searched for product: " + key); // Log the action
                    break;
                }
                case 4: {
                    string name;
                    int quantity;
                    cout << "Enter the name of the product to add to cart: ";
                    cin.ignore();
                    getline(cin, name);

                    cout << "Enter quantity: ";
                    while (!(cin >> quantity)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid quantity: ";
                    }

                    bool found = false;
                    for (const auto &product: manager.getProducts()) {
                        if (product.getName() == name) {
                            reg.add(product, quantity);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Product not found.\n";
                    } else {
                        logAction(username, "Added product to cart: " + name + " (Quantity: " + to_string(quantity) + ")"); // Log the action
                    }
                    break;
                }
                case 5:
                    reg.print();
                    logAction(username, "Printed receipt."); // Log the action
                    break;
                case 6:
                    reg.clear();
                    logAction(username, "Cleared cart."); // Log the action
                    break;
                case 7: {
                    manager.viewAll();
                    logAction(username, "Viewed all products."); // Log the action
                    break;
                }
                case 8: {
                    cout
                            << "This electronics store specializes in selling a wide range of electrical appliances and components. The store offers various products, "
                               "including household electronics, industrial components, and power tools, catering to both everyday consumers and professional contractors. "
                               "With a focus on quality, affordability, and cutting-edge technology, the store ensures that customers have access to the latest electrical products,"
                               " supported by excellent customer service and knowledgeable staff.\n";
                    logAction(username, "Displayed store information."); // Log the action
                    break;
                }
            }
        } while (choice != 9);
    }

    logger.log("Program exited.");
    return 0;
}
