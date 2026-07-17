#ifndef ORDER_H
#define ORDER_H

#include <chrono>

using namespace std;

enum class Side
{
    BUY,
    SELL
};

class Order
{
public:
    int id;
    Side side;          // Better name than isBuy
    int price;
    int quantity;
    long long timestamp;

    Order(int id, Side s, int p, int q)
    {
        this->id = id;
        side = s;
        price = p;
        quantity = q;

        timestamp = chrono::duration_cast<chrono::microseconds>(
                        chrono::steady_clock::now().time_since_epoch())
                        .count();
    }
};

#endif