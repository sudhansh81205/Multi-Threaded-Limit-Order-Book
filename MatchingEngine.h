#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include "ThreadSafeQueue.h"
#include <thread>
#include <atomic>
#include <vector>
#include "Trade.h"
#include "OrderBook.h"
#include "Logger.h"

class MatchingEngine{
private:
    OrderBook orderBook;
    ThreadSafeQueue<Order> orderQueue;
    thread consumerThread;
    atomic<bool> running;
    vector<Trade> tradeHistory;
    Logger logger;
public:
    MatchingEngine();
    ~MatchingEngine();
    void submitOrder(const Order& order);
    void consumer();
    void processOrder(Order order);
    bool cancelOrder(int orderId);
    void matchOrders();
    void printTradeHistory();
    bool modifyOrder(int orderId, int newPrice, int newQty);
};
#endif