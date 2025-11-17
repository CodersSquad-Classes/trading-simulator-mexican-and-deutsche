#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include <queue>
#include <iostream>
#include "order.h"

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) {
        if (a.price != b.price) {
            return a.price < b.price; 
        }
        return a.timestamp > b.timestamp; 
    }
};

struct SellComparator {
    bool operator()(const Order& a, const Order& b) {
        if (a.price != b.price) {
            return a.price > b.price; 
        }
        return a.timestamp > b.timestamp; 
    }
};

// --- ORDER BOOK KLASSE ---

class OrderBook {
private:
    std::priority_queue<Order, std::vector<Order>, BuyComparator> buyOrders;
    std::priority_queue<Order, std::vector<Order>, SellComparator> sellOrders;

public:
    void addOrder(const Order& order) {
        if (order.type == OrderType::BUY) {
            buyOrders.push(order);
        } else {
            sellOrders.push(order);
        }
    }

    bool hasBuyOrders() const { return !buyOrders.empty(); }
    bool hasSellOrders() const { return !sellOrders.empty(); }

    const Order& getBestBuy() const {
        return buyOrders.top();
    }

    const Order& getBestSell() const {
        return sellOrders.top();
    }

    void popBestBuy() { buyOrders.pop(); }
    void popBestSell() { sellOrders.pop(); }
    
    std::vector<Order> getBuyOrdersVector() {
        std::vector<Order> result;
        auto tempQueue = buyOrders; // Kopie erstellen
        while (!tempQueue.empty()) {
            result.push_back(tempQueue.top());
            tempQueue.pop();
        }
        return result;
    }

    std::vector<Order> getSellOrdersVector() {
        std::vector<Order> result;
        auto tempQueue = sellOrders; // Kopie erstellen
        while (!tempQueue.empty()) {
            result.push_back(tempQueue.top());
            tempQueue.pop();
        }
        return result;
    }
};

#endif 