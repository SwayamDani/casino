#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "../blackjack/blackjack.h"
#include "../include/player.h"
#include "../include/dealer.h"
#include "../include/utils.h"

void Blackjack::printCards(const std::vector<int>& hand) {
    std::string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    
    for (int i = 0; i < hand.size(); ++i) {
        int card = hand[i];
        if (card < 0 || card >= 52) {
            std::cout << RED << "[Invalid Card]" << RESET;
        } else {
            // Assign colors to suits
            const char* color = RESET;
            if (card / 13 == 0) color = RED;    // Hearts
            if (card / 13 == 1) color = RED;    // Diamonds
            if (card / 13 == 2) color = BLUE;   // Clubs
            if (card / 13 == 3) color = BLUE;   // Spades
            
            std::cout << color << ranks[card % 13] << " of " << suits[card / 13] << RESET;
        }
        
        if (i < hand.size() - 1) {
            std::cout << ", ";
        }
    }
}

// Handle player betting before the game starts
void Blackjack::handleBetting(std::vector<Player*>& players) {
    for (Player* player : players) {
        std::cout << "\n" << BOLD << YELLOW << "══════ " << player->getName() << "'s betting ══════" << RESET << std::endl;
        std::cout << "Current balance: " << GREEN << "$" << player->getBank() << RESET << std::endl;
        
        // Skip players with no money
        if (player->getBank() <= 0) {
            std::cout << RED << "Sorry, you don't have any money left to bet!" << RESET << std::endl;
            continue;
        }
        
        int bet = 0;
        bool validBet = false;
        
        while (!validBet) {
            std::cout << "Enter your bet amount (minimum: $1): $";
            getIntInput(bet);
            
            if (bet <= 0) {
                std::cout << RED << "Invalid bet. Bet must be at least $1." << RESET << std::endl;
            }
            else if (!player->correctBet(bet)) {
                std::cout << RED << "You don't have enough money for that bet!" << RESET << std::endl;
            }
            else {
                validBet = true;
                player->setBet(bet);
                std::cout << GREEN << "Bet placed: $" << bet << RESET << std::endl;
            }
        }
    }
}

// Process winnings after the game
void Blackjack::processWinnings(std::vector<Player*>& players, Player* dealerPlayer) {
    bool dealerBusted = dealerPlayer->getHandValue() > 21;
    
    for (Player* player : players) {
        int bet = player->getBet();
        
        // Process results and update banks
        if (player->getHandValue() > 21) {
            // Player busted - bet is lost (already deducted)
            std::cout << player->getName() << " lost $" << bet << std::endl;
        }
        else if (dealerBusted) {
            // Dealer busted - player wins
            int winnings = bet * 2;  // Return original bet + winnings
            player->addBank(winnings);
            std::cout << GREEN << player->getName() << " wins $" << bet 
                      << "! New balance: $" << player->getBank() << RESET << std::endl;
        }
        else if (player->getHandValue() > dealerPlayer->getHandValue()) {
            // Player has higher hand - player wins
            int winnings = bet * 2;  // Return original bet + winnings
            player->addBank(winnings);
            std::cout << GREEN << player->getName() << " wins $" << bet 
                      << "! New balance: $" << player->getBank() << RESET << std::endl;
        }
        else if (player->getHandValue() < dealerPlayer->getHandValue()) {
            // Dealer has higher hand - player loses (bet already deducted)
            std::cout << RED << player->getName() << " lost $" << bet 
                      << ". New balance: $" << player->getBank() << RESET << std::endl;
        }
        else {
            // Push (tie) - return bet
            player->addBank(bet);
            std::cout << YELLOW << player->getName() << "'s bet of $" << bet 
                      << " is returned. Balance: $" << player->getBank() << RESET << std::endl;
        }
        
        // Check if player is out of money
        if (player->getBank() <= 0) {
            std::cout << RED << BOLD << player->getName() << " is out of money!" << RESET << std::endl;
        }
        
        // Clear bet for next round
        player->clearBet();
    }
}

