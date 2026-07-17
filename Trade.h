#ifndef TRADE_H
#define TRADE_H

class Trade
{
public:
    int buyOrderId;
    int sellOrderId;
    int price;
    int quantity;

    Trade(int buyId, int sellId, int p, int q)
    {
        buyOrderId = buyId;
        sellOrderId = sellId;
        price = p;
        quantity = q;
    }
};

#endif