[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/yqZxj4OI)
# Stock Exchange Matching Engine

Traders continuously post bids to buy or sell stock. A limit order means that a buyer (seller) places an order to buy (sell) a specified amount of a given stock at or below (at or above) a given price. The order book displays buy and sell orders, and ranks them by price and then by time. Matching engine matches compatible buyers and sellers; if there are multiple possible buyers, break ties by choosing the buyer that placed the bid earliest. Use two priority queues for each stock, one for buyers and one for sellers.

A continuous limit order book (CLOB) is a trading system used by exchanges to match buy and sell orders based on both price and time priority, ensuring a transparent and real-time market. It operates as a central, dynamic list of all open orders, with bids on one side and asks on the other, continuously updated as new orders are added or existing ones are executed or canceled. CLOBs provide transparency into market depth and facilitate fair pricing by allowing traders to see and compete for the best available prices.

On this challenge, you're implementing a Continuos Limit Order Book (CLOB). Buyers and sellers will be **dynamically** created and then displayed in a **real-time dashboard**. Consider that your implementation should look **as realist as possible** (you can use colors). You are free to choose the number of rows to display. Take a look in the following [document](https://faculty.haas.berkeley.edu/hender/ITpro.pdf), the Island's limit order book can be a good example of what is expected, but in terminal.


## How to build and run

### Linux / macOS / WSL
1. Compile: `g++ -std=c++11 main.cpp MatchingEngine.cpp Display.cpp -o market`
2. Run: `./market`

### Windows (MinGW)
1. Compile: `g++ -std=c++11 main.cpp MatchingEngine.cpp Display.cpp -o market.exe`
2. Run: `market.exe`


## Deliverables

- Source code must be implemented in `*.cpp` and `*.h` files
- Instructions at [How to build and run](#how-to-build-and-run) section
- [DOCS.md](./DOCS.md)
    - Introduction
    - Research on stocks exchange 
    - Software Design and Implementation (diagrams, charts, key functions, code snippets, etc)
    - Conclusions and Learnings (one per teammate)

## Introduction

The project simulates a real-time **Continuous Limit Order Book (CLOB)**, where buy and sell orders are matched based on price and time priority.

Inspired by the classic **Island ECN** interface, the application features a fully functional **Terminal-based UI** that visualizes market depth, trade execution, and volume in real-time. Under the hood, the engine utilizes efficient **Priority Queues** (Min-Heap and Max-Heap) to ensure fast order processing ($O(\log n)$) and correct First-In-First-Out (FIFO) handling for time priority.

## Research on Stock Exchange

Modern financial markets have shifted from physical trading floors to **Electronic Communications Networks (ECNs)**, such as the Island ECN. The core mechanism driving these systems is the **Continuous Limit Order Book (CLOB)**, which maintains a real-time list of outstanding Buy (Bid) and Sell (Ask) orders.

To ensure fair execution, the matching engine operates on a strict **Price-Time Priority** basis:
1.  **Price Priority:** The "best" price always wins (highest Bid and lowest Ask).
2.  **Time Priority:** If multiple orders exist at the same price, the order that arrived earliest is executed first (FIFO).

## Software Design and Implementation

The program is built on a modular, header-driven C++ architecture that ensures a separation between data management, trade execution logic, and visualization. At the core of the system, the OrderBook uses two distinct std::priority_queue instances to efficiently manage liquidity, we chose them for their ability to handle order insertions in logarithmic time ($O(\log n)$) and provide constant time ($O(1)$) access to the best available prices. Custom comparator structs enforce the strict Price-Time priority rules: a Max-Heap is used for the Buy side to prioritize the highest bids, while a Min-Heap manages the Sell side to prioritize the lowest asks, with both implementing a secondary "First-In-First-Out" (FIFO) logic to resolve price ties based on order timestamps. The MatchingEngine acts as the central processor, continuously evaluating the top of these queues, whenever a Bid price meets or exceeds an Ask price, a trade is executed, and any remaining quantity from partially filled orders is re-inserted into the book while strictly preserving its original timestamp to maintain market fairness. Finally, the user interface is implemented as a high-performance Real-Time Terminal UI using ANSI escape for color-coding (green for bids, red for asks) and cursor positioning, effectively simulating a professional trading dashboard like the Island ECN without using external graphical libraries.

## Conclusions and Learning - Julius

This project demonstrated the critical role of data structure selection in complex systems. Implementing a Continuous Limit Order Book (CLOB) revealed that simple arrays or vectors are insufficient for real-time trading due to sorting overhead. By utilizing Priority Queues (Heaps), we achieved the necessary $O(1)$ access time for the best bid and ask prices, ensuring the matching engine operates efficiently even under load. The project provided deep insight into market strcuture. By translating the theoretical concept of Price-Time Priority into C++ code highlighted the complexity of edge cases, particularly "Partial Fills", thus ensuring that remaining order quantities retain their original priority timestamp was a key implementation challenge. Building the Terminal UI proved that a functional, professional-looking dashboard can be created without heavy graphical libraries. Showing The capabilities of the Terminal are not as limited as they might seem.

## Conclusions and Learning - Don Calderon


## Grading Policy

| Rubric                           | Points |
|----------------------------------|--------|
| Use of Priority Queues           |   40   |
| Terminal-based real-time UI      |   30   |
| Documentation                    |   30   |
| Total                            |   100  |
