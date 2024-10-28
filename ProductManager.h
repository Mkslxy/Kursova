#include "ElectricalProduct.h"
#include "Logger.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream>
#include <regex>
using namespace std;

class ProductManager {
private:
    vector<ElectricalProduct> products;

public:
    bool isValidDate(const std::string& date) {
        if (date.length() != 8) return false;
        if (!std::all_of(date.begin(), date.end(), ::isdigit)) return false;

        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(4, 2));
        int day = std::stoi(date.substr(6, 2));


        if (month < 1 || month > 12) return false;


        if (day < 1 || day > 31) return false;


        if (month == 2) {
            if (day > 29) return false;
            if (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) return false;
        }


        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

        return true;
    }


    int getProductAmount(const std::string& productName) const {
        for (const auto& product : products) {
            if (product.getName() == productName) {
                return product.getAmount();
            }
        }
        return 0;
    }

    void add(const ElectricalProduct &product) {
        for (const auto &existingProduct : products) {
            if (existingProduct.getName() == product.getName()) {
                cout << "Product with name '" << product.getName() << "' already exists. Please use a different name.\n";
                logger.log("Attempted to add a product with an existing name: " + product.getName());
                return;
            }
        }

        int lastDate;
        string dateInput;
        while (true) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<endl;

            cout << "Please  enter the supply date (YYYYMMDD):";
            getline(cin, dateInput);


            dateInput.erase(remove(dateInput.begin(), dateInput.end(), '\n'), dateInput.end());
            dateInput.erase(remove(dateInput.begin(), dateInput.end(), '\r'), dateInput.end());


            if (dateInput.length() == 8 && all_of(dateInput.begin(), dateInput.end(), ::isdigit)) {

                int year = stoi(dateInput.substr(0, 4));
                int month = stoi(dateInput.substr(4, 2));
                int day = stoi(dateInput.substr(6, 2));

                if (month >= 1 && month <= 12) {

                    int daysInMonth = (month == 2) ? (year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 29 : 28) :
                                      (month == 4 || month == 6 || month == 9 || month == 11 ? 30 : 31);

                    if (day >= 1 && day <= daysInMonth) {
                        lastDate = year * 10000 + month * 100 + day;
                        break;
                    } else {
                        cout << "Invalid day for the given month. Please try again.\n";
                    }
                } else {
                    cout << "Invalid month. Please try again.\n";
                }
            } else {
                cout << "Invalid date format. Press Enter!\n";
            }
        }



        ElectricalProduct newProduct(product.getName(), product.getCost(), product.getAmount(), product.getUnitOfMeasurement(), lastDate, product.getPower());
        products.push_back(newProduct);
        cout << "Product added: " << newProduct.getName() << endl;
        logger.log("Product added: " + newProduct.getName());
        save();
    }






    void edit(const string &name) {
        for (auto &product : products) {
            if (product.getName() == name) {
                string newName, unitOfMeasurement;
                int cost = product.getCost(), amount = product.getAmount(), power = product.getPower();
                string input;

                cout << "Enter new name (or press Enter to keep '" << product.getName() << "'): ";
                getline(cin, newName);

                if (!newName.empty()) {
                    bool nameExists = false;
                    for (const auto &existingProduct : products) {
                        if (existingProduct.getName() == newName && &existingProduct != &product) {
                            nameExists = true;
                            break;
                        }
                    }

                    if (nameExists) {
                        cout<<endl;
                        cout << "Product with name '" << newName << "' already exists. Please use a different name.\n";
                        logger.log("Attempted to rename product to an existing name: " + newName);
                        return;
                    } else {
                        product.setName(newName);
                        logger.log("Product name updated: " + newName);
                    }
                }

                cout << endl;

                cout << "Enter new cost (or press Enter to keep " << cost << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        cost = stoi(input);
                        product.setCost(cost);
                        logger.log("Product cost updated for " + product.getName() + ": " + to_string(cost));
                    } catch (const invalid_argument &) {
                        cout << "Invalid input. Keeping old cost.\n";
                    }
                }

                cout << endl;

                cout << "Enter new amount (or press Enter to keep " << amount << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        amount = stoi(input);
                        product.setAmount(amount);
                        logger.log("Product amount updated for " + product.getName() + ": " + to_string(amount));
                    } catch (const invalid_argument &) {
                        cout << "Invalid input. Keeping old amount.\n";
                    }
                }

                cout << endl;

                cout << "Enter new unit of measurement (or press Enter to keep '" << product.getUnitOfMeasurement() << "'): ";
                getline(cin, unitOfMeasurement);
                if (!unitOfMeasurement.empty()) {
                    product.setUnitOfMeasurement(unitOfMeasurement);
                    logger.log("Product unit of measurement updated: " + unitOfMeasurement);
                }

                cout << endl;

                cout << "Enter new last date of supply (YYYYMMDD, or press Enter to keep " << product.getLastDate() << "): ";
                while (true) {
                    getline(cin, input);
                    if (input.empty()) {

                        cout << "Keeping existing last date: " << product.getLastDate() << endl;
                        break;
                    } else if (isValidDate(input)) {
                        int lastDate = stoi(input);
                        product.setLastDate(lastDate);
                        logger.log("Product last date updated for " + product.getName() + ": " + to_string(lastDate));
                        break;
                    } else {
                        cout<< endl;
                        cout << "Invalid date format. Please enter a valid date (YYYYMMDD) or press Enter to skip: ";
                    }
                }

                cout << endl;

                cout << "Enter new power (or press Enter to keep " << power << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        power = stoi(input);
                        product.setPower(power);
                        logger.log("Product power updated for " + product.getName() + ": " + to_string(power));
                    } catch (const invalid_argument &) {
                        cout << "Invalid input. Keeping old power.\n";
                    }
                }

                cout << endl;

                save();
                cout << "Product updated.\n";
                logger.log("Product updated: " + product.getName());
                return;
            }
        }
        cout << "Product not found.\n";
        logger.log("Product not found during edit attempt: " + name);
    }


    void sortPrice() {
        sort(products.begin(), products.end(), [](const ElectricalProduct &a, const ElectricalProduct &b) {
            return a.getCost() > b.getCost();
        });
        cout << "Products sorted by price in descending order.\n";
        logger.log("Products sorted by price in descending order.");
    }

    void filterPrice(int minPrice, int maxPrice) const {
        for (const auto &product : products) {
            if (product.getCost() >= minPrice && product.getCost() <= maxPrice) {
                product.Print();
                cout << endl;
            }
        }
        logger.log("Filtered products by price range: " + to_string(minPrice) + " to " + to_string(maxPrice));
    }

    void search(const string &key) const {
        bool found = false;
        for (const auto &product : products) {
            if (product.getName().find(key) != string::npos) {
                product.Print();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No products found matching: " << key << endl;
            logger.log("No products found matching search key: " + key);
        } else {
            logger.log("Products found matching search key: " + key);
        }
    }

    void load() {
        std::ifstream inFile("products.txt");
        if (!inFile.is_open()) {
            logger.log("Сan not be opened products.txt.");
            return;
        }

        std::string line;
        while (getline(inFile, line)) {
            std::istringstream ss(line);
            std::string name, unitOfMeasurement;
            int cost, amount, lastDate, power;

            getline(ss, name, ',');
            ss >> cost;
            ss.ignore();
            ss >> amount;
            ss.ignore();
            getline(ss, unitOfMeasurement, ',');
            ss >> lastDate;
            ss.ignore();
            ss >> power;


            ElectricalProduct product(name, cost, amount, unitOfMeasurement, lastDate, power);
            products.push_back(product);
        }

        inFile.close();
        logger.log("Uploaded from products.txt.");
    }

    void save() {
        std::ofstream outFile("products.txt");
        for (const auto& product : products) {
            outFile << product.getName() << ","
                    << product.getCost() << ","
                    << product.getAmount() << ","
                    << product.getUnitOfMeasurement() << ","
                    << product.getLastDate() << ","
                    << product.getPower() << "\n";
        }
        outFile.close();
    }

    void decrementProductAmount(const std::string& productName, int quantity) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setAmount(product.getAmount() - quantity);
                return;
            }
        }
        logger.log("Product not found for decrement: " + productName);
    }
    bool updateProductQuantity(const std::string& productName, int quantity) {

        for (auto& product : products) {
            if (product.getName() == productName) {
                int newQuantity = product.getAmount() - quantity;


                if (newQuantity < 0) {
                    logger.log("Cannot update quantity of " + productName + ": insufficient stock.");
                    std::cout << "Cannot add " << quantity << " of " << productName << ": insufficient stock.\n";
                    return false;
                }

                product.setAmount(newQuantity);


                save();
                logger.log("Updated quantity of " + productName + " to " + std::to_string(newQuantity));
                return true;
            }
        }
        logger.log("Product not found: " + productName);
        return false;
    }




    void viewAll() const {
        if (products.empty()) {
            cout << "No products available.\n";
            logger.log("Attempted to view all products, but none are available.");
        } else {
            for (const auto &product : products) {
                product.Print();
                cout << endl;
            }
            logger.log("Viewed all products.");
        }
    }


    void deleteProduct(const string &name) {
        cout << "Attempting to delete product: " << name << endl;
        auto it = remove_if(products.begin(), products.end(), [&](const ElectricalProduct &product) {
            return product.getName() == name;
        });

        if (it != products.end()) {
            products.erase(it, products.end());
            save();
            cout << "Product found and removed.\n";
            logger.log("Product deleted: " + name);
        } else {
            cout << "Product not found.\n";
            logger.log("Product not found during deletion attempt: " + name);
        }
    }



    const vector<ElectricalProduct> &getProducts() const { return products; }
};