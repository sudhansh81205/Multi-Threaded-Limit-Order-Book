#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <map>
#include <deque>
#include <unordered_map>
#include "OrderLocation.h"
#include "Order.h"

using namespace std;

class OrderBook
{
public:
    map<int, deque<Order>, greater<int>> buyBook;
    map<int, deque<Order>> sellBook;
    unordered_map<int, OrderLocation> orderIndex;

    void addOrder(const Order& order) ;
    void printOrderBook() const;
    bool cancelOrder(int orderId);
    
};

#endif