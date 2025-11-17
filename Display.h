#ifndef DISPLAY_H
#define DISPLAY_H

#include "OrderBook.h"
#include "MatchingEngine.h"
#include <string>

// ANSI Color Codes
const std::string RESET   = "\033[0m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string BOLD    = "\033[1m";
const std::string CLEAR   = "\033[2J\033[1;1H"; // Clear screen & move cursor top-left

class Display {
public:
    // Draws the complete dashboard
    static void draw(OrderBook& book, const MatchingEngine& engine, const std::string& symbol);
    
private:
    // Helper to print a single line of the order book
    static void printOrderRow(const Order* buy, const Order* sell);
};

#endif // DISPLAY_H