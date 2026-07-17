#include <iostream>
#include <algorithm>

#include "MatchingEngine.h"

using namespace std;

// Constructor
MatchingEngine::MatchingEngine()
{
    running = true;
    consumerThread = thread(&MatchingEngine::consumer, this);
}

// Destructor
MatchingEngine::~MatchingEngine()
{
    running = false;

    // Wake up consumer thread if it is waiting
    orderQueue.push(Order(-1, Side::BUY, 0, 0));

    if (consumerThread.joinable())
        consumerThread.join();
}

// Producer function
void MatchingEngine::submitOrder(const Order& order)
{
    orderQueue.push(order);
}

// Consumer thread
void MatchingEngine::consumer()
{
    while (running)
    {
        Order order = orderQueue.pop();

        if (!running)
            break;

        processOrder(order);
    }
}

// Process one order
void MatchingEngine::processOrder(Order order)
{
    orderBook.addOrder(order);

    matchOrders();

    orderBook.printOrderBook();
}

// Matching Logic
void MatchingEngine::matchOrders()
{
    while (!orderBook.buyBook.empty() &&
           !orderBook.sellBook.empty())
    {
        auto buyIt = orderBook.buyBook.begin();
        auto sellIt = orderBook.sellBook.begin();

        Order &buyOrder = buyIt->second.front();
        Order &sellOrder = sellIt->second.front();

        // No trade possible
        if (buyOrder.price < sellOrder.price)
            break;

        int tradeQty = min(buyOrder.quantity,
                           sellOrder.quantity);

        // Save trade
        tradeHistory.push_back(
            Trade(
                buyOrder.id,
                sellOrder.id,
                sellOrder.price,
                tradeQty
            )
        );

        // Log trade
        logger.log(
            "BUY ID = " + to_string(buyOrder.id) +
            " SELL ID = " + to_string(sellOrder.id) +
            " PRICE = " + to_string(sellOrder.price) +
            " QTY = " + to_string(tradeQty)
        );

        cout << "\nTrade Executed\n";
        cout << "Price    : " << sellOrder.price << endl;
        cout << "Quantity : " << tradeQty << endl;

        buyOrder.quantity -= tradeQty;
        sellOrder.quantity -= tradeQty;

        // Remove completed buy order
        if (buyOrder.quantity == 0)
        {
            int completedId = buyOrder.id;

            buyIt->second.pop_front();

            orderBook.orderIndex.erase(completedId);

            if (buyIt->second.empty())
                orderBook.buyBook.erase(buyIt);
        }

        // Remove completed sell order
        if (sellOrder.quantity == 0)
        {
            int completedId = sellOrder.id;

            sellIt->second.pop_front();

            orderBook.orderIndex.erase(completedId);

            if (sellIt->second.empty())
                orderBook.sellBook.erase(sellIt);
        }
    }
}

// Print Trade History
void MatchingEngine::printTradeHistory()
{
    cout << "\n========== TRADE HISTORY ==========\n";

    for (const auto &trade : tradeHistory)
    {
        cout << "Buy Order ID : " << trade.buyOrderId << endl;
        cout << "Sell Order ID: " << trade.sellOrderId << endl;
        cout << "Price        : " << trade.price << endl;
        cout << "Quantity     : " << trade.quantity << endl;
        cout << "-----------------------------" << endl;
    }
}

// Cancel Order
bool MatchingEngine::cancelOrder(int orderId)
{
    return orderBook.cancelOrder(orderId);
}

// Modify Order
bool MatchingEngine::modifyOrder(int orderId,
                                 int newPrice,
                                 int newQty)
{
    auto it = orderBook.orderIndex.find(orderId);

    if (it == orderBook.orderIndex.end())
        return false;

    OrderLocation loc = it->second;

    deque<Order>* orders;

    if (loc.side == Side::BUY)
        orders = &orderBook.buyBook[loc.price];
    else
        orders = &orderBook.sellBook[loc.price];

    for (auto &order : *orders)
    {
        if (order.id == orderId)
        {
            Side side = order.side;

            cancelOrder(orderId);

            submitOrder(
                Order(
                    orderId,
                    side,
                    newPrice,
                    newQty
                )
            );

            return true;
        }
    }

    return false;
}