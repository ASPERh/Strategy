#include <iostream>
#include <string>

using namespace std;

class ShippingStrategy {
public:
    virtual double calculate(double orderAmount) const = 0;
    virtual ~ShippingStrategy() {}
};

class RegularMailStrategy : public ShippingStrategy {
public:
    double calculate(double orderAmount) const override {
        return 5.0;
    }
};

class ExpressDeliveryStrategy : public ShippingStrategy {
public:
    double calculate(double orderAmount) const override {
        return 10.0 + (0.1 * orderAmount);
    }
};

class ShippingContext {
private:
    ShippingStrategy* strategy;

public:
    ShippingContext(ShippingStrategy* strategy) : strategy(strategy) {}

    void setStrategy(ShippingStrategy* newStrategy) {
        strategy = newStrategy;
    }

    double calculateShippingCost(double orderAmount) const {
        if (strategy) {
            return strategy->calculate(orderAmount);
        }
        return 0.0;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    RegularMailStrategy regularMailStrategy;
    ShippingContext shippingContext(&regularMailStrategy);

    double shippingCost = shippingContext.calculateShippingCost(50.0);
    cout << "Стоимость доставки (обычная почта): $" << shippingCost << "\n";

    ExpressDeliveryStrategy expressDeliveryStrategy;
    shippingContext.setStrategy(&expressDeliveryStrategy);

    shippingCost = shippingContext.calculateShippingCost(100.0);
    cout << "Стоимость доставки (экспресс): $" << shippingCost << "\n";

    return 0;
}