#include <iostream>
#include <thread>   // For sleep
#include <chrono>   // For duration
#include <cstdlib>  // For rand
#include <ctime>    // For time

#include "Order.h"
#include "OrderBook.h"
#include "MatchingEngine.h"
#include "Display.h"

// Helper to generate random double in range [min, max]
double randomDouble(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

// Helper to generate random int
int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    // 1. Setup
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random
    OrderBook book;
    MatchingEngine engine;
    std::string symbol = "MSFT";
    
    // Start price similar to the Island screenshot
    double currentMarketPrice = 24.05; 
    int orderIdCounter = 1;

    // 2. Simulation Loop
    while (true) {
        
        // --- A. TRADING BOT LOGIC (Generate Orders) ---
        
        // Randomly choose Buy (0) or Sell (1)
        OrderType type = (rand() % 2 == 0) ? OrderType::BUY : OrderType::SELL;
        
        // Generate price close to market price (+/- $0.05 spread)
        // This creates a realistic cluster of orders around the current price
        double priceOffset = randomDouble(-0.05, 0.05);
        double orderPrice = currentMarketPrice + priceOffset;
        
        // Ensure price is positive
        if (orderPrice < 0.01) orderPrice = 0.01;

        // Generate random quantity (lots of 100, e.g., 100, 500, 2000)
        int quantity = randomInt(1, 10) * 100;

        // Create and Add Order
        Order newOrder(orderIdCounter++, type, orderPrice, quantity);
        book.addOrder(newOrder);

        // --- B. MATCHING ENGINE ---
        
        // Check for matches immediately
        engine.match(book);

        // Update reference price if a trade happened (Market Trend)
        if (engine.getLastTradePrice() > 0) {
            currentMarketPrice = engine.getLastTradePrice();
        }

        // --- C. RENDER UI ---
        
        Display::draw(book, engine, symbol);
        
        // Optional: Log what the bot just did below the dashboard
        std::cout << " [BOT]: Placing " << (type == OrderType::BUY ? "BUY" : "SELL") 
                  << " Order #" << (orderIdCounter-1) 
                  << " (" << quantity << " @ " << orderPrice << ")\n";

        // --- D. GAME LOOP TIMING ---
        // Sleep for 200ms to make it readable (5 updates per second)
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}