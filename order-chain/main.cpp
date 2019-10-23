#include <iostream>
#include <fstream>
#include <vector>

struct Order {
    int start;
    int end;
    int price;
};

using Orders = std::vector<Order>;

Orders parseOrders(std::ifstream &file, int orderCount)
{
    Orders orders;
    for (auto i = 0; i < orderCount; ++i) {
        Order order{};
        file >> order.start;
        file >> order.end;
        file >> order.price;

        orders.emplace_back(order);
    }

    return orders;
}

void findSolution(Orders &orders, int oderIndex, int price, int endTime, int &maxPrice)
{
    if (oderIndex == orders.size()) {
        maxPrice = std::max(maxPrice, price);
        return;
    }

    // doesn't include oderIndex'th order
    findSolution(orders, oderIndex + 1, price, endTime, maxPrice);

    bool isValid = endTime <= orders[oderIndex].start;
    if (isValid) {
        // include oderIndex'th order
        price += orders[oderIndex].price;
        endTime = orders[oderIndex].end;
        findSolution(orders, oderIndex + 1, price, endTime, maxPrice);
    }
}

int main()
{
    std::ifstream infile("input.txt");

    int orderCount;
    infile >> orderCount;
    Orders orders = std::move(parseOrders(infile, orderCount));
    infile.close();

    std::sort(orders.begin(),
              orders.end(),
              [](const Order &lhs, const Order &rhs) -> bool { return lhs.start < rhs.start; });

    int maxPrice = 0;
    findSolution(orders, 0, 0, 0, maxPrice);
    std::cout << maxPrice << std::endl;

    return 0;
}