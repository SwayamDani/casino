#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
#include <limits>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>
#include "../include/utils.h"
#include "../include/player.h"

using namespace std;

// Symbol configuration structure
struct Symbol {
    string name;
    string display;
    int color;
    int weight;
    int payout3;
    int payout2;
};

class SlotMachine {
private:
    vector<Symbol> symbols;
    vector<string> weightedSymbols;
    int jackpotAmount;
    
    void createWeightedSymbols() {
        weightedSymbols.clear();
        for (const auto& symbol : symbols) {
            for (int i = 0; i < symbol.weight; i++) {
                weightedSymbols.push_back(symbol.name);
            }
        }
    }

public:
    SlotMachine(int initialJackpot = 1000) : jackpotAmount(initialJackpot) {
        // Initialize symbol configurations with improved displays
        symbols = {
            {"CHERRY", "🍒", 0, 5, 10, 2},      // Red
            {"LEMON",  "🍋", 2, 5, 15, 2},      // Yellow
            {"BELL",   "🔔", 2, 4, 20, 5},      // Yellow
            {"STAR",   "⭐", 2, 3, 20, 5},      // Yellow
            {"SEVEN",  "7️⃣ ", 4, 2, 50, 5},      // Magenta
            {"BAR",    "💎", 5, 1, 100, 10}     // Cyan
        };
        createWeightedSymbols();
    }
    
    int getJackpot() const {
        return jackpotAmount;
    }
    
    void increaseJackpot(int amount) {
        jackpotAmount += amount;
    }

    string getSymbolDisplay(const string& symbol) {
        for (const auto& config : symbols) {
            if (config.name == symbol) return config.display;
        }
        return "?";
    }

    int colorForSymbol(const string& symbol) {
        for (const auto& config : symbols) {
            if (config.name == symbol) return config.color;
        }
        return 5; // Default to cyan
    }

    void displaySlotMachine(const vector<string>& reels, Player* player) {
        clearScreen();
        
        // Slot machine top
        cout << CYAN << "       _\\ " << YELLOW << "███" << CYAN << " /_" << RESET << endl;
        cout << CYAN << "        / " << YELLOW << "███" << CYAN << " \\" << RESET << endl;
        cout << CYAN << "  ┌───────┴─┴───────┐" << RESET << endl;
        cout << CYAN << "  │  " << RED << BOLD << "J A C K P O T" << RESET << CYAN << "  │" << RESET << endl;
        cout << CYAN << "  ├─────────────────┤┌───┐" << RESET << endl;
        cout << CYAN << "  │   ┌──┬──┬──┐    ││   │" << RESET << endl;
        cout << CYAN << "  │   │  │  │  │    │└┬─┬┘" << RESET << endl;
        cout << CYAN << "  │   ├──┼──┼──┤    │ │ │" << RESET << endl;
        cout << CYAN << "  │ ► │";
        
        // Display reels with proper colors
        if (reels.size() > 0) {
            cout << getColorCode(colorForSymbol(reels[0]));
            cout << getSymbolDisplay(reels[0]);
            cout << RESET << CYAN;
        } else {
            cout << "  ";
        }
        
        cout << "│";
        
        if (reels.size() > 1) {
            cout << getColorCode(colorForSymbol(reels[1]));
            cout << getSymbolDisplay(reels[1]) ;
            cout << RESET << CYAN;
        } else {
            cout << "  ";
        }
        
        cout << "│";
        
        if (reels.size() > 2) {
            cout << getColorCode(colorForSymbol(reels[2]));
            cout << getSymbolDisplay(reels[2]) ;
            cout << RESET << CYAN;
        } else {
            cout << "  ";
        }
        
        cout << "│ ◄  │ │ │" << RESET << endl;
        cout << CYAN << "  │   ├──┼──┼──┤    ├┐│ │" << RESET << endl;
        cout << CYAN << "  │   │  │  │  │    │├┘ │" << RESET << endl;
        cout << CYAN << "  │   └──┴──┴──┘ ┌┐ │├──┘" << RESET << endl;
        cout << CYAN << "  │    " << YELLOW << "◌  ◌  ◌" << CYAN << "   ││ ├┘" << RESET << endl;
        cout << CYAN << "  │              └┘ │" << RESET << endl;
        cout << CYAN << "  ├─────────────────┤" << RESET << endl;
        cout << CYAN << "  │ ┌─────────────┐ │" << RESET << endl;
        cout << CYAN << "  │ │ " << GREEN << "Insert Coin" << CYAN << " │ │" << RESET << endl;
        cout << CYAN << "  │ └─────────────┘ │" << RESET << endl;
        cout << CYAN << "  ├─────────────────┤" << RESET << endl;
        cout << CYAN << "  │      ┌───┐      │" << RESET << endl;
        cout << CYAN << "┌─┴──────┘" << WHITE << "---" << CYAN << "└──────┴─┐" << RESET << endl;
        cout << CYAN << "│ " << YELLOW << "Coins: " << WHITE << setw(12) << setfill('0') << player->getBank() << CYAN << " │" << RESET << endl;
        cout << CYAN << "└─────────────────────┘" << RESET << endl;
        
        // Display jackpot amount and player info separately
        cout << endl;
        cout << YELLOW << "═════════════════════════════════════" << RESET << endl;
        cout << WHITE << " Player: " << player->getName() << endl;
        cout << WHITE << " Jackpot: " << RED << formatMoney(jackpotAmount) << RESET << endl;
        cout << YELLOW << "═════════════════════════════════════" << RESET << endl;
        
        // Payout table
        cout << endl << YELLOW << BOLD << "PAYOUT TABLE:" << RESET << endl;
        for (const auto& symbol : symbols) {
            cout << getColorCode(symbol.color) << symbol.display << " " << WHITE 
                 << symbol.name << ": " << YELLOW << "x3=" << symbol.payout3 << "x" 
                 << WHITE << ", " << YELLOW << "x2=" << symbol.payout2 << "x" << RESET << endl;
        }
    }
    
