#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "Logger.h"

class Product {
protected:
    std::string name;
    int cost;
    int amount;
    std::string unitOfMeasurement;
    int lastDate;

public:
    Product(const std::string &name, int cost, int amount, const std::string &unitOfMeasurement, int lastDate)
            : name(name), cost(cost), amount(amount), unitOfMeasurement(unitOfMeasurement), lastDate(lastDate) {
        logger.log("Product created: " + name);
    }

    virtual void Print() const = 0;

    std::string getName() const { return name; }

    int getCost() const { return cost; }

    int getAmount() const { return amount; }

    std::string getUnitOfMeasurement() const { return unitOfMeasurement; }

    int getLastDate() const { return lastDate; }

    void setName(const std::string &n) { name = n; }

    void setCost(int c) { cost = c; }

    void setAmount(int a) { amount = a; }

    void setUnitOfMeasurement(const std::string &u) { unitOfMeasurement = u; }

    void setLastDate(int l) { lastDate = l; }

    virtual ~Product() {
        logger.log("Product destroyed: " + name);  // Log when Product is destroyed
    }
};

#endif // PRODUCT_H
