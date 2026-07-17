#include <iostream>
#include <thread>
#include <chrono>
#include "MatchingEngine.h"
using namespace std;

int main(){

    MatchingEngine engine;

    engine.submitOrder(Order(1, Side::BUY, 105, 100));
    engine.submitOrder(Order(2, Side::BUY, 104, 50));
    engine.submitOrder(Order(3, Side::SELL, 103, 70));
    engine.submitOrder(Order(4, Side::SELL, 106, 20));
    engine.submitOrder(Order(5, Side::SELL, 105, 50));

    // Give the consumer thread time to process
    this_thread::sleep_for(chrono::seconds(1));
    engine.printTradeHistory();
    
    return 0;
}