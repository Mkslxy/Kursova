#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "ElectricalProduct.h"
#include "Logger.h"


class Checkout {
private:
    std::vector<std::pair<ElectricalProduct, int>> cart; // Pair of product and its quantity
    ProductManager& manager; // Reference to ProductManager

public:
    Checkout(ProductManager& mgr) : manager(mgr) {} // Constructor to accept ProductManager reference

    void add(const ElectricalProduct& product, int quantity) {
        if (quantity > 0 && quantity <= product.getAmount()) {
            cart.push_back(std::make_pair(product, quantity)); // Add product and its quantity to the cart
            manager.updateProductQuantity(product.getName(), quantity); // Update quantity in ProductManager
            logger.log("Added " + std::to_string(quantity) + " of " + product.getName() + " to cart.");
        } else {
            logger.log("Invalid quantity or not enough stock for " + product.getName());
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

            std::cout << std::setw(20) << std::left << product.getName()
                      << std::setw(10) << std::right << product.getCost()
                      << std::setw(10) << std::right << quantity
                      << std::setw(15) << std::right << productTotal
                      << std::endl;
        }
        std::cout << "--------------------\n";
        std::cout << std::setw(30) << std::right << "Total: " << total << std::endl;
        logger.log("Printed receipt with total: " + std::to_string(total));  // Log receipt printing
    }

    void clear() {
        cart.clear();
        logger.log("Cart cleared.");
        std::cout << "Cart cleared.\n";
    }
};

#endif // CHECKOUT_H
