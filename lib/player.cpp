#include "../include/player.h"
#include "../include/utils.h"
#include <iostream>
#include <iomanip>  // for setw

void Player::showCards() {
    std::cout << "\n" << getName() << "'s hand:\n";
    
    // Print first row of both cards (top border)
    std::string color1 = (hand[0] / 13 <= 1) ? RED : WHITE;
    std::string color2 = (hand[1] / 13 <= 1) ? RED : WHITE;
    std::cout << color1 << "┌─────┐ " << color2 << "┌─────┐\n";
    
    // Print second row (rank and suit)
    std::string suits[] = { "♥", "♦", "♣", "♠" };
    std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    
    std::cout << color1 << "│" << std::left << std::setw(2) << ranks[hand[0] % 13] << "   │ "
              << color2 << "│" << std::left << std::setw(2) << ranks[hand[1] % 13] << "   │\n";
    
    // Print third row (center suit)
    std::cout << color1 << "│  " << suits[hand[0] / 13] << "  │ "
              << color2 << "│  " << suits[hand[1] / 13] << "  │\n";
    
    // Print fourth row (rank and suit at bottom)
    std::cout << color1 << "│   " << std::right << std::setw(2) << ranks[hand[0] % 13] << "│ "
              << color2 << "│   " << std::right << std::setw(2) << ranks[hand[1] % 13] << "│\n";
    
    // Print fifth row (bottom border)
    std::cout << color1 << "└─────┘ " << color2 << "└─────┘" << RESET << "\n";
}

int Player::getHandValue() const {
    int value = 0;
    int aces = 0;
    
    for (int card : hand) {
        int rank = card % 13;
        
        if (rank == 12) {  
            aces++;
            value += 1;  
        } else if (rank < 9) {  
            value += rank + 2;  
        } else {  
            value += 10;
        }
    }
    
    for (int i = 0; i < aces; ++i) {
        if (value + 10 <= 21) {
            value += 10;
        }
    }
    
    return value;
}