void Blackjack::playGame(std::vector<Player*>& players) {
    dealer deck;
    
    // Create dealer and add to players at beginning
    Player* dealerPlayer = new Player("Dealer", 0);
    
    // Clear existing hands
    for (Player* player : players) {
        player->clearHand();
    }
    dealerPlayer->clearHand();
    
    clearScreen();
    std::cout << BOLD << CYAN << "\n╔═══════════════════════════════════════╗" << std::endl;
    std::cout << "║        BLACKJACK GAME STARTED        ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════╝\n" << RESET << std::endl;
    
    // Handle betting phase
    handleBetting(players);
    
    // Deal initial cards
    dealerPlayer->receiveCard(deck.drawCard());
    dealerPlayer->receiveCard(deck.drawCard());
    
    for (Player* player : players) {
        player->receiveCard(deck.drawCard());
        player->receiveCard(deck.drawCard());
    }
    
    // Show dealer's first card only
    std::cout << BOLD << "Dealer's hand: " << RESET;
    std::cout << "Card 1: " << std::endl;
    printCardFormatted(dealerPlayer->getHand()[0]);
    std::cout << std::endl << "Card 2: [Hidden]" << std::endl;
    
    // Player turns
    for (int i = 0; i < players.size(); ++i) {
        Player* currentPlayer = players[i];
        
        // Skip player if they didn't place a bet
        if (currentPlayer->getBet() <= 0) {
            continue;
        }
        
        std::cout << "\n" << BOLD << YELLOW << "══════ " << currentPlayer->getName() << "'s turn ══════" << RESET << std::endl;
        std::cout << "Current bet: " << GREEN << "$" << currentPlayer->getBet() << RESET << std::endl;
        
        // Show current player's cards
        std::cout << currentPlayer->getName() << "'s hand: ";
        printCards(currentPlayer->getHand());
        std::cout << " (Total: " << currentPlayer->getHandValue() << ")" << std::endl;
        
        // Player decision loop
        bool playerDone = false;
        while (!playerDone && currentPlayer->getHandValue() <= 21) {
            std::cout << CYAN << "\nOptions: " << RESET << std::endl;
            std::cout << "  " << GREEN << "[H]" << RESET << " Hit (get another card)" << std::endl;
            std::cout << "  " << YELLOW << "[S]" << RESET << " Stand (end your turn)" << std::endl;
            std::cout << CYAN << "Your choice (H/S): " << RESET;
            
            char choice;
            std::cin >> choice;
            choice = tolower(choice);
            
            if (choice == 'h') {
                int newCard = deck.drawCard();
                currentPlayer->receiveCard(newCard);
                
                std::cout << "\nYou drew: " << std::endl;
                printCardFormatted(newCard);
                std::cout << std::endl;
                
                std::cout << "Your hand now: ";
                printCards(currentPlayer->getHand());
                std::cout << " (Total: " << currentPlayer->getHandValue() << ")" << std::endl;
                
                if (currentPlayer->getHandValue() > 21) {
                    std::cout << RED << BOLD << "BUST! You went over 21." << RESET << std::endl;
                    playerDone = true;
                }
            } 
            else if (choice == 's') {
                std::cout << "You decided to stand with " << currentPlayer->getHandValue() << "." << std::endl;
                playerDone = true;
            } 
            else {
                std::cout << RED << "Invalid choice. Please enter 'H' to hit or 'S' to stand." << RESET << std::endl;
            }
        }
        
        std::cout << YELLOW << "\nPress Enter to continue to next player..." << RESET << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        clearScreen();
        
        // Redisplay dealer's hand
        std::cout << BOLD << "Dealer's hand: " << RESET << std::endl;
        std::cout << "Card 1: " << std::endl;
        printCardFormatted(dealerPlayer->getHand()[0]);
        std::cout << std::endl;
        std::cout << "Card 2: [Hidden]" << std::endl;
        
        // Show all players' current status
        for (int j = 0; j <= i; j++) {
            Player* player = players[j];
            if (player->getBet() <= 0) continue;
            
            std::cout << player->getName() << "'s hand: ";
            printCards(player->getHand());
            std::cout << " (Total: " << player->getHandValue() << ")";
            if (player->getHandValue() > 21) {
                std::cout << RED << " BUSTED!" << RESET;
            }
            std::cout << std::endl;
        }
    }
    
    // Dealer's turn
    std::cout << BOLD << MAGENTA << "\n══════ Dealer's turn ══════" << RESET << std::endl;
    std::cout << "Dealer reveals second card: " << std::endl;
    printCardFormatted(dealerPlayer->getHand()[1]);
    std::cout << std::endl;
    
    std::cout << "Dealer's hand: ";
    printCards(dealerPlayer->getHand());
    std::cout << " (Total: " << dealerPlayer->getHandValue() << ")" << std::endl;
    
    // Dealer hits until reaches 17 or more
    while (dealerPlayer->getHandValue() < 17) {
        std::cout << "Dealer hits..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Dramatic pause
        
        int newCard = deck.drawCard();
        dealerPlayer->receiveCard(newCard);
        
        std::cout << "Dealer drew: " << std::endl;
        printCardFormatted(newCard);
        std::cout << std::endl;
        
        std::cout << "Dealer's hand: ";
        printCards(dealerPlayer->getHand());
        std::cout << " (Total: " << dealerPlayer->getHandValue() << ")" << std::endl;
    }
    
    // Determine outcomes
    bool dealerBusted = dealerPlayer->getHandValue() > 21;
    if (dealerBusted) {
        std::cout << RED << BOLD << "Dealer BUSTED with " << dealerPlayer->getHandValue() << "!" << RESET << std::endl;
    } else {
        std::cout << "Dealer stands with " << dealerPlayer->getHandValue() << "." << std::endl;
    }
    
    // Show results
    std::cout << BOLD << CYAN << "\n╔═══════════════════════════════════════╗" << std::endl;
    std::cout << "║              GAME RESULTS             ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════╝\n" << RESET << std::endl;
    
    for (Player* player : players) {
        if (player->getBet() <= 0) continue;
        
        std::cout << BOLD << player->getName() << ": " << RESET;
        
        if (player->getHandValue() > 21) {
            std::cout << RED << "BUSTED with " << player->getHandValue() << RESET << std::endl;
        }
        else if (dealerBusted) {
            std::cout << GREEN << "WINS! Dealer busted." << RESET << std::endl;
        }
        else if (player->getHandValue() > dealerPlayer->getHandValue()) {
            std::cout << GREEN << "WINS with " << player->getHandValue() 
                      << " against dealer's " << dealerPlayer->getHandValue() << RESET << std::endl;
        }
        else if (player->getHandValue() < dealerPlayer->getHandValue()) {
            std::cout << RED << "LOSES with " << player->getHandValue() 
                     << " against dealer's " << dealerPlayer->getHandValue() << RESET << std::endl;
        }
        else {
            std::cout << YELLOW << "PUSHES (Tie) with " << player->getHandValue() << RESET << std::endl;
        }
    }
    
    // Process winnings
    processWinnings(players, dealerPlayer);
    
    // Clean up dealer
    delete dealerPlayer;
}

