#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include "include/utils.h"
#include "include/player.h"
#include "poker/pokerGame.h"
#include "blackjack/blackjack.h"
#include "roulette/roulette.h"
#include "slot/slotMachine.h"

void slowPrint(const std::string& str, int delay = 30) {
    for (char c : str) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    std::cout << std::endl;
}

void displayWelcomeBanner() {
    std::cout << BOLD << RED;
    std::cout << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║     🎰 Welcome to the C++ Casino & Entertainment House 🎲     ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝
    )" << RESET << std::endl;
    
    std::cout << YELLOW;
    slowPrint("            Where Fortune Favors the Bold!");
    std::cout << RESET;
    std::cout << "\n";
}

void displayGameMenu() {
    std::cout << BLUE << BOLD << "\n=== Available Games ===" << RESET << "\n\n";
    std::cout << CYAN << "1. 🎲 Poker (Minimum 2 players required)\n";
    std::cout << "2. 🎯 Roulette\n";
    std::cout << "3. 🃏 Blackjack\n";
    std::cout << "4. 🎰 Slot Machine\n";
    std::cout << "5. 💰 Visit Bank\n";
    std::cout << "6. 🚪 Exit Casino\n" << RESET;
}

int buyChips() {
    int amount;
    std::cout << YELLOW << "\n💰 Welcome to the Casino Bank!" << RESET << std::endl;
    std::cout << "How many chips would you like to buy? $";
    getIntInput(amount);
    std::cout << GREEN << "Successfully purchased $" << amount << " in chips!" << RESET << std::endl;
    return amount;
}

std::vector<Player*> registerPlayers() {
    std::vector<Player*> players;
    int numPlayers;
    
    std::cout << CYAN << "\nHow many players are joining today? " << RESET;
    while (!(std::cin >> numPlayers) || numPlayers <= 0) {
        std::cout << RED << "Please enter a valid number of players: " << RESET;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore();

    for (int i = 0; i < numPlayers; i++) {
        std::string name;
        std::cout << YELLOW << "\nPlayer " << (i + 1) << ", please enter your name: " << RESET;
        std::getline(std::cin, name);
        
        std::cout << MAGENTA << "\nWelcome, " << name << "! Let's get you some chips." << RESET << std::endl;
        int chips = buyChips();
        
        players.push_back(new Player(name, chips));
    }
    
    return players;
}

int main() {
    system("clear"); // or system("cls") for Windows
    displayWelcomeBanner();
    
    std::vector<Player*> players = registerPlayers();
    
    bool running = true;
    while (running) {
        displayGameMenu();
        
        int choice;
        std::cout << CYAN << "\nPlease select an option (1-6): " << RESET;
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Poker
                if (players.size() < 2) {
                    std::cout << RED << "\n⚠️  Poker requires at least 2 players!" << RESET << std::endl;
                    std::cout << "Please invite more players to play poker.\n";
                } else {
                    pokerGame game(players);
                }
                break;
            }
            case 2: {
                std::cout << CYAN << "\nWhich player wants to play Roulette?" << RESET << std::endl;
                for (size_t i = 0; i < players.size(); i++) {
                    std::cout << "  " << (i + 1) << ". " << players[i]->getName() 
                             << " (Balance: " << formatMoney(players[i]->getBank()) << ")\n";
                }
                
                int playerChoice;
                std::cout << YELLOW << "\nSelect player (1-" << players.size() << "): " << RESET;
                getIntInput(playerChoice);
                
                if (playerChoice > 0 && playerChoice <= players.size()) {
                    // Create and play the roulette game with this player
                    roulette game(players[playerChoice - 1]);
                    game.play();
                }
                else {
                    std::cout << RED << "Invalid player selection!" << RESET << std::endl;
                }
                break;
            case 3: // Blackjack
                if (players.size() < 1) {
                    std::cout << RED << "\n⚠️  Blackjack requires at least 1 player!" << RESET << std::endl;
                    std::cout << "Please register a player to play blackjack.\n";
                }
                else{
                    Blackjack game(players);
                }
                break;
            }
            case 4: {
                if (players.size() < 1) {
                    std::cout << RED << "\n⚠️  You need at least one player to play Slot Machine!" << RESET << std::endl;
                } else {
                    std::cout << "\nWhich player wants to try the Slot Machine?\n";
                    for (size_t i = 0; i < players.size(); i++) {
                        std::cout << (i + 1) << ". " << players[i]->getName() 
                                << " (Current balance: " << formatMoney(players[i]->getBank()) << ")\n";
                    }
                    
                    int playerChoice;
                    std::cout << CYAN << "\nSelect player (1-" << players.size() << "): " << RESET;
                    getIntInput(playerChoice);
                    
                    if (playerChoice > 0 && playerChoice <= players.size()) {
                        runSlotMachineGame(players[playerChoice - 1]);
                    } else {
                        std::cout << RED << "\n⚠️  Invalid player selection!" << RESET << std::endl;
                    }
                }
                break;
            }
            case 5: { // Visit Bank
                std::cout << "\nWhich player is visiting the bank?\n";
                for (size_t i = 0; i < players.size(); i++) {
                    std::cout << (i + 1) << ". " << players[i]->getName() 
                             << " (Current balance: $" << players[i]->getBank() << ")\n";
                }
                int playerChoice;
                std::cin >> playerChoice;
                if (playerChoice > 0 && playerChoice <= players.size()) {
                    int newChips = buyChips();
                    players[playerChoice - 1]->addBank(newChips);
                }
                break;
            }
            case 6: {
                std::cout << MAGENTA << "\nThank you for visiting C++ Casino! 👋\n";
                std::cout << "Hope to see you again soon!" << RESET << std::endl;
                running = false;
                break;
            }
            default:
                std::cout << RED << "\n⚠️  Invalid option! Please try again." << RESET << std::endl;
        }
        
        if (running) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        system("clear"); // or system("cls") for Windows
    }
    
    // Cleanup
    for (auto player : players) {
        delete player;
    }
    
    return 0;
} 