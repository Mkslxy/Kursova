#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "ElectricalProduct.h"
#include "Logger.h"

class Checkout {
private:
    std::vector<std::pair<ElectricalProduct, int>> cart;
    ProductManager& manager;

public:

    Checkout(ProductManager& manager) : manager(manager) {
        logger.log("Checkout created");
    }


    void add(const std::vector<std::pair<ElectricalProduct, int>>& products) {
        for (const auto& item : products) {
            const ElectricalProduct& product = item.first;
            int quantity = item.second;

            if (quantity > 0 && quantity <= product.getAmount()) {
                cart.push_back(std::make_pair(product, quantity));
                logger.log("Added " + std::to_string(quantity) + " of " + product.getName() + " to cart.");


            } else {
                logger.log("Invalid quantity or not enough stock for " + product.getName());
            }
        }
    }


    void print() const {
        double total = 0.0;
        std::cout << "----- Receipt -----\n";
        for (const auto& item : cart) {
            const ElectricalProduct& product = item.first;
            int quantity = item.second;
            double productTotal = product.getCost() * quantity;
            total += productTotal;

            std::cout << std::setw(20) << std::left << "Name of your product: " << product.getName() << '\n'
                      << std::setw(10) << std::right << "Cost of your product: " << product.getCost() << '\n'
                      << std::setw(10) << std::right << "The quantity product: " << quantity << '\n'
                      << std::setw(15) << std::right << "Total cost: " << productTotal << '\n'
                      << std::endl;
        }
        std::cout << "--------------------\n";
        std::cout << std::setw(30) << std::right << "Total: " << total << std::endl;
        logger.log("Printed receipt with total: " + std::to_string(total));
    }


    void clear() {
        cart.clear();
        logger.log("Cart cleared.");
        std::cout << "Cart cleared.\n";
    }
};

#endif // CHECKOUT_H
