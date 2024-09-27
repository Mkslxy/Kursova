#ifndef ELECTRICALPRODUCT_H
#define ELECTRICALPRODUCT_H

#include "Product.h"
#include "Logger.h"

class ElectricalProduct : public Product {
private:
    int power;

public:
    ElectricalProduct(const std::string& name, int cost, int amount, const std::string& unitOfMeasurement, int lastDate, int power)
            : Product(name, cost, amount, unitOfMeasurement, lastDate), power(power) {
        logger.log("ElectricalProduct created: " + name);
    }

    void Print() const override {
        std::cout << "Name: " << name << "\nCost: " << cost << "\nAmount: " << amount
                  << "\nUnit of Measurement: " << unitOfMeasurement << "\nSupply Date: " << lastDate
                  << "\nPower: " << power << "W\n";
    }

    int getPower() const { return power; }
    void setPower(int p) { power = p; }

    ~ElectricalProduct() override {
        logger.log("ElectricalProduct destroyed: " + name);
    }
};

#endif // ELECTRICALPRODUCT_H