Blackjack::Blackjack(std::vector<Player*>& players) {
    clearScreen();
    std::cout << BOLD << CYAN << "\n╔═══════════════════════════════════════╗" << std::endl;
    std::cout << "║       WELCOME TO BLACKJACK GAME       ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════╝\n" << RESET << std::endl;
    
    std::cout << "Press Enter to start the game...";
    std::cin.get();
    
    // Game rules
    clearScreen();
    std::cout << BOLD << CYAN << "\n╔═══════════════════════════════════════╗" << std::endl;
    std::cout << "║           BLACKJACK RULES             ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════╝\n" << RESET << std::endl;
    
    std::cout << YELLOW << "1." << RESET << " Get as close to 21 without going over." << std::endl;
    std::cout << YELLOW << "2." << RESET << " Number cards: face value, Face cards: 10, Ace: 1 or 11." << std::endl;
    std::cout << YELLOW << "3." << RESET << " Each player starts with two cards." << std::endl;
    std::cout << YELLOW << "4." << RESET << " Only one of the dealer's cards is visible until the end." << std::endl;
    std::cout << YELLOW << "5." << RESET << " Players can 'Hit' for another card or 'Stand' to hold." << std::endl;
    std::cout << YELLOW << "6." << RESET << " Going over 21 is a 'Bust' and means you lose." << std::endl;
    std::cout << YELLOW << "7." << RESET << " Dealer must hit until their cards total 17 or higher." << std::endl;
    std::cout << YELLOW << "8." << RESET << " If dealer busts, all remaining players win." << std::endl;
    std::cout << YELLOW << "9." << RESET << " Otherwise, higher hand wins. Equal is a push (tie)." << std::endl;
    std::cout << YELLOW << "10." << RESET << " Winning pays 1:1 (you win what you bet)." << std::endl;
    
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
    
    // Game loop
    bool playAgain = true;
    while (playAgain) {
        playGame(players);
        
        // Check if any players have money left
        bool anyPlayerWithMoney = false;
        for (Player* player : players) {
            if (player->getBank() > 0) {
                anyPlayerWithMoney = true;
                break;
            }
        }
        
        if (!anyPlayerWithMoney) {
            std::cout << RED << BOLD << "\nAll players are out of money! Game over." << RESET << std::endl;
            break;
        }
        
        std::cout << "\n" << YELLOW << "Would you like to play again?" << RESET << std::endl;
        std::cout << GREEN << "[1]" << RESET << " Yes" << std::endl;
        std::cout << RED << "[0]" << RESET << " No" << std::endl;
        std::cout << "Your choice: ";
        
        int input = 1;
        getIntInput(input);
        
        while (input != 0 && input != 1) {
            std::cout << RED << "Invalid input. Please enter 0 or 1: " << RESET;
            getIntInput(input);
        }
        
        playAgain = (input == 1);
        
        if (playAgain) {
            clearScreen();
        }
    }
    
    std::cout << BOLD << CYAN << "\nThank you for playing Blackjack! Goodbye!\n" << RESET << std::endl;
}