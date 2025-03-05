#include "pokerOutput.h"
#include "../include/utils.h"
#include "iostream"
#include <thread>
#include <chrono>

void pokerOutput::showFlops(const std::vector<int>& tableCards) const {
    std::cout << BOLD << "\n=== TABLE CARDS ===" << RESET << "\n\n";
    
    // Print first line of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "┌─────────┐ " << RESET;
    }
    std::cout << "\n";
    
    // Print second line of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::string rank = ranks[tableCards[i] % 13];
        std::string padding = (rank.length() == 1) ? " " : "";
        std::cout << color << "│ " << rank << padding << "      │ " << RESET;
    }
    std::cout << "\n";
    
    // Print third line of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│         │ " << RESET;
    }
    std::cout << "\n";
    
    // Print fourth line (suit) of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│    " << suits[tableCards[i] / 13] << "    │ " << RESET;
    }
    std::cout << "\n";
    
    // Print fifth line of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│         │ " << RESET;
    }
    std::cout << "\n";
    
    // Print sixth line of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::string rank = ranks[tableCards[i] % 13];
        std::string padding = (rank.length() == 1) ? " " : "";
        std::cout << color << "│      " << padding << rank << " │ " << RESET;
    }
    std::cout << "\n";
    
    // Print last line of all cards
    for (int i = 0; i < 3; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "└─────────┘ " << RESET;
    }
    std::cout << "\n\n";
}
void pokerOutput::showTurn(const std::vector<int>& tableCards) const {
    std::cout << BOLD << "\n=== TABLE CARDS ===" << RESET << "\n\n";
    
    // Print first line of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "┌─────────┐ " << RESET;
    }
    std::cout << "\n";
    
    // Print second line of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::string rank = ranks[tableCards[i] % 13];
        std::string padding = (rank.length() == 1) ? " " : "";
        std::cout << color << "│ " << rank << padding << "      │ " << RESET;
    }
    std::cout << "\n";
    
    // Print third line of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│         │ " << RESET;
    }
    std::cout << "\n";
    
    // Print fourth line (suit) of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│    " << suits[tableCards[i] / 13] << "    │ " << RESET;
    }
    std::cout << "\n";
    
    // Print fifth line of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│         │ " << RESET;
    }
    std::cout << "\n";
    
    // Print sixth line of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::string rank = ranks[tableCards[i] % 13];
        std::string padding = (rank.length() == 1) ? " " : "";
        std::cout << color << "│      " << padding << rank << " │ " << RESET;
    }
    std::cout << "\n";
    
    // Print last line of all cards
    for (int i = 0; i < 4; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "└─────────┘ " << RESET;
    }
    std::cout << "\n\n";
}
void pokerOutput::showRiver(const std::vector<int>& tableCards) const {
    std::cout << BOLD << "\n=== TABLE CARDS ===" << RESET << "\n\n";
    
    // Print first line of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "┌─────────┐ " << RESET;
    }
    std::cout << "\n";
    
    // Print second line of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::string rank = ranks[tableCards[i] % 13];
        std::string padding = (rank.length() == 1) ? " " : "";
        std::cout << color << "│ " << rank << padding << "      │ " << RESET;
    }
    std::cout << "\n";
    
    // Print third line of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│         │ " << RESET;
    }
    std::cout << "\n";
    
    // Print fourth line (suit) of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│    " << suits[tableCards[i] / 13] << "    │ " << RESET;
    }
    std::cout << "\n";
    
    // Print fifth line of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "│         │ " << RESET;
    }
    std::cout << "\n";
    
    // Print sixth line of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::string rank = ranks[tableCards[i] % 13];
        std::string padding = (rank.length() == 1) ? " " : "";
        std::cout << color << "│      " << padding << rank << " │ " << RESET;
    }
    std::cout << "\n";
    
    // Print last line of all cards
    for (int i = 0; i < 5; i++) {
        std::string color = (tableCards[i] / 13 <= 1) ? RED : WHITE;
        std::cout << color << "└─────────┘ " << RESET;
    }
    std::cout << "\n\n\n\n";
}
void pokerOutput::showRules() const{
    clearScreen();
    std::cout << CYAN << BOLD;
    std::cout << "╔════════════════════════════════╗" << std::endl;
    std::cout << "║       Welcome to Poker!        ║" << std::endl;
    std::cout << "╚════════════════════════════════╝" << RESET << std::endl << std::endl;
    
    std::cout << YELLOW << "Press Enter to start the game..." << RESET << std::endl;
    std::cin.get();
    std::cout << MAGENTA << "╔═══════════════════════════ HOW TO PLAY ═══════════════════════════╗" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 1. Each player receives two cards                                 " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 2. Dealer places three cards face up on table (the flop)          " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 3. Players bet                                                    " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 4. Dealer places one more card (the turn)                         " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 5. Players bet again                                              " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 6. Dealer places final card (the river)                           " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 7. Final betting round                                            " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 8. Player with best hand wins the pot!                            " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "╚═══════════════════════════════════════════════════════════════════╝" << RESET << std::endl;
    std::cout << "Press Enter to continue." << std::endl;
    std::cin.get();
}
void pokerOutput::showPool(const int pool) const{
    std::cout << CYAN << "╔════════════════════════════════╗" << RESET << std::endl;
    std::cout << CYAN << "║" << RESET << " Current Pool: $" << BOLD << pool << RESET;
    std::cout << std::string(8 - std::to_string(pool).length(), ' ') << CYAN << "        ║" << RESET << std::endl;
    std::cout << CYAN << "╚════════════════════════════════╝" << RESET << std::endl << std::endl;
}
void pokerOutput::showBettingActions(const int minBet) const{
    std::cout << MAGENTA << "╔═════════════ ACTIONS ═════════════╗" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 1. Fold                           " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 2. Call ($" << minBet << ")" << std::string(23 - std::to_string(minBet).length(), ' ') << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "║" << RESET << " 3. Raise                          " << MAGENTA << "║" << RESET << std::endl;
    std::cout << MAGENTA << "╚═══════════════════════════════════╝" << RESET << std::endl;
}
void pokerOutput::countdown(const int seconds) const {
    for (int i = seconds; i > 0; --i) {
        std::cout << YELLOW << "Starting in " << BOLD << i << RESET << YELLOW << " seconds..." << RESET << "\r" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::string(40, ' ') << "\r";
}