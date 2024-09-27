#include "ElectricalProduct.h"
#include "Logger.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream> // Для istringstream
#include <regex>
using namespace std;

class ProductManager {
private:
    vector<ElectricalProduct> products;

public:
    bool isValidDate(const std::string& date) {
        if (date.length() != 8) return false; // Дата должна быть длиной 8 символов
        if (!std::all_of(date.begin(), date.end(), ::isdigit)) return false; // Дата должна содержать только цифры

        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(4, 2));
        int day = std::stoi(date.substr(6, 2));

        // Проверка корректности месяца
        if (month < 1 || month > 12) return false;

        // Проверка корректности дня в зависимости от месяца
        if (day < 1 || day > 31) return false;


        if (month == 2) {
            if (day > 29) return false; // Февраль не может иметь более 29 дней
            if (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) return false; // Проверка на високосный год
        }


        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

        return true; // Дата валидна
    }

    void add(const ElectricalProduct &product) {
        // Проверка на уникальность имени продукта
        for (const auto &existingProduct : products) {
            if (existingProduct.getName() == product.getName()) {
                cout << "Product with name '" << product.getName() << "' already exists. Please use a different name.\n";
                logger.log("Attempted to add a product with an existing name: " + product.getName());
                return;  // Выход из метода, если продукт с таким именем уже существует
            }
        }

        int lastDate; // Переменная для хранения даты
        string dateInput;
        while (true) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Please enter the supply date (YYYYMMDD): ";
            getline(cin, dateInput); // Получаем ввод пользователя

            // Убираем лишние символы новой строки или пробелы
            dateInput.erase(remove(dateInput.begin(), dateInput.end(), '\n'), dateInput.end());
            dateInput.erase(remove(dateInput.begin(), dateInput.end(), '\r'), dateInput.end());

            // Проверка формата даты
            if (dateInput.length() == 8 && all_of(dateInput.begin(), dateInput.end(), ::isdigit)) {
                // Проверка на валидность даты
                int year = stoi(dateInput.substr(0, 4));
                int month = stoi(dateInput.substr(4, 2));
                int day = stoi(dateInput.substr(6, 2));

                if (month >= 1 && month <= 12) {
                    // Проверка на количество дней в месяце
                    int daysInMonth = (month == 2) ? (year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 29 : 28) :
                                      (month == 4 || month == 6 || month == 9 || month == 11 ? 30 : 31);

                    if (day >= 1 && day <= daysInMonth) {
                        lastDate = year * 10000 + month * 100 + day; // Преобразование в YYYYMMDD
                        break; // Выход из цикла, если дата валидна
                    } else {
                        cout << "Invalid day for the given month. Please try again.\n";
                    }
                } else {
                    cout << "Invalid month. Please try again.\n";
                }
            } else {
                cout << "Invalid date format. Please enter date in YYYYMMDD format.\n";
            }
        }

        // Создание продукта с валидной датой
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
                    product.setName(newName);
                    logger.log("Product name updated: " + newName);
                }

                cout << "Enter new cost (or press Enter to keep " << cost << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        cost = stoi(input);
                        product.setCost(cost);
                        logger.log("Product cost updated for " + product.getName() + ": " + to_string(cost));
                    } catch (const invalid_argument&) {
                        cout << "Invalid input. Keeping old cost.\n";
                    }
                }

                cout << "Enter new amount (or press Enter to keep " << amount << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        amount = stoi(input);
                        product.setAmount(amount);
                        logger.log("Product amount updated for " + product.getName() + ": " + to_string(amount));
                    } catch (const invalid_argument&) {
                        cout << "Invalid input. Keeping old amount.\n";
                    }
                }

                cout << "Enter new unit of measurement (or press Enter to keep '" << product.getUnitOfMeasurement() << "'): ";
                getline(cin, unitOfMeasurement);
                if (!unitOfMeasurement.empty()) {
                    product.setUnitOfMeasurement(unitOfMeasurement);
                    logger.log("Product unit of measurement updated: " + unitOfMeasurement);
                }

                // Запрашиваем новую дату
                cout << "Enter new last date of supply (YYYYMMDD, or press Enter to keep " << product.getLastDate() << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    if (!isValidDate(input)) {
                        cout << "Invalid date format. Please enter date in YYYYMMDD format.\n";
                        return; // Завершить выполнение метода, если формат неверный
                    }
                    int lastDate = stoi(input);
                    product.setLastDate(lastDate);
                    logger.log("Product last date updated for " + product.getName() + ": " + to_string(lastDate));
                }

                cout << "Enter new power (or press Enter to keep " << power << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        power = stoi(input);
                        product.setPower(power);
                        logger.log("Product power updated for " + product.getName() + ": " + to_string(power));
                    } catch (const invalid_argument&) {
                        cout << "Invalid input. Keeping old power.\n";
                    }
                }

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
            logger.log("Не удалось открыть файл products.txt.");
            return; // Завершаем выполнение функции
        }

        std::string line;
        while (getline(inFile, line)) {
            std::istringstream ss(line);
            std::string name, unitOfMeasurement;
            int cost, amount, lastDate, power;

            // Считываем данные, разделенные запятыми
            getline(ss, name, ',');
            ss >> cost;
            ss.ignore(); // Игнорируем запятую
            ss >> amount;
            ss.ignore(); // Игнорируем запятую
            getline(ss, unitOfMeasurement, ',');
            ss >> lastDate;
            ss.ignore(); // Игнорируем запятую
            ss >> power;

            // Создаем продукт и добавляем его в вектор
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
                    << product.getPower() << "\n"; // Сохраняем данные в файл
        }
        outFile.close();
    }

    void updateProductQuantity(const std::string& productName, int quantity) {
        // Loop through products and update the quantity
        for (auto& product : products) { // Assuming 'products' is a vector of ElectricalProduct
            if (product.getName() == productName) {
                int newQuantity = product.getAmount() - quantity;
                product.setAmount(newQuantity); // Assuming a setter exists

                // Update the product file
                save(); // Call a method to save the updated products list to product.txt
                logger.log("Updated quantity of " + productName + " to " + std::to_string(newQuantity));
                return;
            }
        }
        logger.log("Product not found: " + productName);
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