    void displayWinLine(const vector<string>& reels, int winnings) {
        cout << endl;
        cout << WHITE << "┌─────────────────────────────────┐" << endl;
        
        if (winnings > 0) {
            cout << GREEN << "│ 🎉 WINNER! You won " << formatMoney(winnings) << "!" << string(max(0, 11 - static_cast<int>(to_string(winnings).length())), ' ') << "│" << endl;
            
            // Find which symbols matched
            unordered_map<string, int> counts;
            for (const auto& reel : reels) {
                counts[reel]++;
            }
            
            string matchedSymbol;
            int matchCount = 0;
            
            for (const auto& pair : counts) {
                if (pair.second >= 2 && pair.second > matchCount) {
                    matchedSymbol = pair.first;
                    matchCount = pair.second;
                }
            }
            
            if (!matchedSymbol.empty()) {
                cout << YELLOW << "│ Matched " << matchCount << "x ";
                cout << getColorCode(colorForSymbol(matchedSymbol)) << getSymbolDisplay(matchedSymbol);
                cout << YELLOW << " symbols!" << string(max(0, 11 - static_cast<int>(to_string(matchCount).length())), ' ') << "│" << endl;
            }
        } else {
            cout << RED << "│ No win this time. Try again!" << string(5, ' ') << "│" << endl;
        }
        
        cout << WHITE << "└─────────────────────────────────┘" << endl;
    }

    void spinAnimation(vector<string>& reels, Player* player) {
        // Initialize reels if empty
        if (reels.empty()) {
            reels = vector<string>(3, "");
        }
        
        // Visual spinning effect with sound
        for (int i = 0; i < 15; ++i) {
            reels[0] = weightedSymbols[rand() % weightedSymbols.size()];
            reels[1] = weightedSymbols[rand() % weightedSymbols.size()];
            reels[2] = weightedSymbols[rand() % weightedSymbols.size()];
            
            displaySlotMachine(reels, player);
            
            // Console beep on every other spin for sound effect
            if (i % 2 == 0) {
                cout << "\a" << flush;
            }
            
            // Gradually slow down the spinning
            this_thread::sleep_for(chrono::milliseconds(100 + i * 20));
        }
    }

