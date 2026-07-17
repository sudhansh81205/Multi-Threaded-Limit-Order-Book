#include <iostream>
#include "OrderBook.h"

using namespace std ;
void OrderBook::printOrderBook(){
    cout << "\n===== ORDER BOOK =====\n";

    cout << "\nSELL ORDERS\n";

    for (auto &level : sellBook)
    {
        cout << "Price: " << level.first << " -> ";

        for (auto &order : level.second)
        {  cout << "[ID:" << order.id
                << " Qty:" << order.quantity << "] ";
        }

        cout << endl;
    }

    cout << "\nBUY ORDERS\n";

    for (auto &level : buyBook)
    {
        cout << "Price: " << level.first << " -> ";

        for (auto &order : level.second)
        {
            cout << "[ID:" << order.id
                 << " Qty:" << order.quantity << "] ";
        }

        cout << endl;
    }

    cout << "=========\n";
}

void OrderBook::addOrder(const Order& order)
{
    if(order.side == Side::BUY)
        buyBook[order.price].push_back(order);
    else
        sellBook[order.price].push_back(order);

    orderIndex[order.id] = {order.side, order.price};
}

bool OrderBook::cancelOrder(int orderId){
    // Check if order exists
    auto it = orderIndex.find(orderId);
    if(it == orderIndex.end())
        return false;

    OrderLocation location = it->second;

    if(location.side == Side::BUY){
        auto &orders = buyBook[location.price];

        for(auto itr = orders.begin(); itr != orders.end(); itr++) {
            if(itr->id == orderId){
                orders.erase(itr);
                if(orders.empty())
                    buyBook.erase(location.price);

                orderIndex.erase(orderId);

                return true;
            }
        }
    }
    else {
        auto &orders = sellBook[location.price];

        for(auto itr = orders.begin(); itr != orders.end(); itr++){
            if(itr->id == orderId){
                orders.erase(itr);

                if(orders.empty())
                    sellBook.erase(location.price);

                orderIndex.erase(orderId);

                return true;
            }
        }
    }

    return false;
}
