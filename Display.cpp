#include "Display.h"
#include <iostream>
#include <iomanip>
#include <vector>

void Display::draw(OrderBook& book, const MatchingEngine& engine, const std::string& symbol) {
    // 1. Clear Terminal
    std::cout << CLEAR;

    // 2. Header Section (Island ECN Style)
    std::cout << "======================================================================\n";
    std::cout << " " << BOLD << "ISLAND CLOB" << RESET << " | SYMBOL: " << BLUE << symbol << RESET << " | STATUS: " << GREEN << "OPEN" << RESET << "\n";
    std::cout << "======================================================================\n";

    // 3. Market Status (Last Price & Volume)
    std::cout << " " << BOLD << "[LAST MATCH]" << RESET << "                 " << BOLD << "[MARKET ACTIVITY]" << RESET << "\n";
    std::cout << " Price:   " << YELLOW << "$" << std::fixed << std::setprecision(4) << engine.getLastTradePrice() << RESET 
              << "             Total Volume:   " << engine.getTotalVolume() << "\n";
    std::cout << "----------------------------------------------------------------------\n";

    // 4. Order Book Header
    std::cout << GREEN << "        BUY ORDERS (BIDS)      " << RESET << "||" << RED << "       SELL ORDERS (ASKS)      " << RESET << "\n";
    std::cout << "   SHARES  |      PRICE        ||        PRICE      |   SHARES   \n";
    std::cout << "-----------+-------------------++-------------------+------------\n";

    // 5. Render Rows
    // Need copies of vectors to iterate without popping from PriorityQueue
    std::vector<Order> buys = book.getBuyOrdersVector();
    std::vector<Order> sells = book.getSellOrdersVector();

    int maxRows = 15; // Show top 15 orders
    for (int i = 0; i < maxRows; ++i) {
        const Order* b = (i < buys.size()) ? &buys[i] : nullptr;
        const Order* s = (i < sells.size()) ? &sells[i] : nullptr;
        printOrderRow(b, s);
    }
    std::cout << "----------------------------------------------------------------------\n";
}

void Display::printOrderRow(const Order* buy, const Order* sell) {
    // Left Side (BUY)
    if (buy) {
        std::cout << std::setw(10) << buy->quantity << " | " 
                  << GREEN << "$ " << std::setw(9) << std::fixed << std::setprecision(4) << buy->price << RESET;
    } else {
        std::cout << "           |                   ";
    }

    std::cout << " || ";

    // Right Side (SELL)
    if (sell) {
        std::cout << RED << "$ " << std::setw(9) << std::fixed << std::setprecision(4) << sell->price << RESET << " | " 
                  << std::setw(10) << sell->quantity;
    } else {
        std::cout << "                   |           ";
    }
    std::cout << "\n";
}