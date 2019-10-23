#include <iostream>
#include <fstream>
#include <set>

struct Order {
    int start;
    int end;
    int price;
};

struct OrderCmp {
    bool operator()(const Order& lhs, const Order& rhs) const {
        return lhs.start < rhs.start;
    }
};

using Orders = std::set<Order, OrderCmp>;

void parseOrders(Orders &orders, std::ifstream &file, int orderCount)
{
    std::string temp;
    for (size_t i = 0; i < orderCount; ++i) {
        Order order{};
        file >> order.start;
        file >> order.end;
        file >> order.price;

        orders.emplace(order);
    }
}

void findSolution(Orders &oders, Orders::iterator it, int price, int endTime, int &maxPrice)
{
    if (it == oders.end())
    {
        maxPrice = std::max(maxPrice, price);
        return;
    }

    auto oldIt = it++;
    // doesn't include it'th order
    findSolution(oders, it, price, endTime, maxPrice);

    bool isValid = endTime <= oldIt->start;
    if (isValid) {
        price += oldIt->price;
        endTime = oldIt->end;
        // include it'th order
        findSolution(oders, it, price, endTime, maxPrice);
    }
}

int main() {
    std::ifstream infile("input.txt");

    int orderCount;
    infile >> orderCount;

    Orders orders;
    parseOrders(orders, infile, orderCount);

    int maxPrice = 0;
    auto it = orders.begin();
    findSolution(orders, it, 0, 0, maxPrice);
    std::cout << maxPrice << std::endl;
}