#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <vector>
#include <queue>
#include "Order.h"

// --- COMPARATORS ---

// Buy: Higher price = Higher priority. Tie-breaker: Older time.
struct BuyComparator {
    bool operator()(const Order& a, const Order& b) {
        if (a.price != b.price) return a.price < b.price;
        return a.timestamp > b.timestamp; 
    }
};

// Sell: Lower price = Higher priority. Tie-breaker: Older time.
struct SellComparator {
    bool operator()(const Order& a, const Order& b) {
        if (a.price != b.price) return a.price > b.price; 
        return a.timestamp > b.timestamp; 
    }
};

// --- CLASS DEFINITION ---

class OrderBook {
private:
    std::priority_queue<Order, std::vector<Order>, BuyComparator> buyOrders;
    std::priority_queue<Order, std::vector<Order>, SellComparator> sellOrders;

public:
    void addOrder(const Order& order) {
        if (order.type == OrderType::BUY) buyOrders.push(order);
        else sellOrders.push(order);
    }

    bool hasBuyOrders() const { return !buyOrders.empty(); }
    bool hasSellOrders() const { return !sellOrders.empty(); }

    const Order& getBestBuy() const { return buyOrders.top(); }
    const Order& getBestSell() const { return sellOrders.top(); }

    void popBestBuy() { buyOrders.pop(); }
    void popBestSell() { sellOrders.pop(); }
    
    // Helpers for UI (returns copies)
    std::vector<Order> getBuyOrdersVector() {
        std::vector<Order> result;
        auto temp = buyOrders;
        while (!temp.empty()) { result.push_back(temp.top()); temp.pop(); }
        return result;
    }

    std::vector<Order> getSellOrdersVector() {
        std::vector<Order> result;
        auto temp = sellOrders;
        while (!temp.empty()) { result.push_back(temp.top()); temp.pop(); }
        return result;
    }
};

#endif // ORDERBOOK_H