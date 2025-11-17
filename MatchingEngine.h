#ifndef MATCHINGENGINE_H
#define MATCHINGENGINE_H

#include "OrderBook.h"
#include <vector>  
#include <ctime>   

struct Trade {
    double price;
    int quantity;
    long long timestamp;
};

class MatchingEngine {
private:
    std::vector<Trade> tradeHistory;
    long long totalVolume;

public:
    MatchingEngine();
    void match(OrderBook& orderBook);

    const std::vector<Trade>& getTradeHistory() const;
    double getLastTradePrice() const;
    long long getTotalVolume() const;
};

#endif // MATCHINGENGINE_H