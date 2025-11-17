#ifndef ORDER_H
#define ORDER_H

#include <ctime>

enum class OrderType { BUY, SELL };

struct Order {
    int id;                 // Unique Order ID
    OrderType type;         // BUY or SELL
    double price;           // Limit price
    int quantity;           // Number of shares
    long long timestamp;    // Time priority (FIFO)

    Order(int id, OrderType type, double price, int quantity) 
        : id(id), type(type), price(price), quantity(quantity) {
        timestamp = std::time(nullptr); // Set current time
    }
};

#endif // ORDER_H