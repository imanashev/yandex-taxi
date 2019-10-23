#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Order {
    int start;
    int end;
    int price;
};

void parseOrders(std::vector<Order> &orders, std::ifstream &file, int N)
{
    std::string temp;
    for (size_t i = 0; i < N; ++i) {
        Order order{};
        file >> order.start;
        file >> order.end;
        file >> order.price;

        orders.emplace_back(order);
    }
}

void findSolution(std::vector<Order> &oders, int orderNum, int price, int endTime, int &result)
{
    if (orderNum == oders.size())
    {
            result = std::max(result, price);
        return;
    }

    // doesn't include orderNum'th order
    findSolution(oders, orderNum + 1, price, endTime, result);

    bool isValid = endTime <= oders[orderNum].start;
    if (isValid) {
        price += oders[orderNum].price;
        endTime = oders[orderNum].end;
        // include orderNum'th order
        findSolution(oders, orderNum + 1, price, endTime, result);
    }
}

int main() {
    std::ifstream infile("input.txt");

    int N;
    infile >> N;

    std::vector<Order> orders;
    parseOrders(orders, infile, N);

    std::sort(orders.begin(), orders.end(), [](const Order &a, const Order &b) -> bool
        {
          return a.start < b.start;
        }
    );

    int result = 0;
    findSolution(orders, 0, 0, 0, result);
    std::cout << result << std::endl;
}