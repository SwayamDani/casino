#include "../include/utils.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

const char* RESET   = "\033[0m";
const char* BLACK   = "\033[30m";
const char* RED     = "\033[31m";
const char* GREEN   = "\033[32m";
const char* YELLOW  = "\033[33m";
const char* BLUE    = "\033[34m";
const char* MAGENTA = "\033[35m";
const char* CYAN    = "\033[36m";
const char* WHITE   = "\033[37m";
const char* BOLD    = "\033[1m"; 

std::string formatMoney(int amount) {
    std::string str = std::to_string(amount);
    int len = str.length();
    for (int i = len - 3; i > 0; i -= 3) {
        str.insert(i, ",");
    }
    return "$" + str;
}

std::string centerText(const std::string& text, int width) {
    int padding = width - text.length();
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    return std::string(leftPad, ' ') + text + std::string(rightPad, ' ');
}

void getIntInput(int& input) {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (ss >> input && ss.eof()) {
            return;
        } else {
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
    }
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void printCardFormatted(int card) {
    std::string suits[] = { "♥", "♦", "♣", "♠" };
    std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    std::string color = (card / 13 <= 1) ? RED : WHITE;
    
    std::string rank = ranks[card % 13];
    std::string suit = suits[card / 13];
    std::string rankPadding = (rank.length() == 1) ? " " : "";
    
    std::cout << color;
    std::cout << "┌─────────┐\n";
    std::cout << "│ " << rank << rankPadding << "      │\n";
    std::cout << "│         │\n";
    std::cout << "│    " << suit << "    │\n";
    std::cout << "│         │\n";
    std::cout << "│      " << rankPadding << rank << " │\n";
    std::cout << "└─────────┘" << RESET;
}

void printCard(int card) {
    printCardFormatted(card);
    std::cout << " ";
}