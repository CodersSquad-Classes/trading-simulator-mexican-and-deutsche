#ifndef ORDER_H
#define ORDER_H

#include <ctime>
#include <string>

enum class OrderType {
    BUY,
    SELL
};

struct Order {
    int id;                 
    OrderType type;         
    double price;           
    int quantity;           
    long long timestamp;    

    Order(int id, OrderType type, double price, int quantity) 
        : id(id), type(type), price(price), quantity(quantity) {
        timestamp = std::time(nullptr); 
    }
};

#endif // ORDER_H