    int calculateWinnings(const vector<string>& reels, int bet) {
        if (reels.size() < 3) return 0;
        
        unordered_map<string, int> counts;
        for (const auto& reel : reels) {
            counts[reel]++;
        }

        // Check for three-of-a-kind (jackpot for three BAR symbols)
        for (const auto& symbol : symbols) {
            if (counts[symbol.name] == 3) {
                if (symbol.name == "BAR") {
                    return jackpotAmount; // Return the entire jackpot
                }
                return bet * symbol.payout3;
            }
        }

        // Check for two-of-a-kind
        for (const auto& symbol : symbols) {
            if (counts[symbol.name] == 2) {
                return bet * symbol.payout2;
            }
        }

        return 0;
    }
    
    string getColorCode(int colorIndex) {
        switch (colorIndex) {
            case 0: return RED;
            case 1: return GREEN;
            case 2: return YELLOW;
            case 3: return BLUE;
            case 4: return MAGENTA;
            case 5: return CYAN;
            default: return WHITE;
        }
    }
};

// Main slot machine game function to be called from main.cpp
void runSlotMachineGame(Player* player) {
    srand(static_cast<unsigned int>(time(0)));
    SlotMachine machine;
    
    int totalSpins = 0;
    int totalWins = 0;
    vector<string> currentReels;
    
    while (player->getBank() > 0) {
        // Display initial state
        machine.displaySlotMachine(currentReels, player);
        
        // Show game stats
        cout << endl;
        cout << YELLOW << "═════════════════════════════════════" << RESET << endl;
        cout << WHITE << " Spins: " << totalSpins << " | Wins: " << totalWins;
        if (totalSpins > 0) {
            cout << " | Win Rate: " << fixed << setprecision(1) << (totalWins * 100.0 / totalSpins) << "%";
        }
        cout << RESET << endl;
        cout << YELLOW << "═════════════════════════════════════" << RESET << endl;
        
        // Get bet amount
        cout << endl << CYAN << "Enter bet (1-" << player->getBank() << "), or 0 to return to casino: " << RESET;
        
        int bet;
        getIntInput(bet);

        if (bet == 0) break;
        
        if (bet < 1 || bet > player->getBank()) {
            cout << RED << "Invalid bet! Please bet between 1 and " << player->getBank() << "." << RESET << endl;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }

        // Subtract bet from player's bank
        player->setBet(bet);
        
        // Contribution to jackpot
        machine.increaseJackpot(static_cast<int>(bet * 0.1));
        
        // Spin animation
        cout << endl << YELLOW << "🎰 Spinning the reels... Good luck! 🍀" << RESET << endl;
        machine.spinAnimation(currentReels, player);
        
        // Calculate winnings
        int winnings = machine.calculateWinnings(currentReels, bet);
        
        // Display win/loss message
        machine.displayWinLine(currentReels, winnings);
        
        if (winnings > 0) {
            // Special case for jackpot win
            if (winnings == machine.getJackpot()) {
                cout << endl;
                cout << RED << BOLD << "🎊 JACKPOT! 🎊 JACKPOT! 🎊 JACKPOT! 🎊" << RESET << endl;
                cout << YELLOW << BOLD << "You've won the entire jackpot of " << formatMoney(winnings) << "!" << RESET << endl;
                
                // Reset jackpot after win
                machine.increaseJackpot(-machine.getJackpot() + 1000);
            }
            
            player->addBank(bet + winnings); // Return original bet + winnings
            totalWins++;
        }

        totalSpins++;
        
        // Wait for user to press Enter before continuing
        cout << endl << CYAN << "Press Enter to continue..." << RESET;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // End game screen
    clearScreen();
    cout << YELLOW << BOLD;
    cout << "╔═══════════════════════════════════╗" << endl;
    cout << "║           GAME SUMMARY           ║" << endl;
    cout << "╚═══════════════════════════════════╝" << RESET << endl;
    
    cout << WHITE << "Player: " << player->getName() << endl;
    cout << "Final Balance: " << formatMoney(player->getBank()) << endl;
    cout << "Total Spins: " << totalSpins << endl;
    cout << "Total Wins: " << totalWins << endl;
    if (totalSpins > 0) {
        cout << "Win Rate: " << fixed << setprecision(1) << (totalWins * 100.0 / totalSpins) << "%" << endl;
    }
    
    cout << endl << CYAN << "Press Enter to return to the casino..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}