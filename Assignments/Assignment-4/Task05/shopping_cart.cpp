#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;

public:
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double t = 0.0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100.0 - discount) / 100.0;
    }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Cart directCart;
    directCart.add("Milk", 60).add("Bread", 45);
    std::cout << "Direct access    : " << directCart.total() << '\n';

    Cart* ptrCart = &directCart;
    ptrCart->add("Eggs", 90);
    std::cout << "Pointer access   : " << ptrCart->total() << '\n';

    Cart& refCart = directCart;
    refCart.setDiscount(10);
    std::cout << "Reference access : " << refCart.total() << '\n';

    Cart* heapCart = new Cart();
    heapCart->add("Rice", 500).add("Oil", 220).setDiscount(5);
    std::cout << "Heap access      : " << heapCart->total() << '\n';

    Cart thirdCart;
    thirdCart.add("Coffee", 350);

    Cart* activeCarts[3] = {&directCart, heapCart, &thirdCart};
    Cart* highest = activeCarts[0];
    for (int i = 1; i < 3; ++i) {
        if (activeCarts[i]->total() > highest->total()) {
            highest = activeCarts[i];
        }
    }
    std::cout << "Highest cart total: " << highest->total() << '\n';

    delete heapCart;
    return 0;
}
