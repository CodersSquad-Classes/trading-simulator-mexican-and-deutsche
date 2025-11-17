#include "MatchingEngine.h"
#include <algorithm> // für std::min
#include <ctime>

MatchingEngine::MatchingEngine() : totalVolume(0) {}

void MatchingEngine::match(OrderBook& orderBook) {
    while (orderBook.hasBuyOrders() && orderBook.hasSellOrders()) {
        // Inspect top orders
        Order bestBuy = orderBook.getBestBuy();
        Order bestSell = orderBook.getBestSell();

        // Check if trade is possible (Bid >= Ask)
        if (bestBuy.price >= bestSell.price) {
            
            // Execute Trade
            int matchQuantity = std::min(bestBuy.quantity, bestSell.quantity);
            // Determine price (simple logic: use buyer's price if older, else seller's)
            double tradePrice = (bestBuy.timestamp < bestSell.timestamp) ? bestBuy.price : bestSell.price;

            // Remove from queues
            orderBook.popBestBuy();
            orderBook.popBestSell();

            // Update Stats
            tradeHistory.push_back({tradePrice, matchQuantity, std::time(nullptr)});
            totalVolume += matchQuantity;

            // Handle Partial Fills (Push remainder back to queue)
            if (bestBuy.quantity > matchQuantity) {
                bestBuy.quantity -= matchQuantity;
                orderBook.addOrder(bestBuy); // Timestamp preserved!
            }

            if (bestSell.quantity > matchQuantity) {
                bestSell.quantity -= matchQuantity;
                orderBook.addOrder(bestSell); // Timestamp preserved!
            }

        } else {
            // No overlap, stop matching
            break;
        }
    }
}

const std::vector<Trade>& MatchingEngine::getTradeHistory() const {
    return tradeHistory;
}

double MatchingEngine::getLastTradePrice() const {
    if (tradeHistory.empty()) return 0.0;
    return tradeHistory.back().price;
}

long long MatchingEngine::getTotalVolume() const {
    return totalVolume;
}