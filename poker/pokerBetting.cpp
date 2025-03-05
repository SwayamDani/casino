#include "pokerBetting.h"
#include "../include/player.h"
#include "node.h"
#include "iostream"
#include "vector"
#include "chrono"
#include "thread"

void pokerBetting::takeBets( std::vector<Player*>& playersPlaying, const int count, const std::vector<int>& tableCards){
    if (count == 0) {
        out.showFlops(tableCards);
    } else if (count == 1) {
        out.showTurn(tableCards);
    } else if (count == 2) {
        out.showRiver(tableCards);
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::vector<Player*> playersToRespond = playersPlaying;
    std::vector<Player*> playersFolded;
    int minBet = 0;
    int diff = 0;
    while (!playersToRespond.empty()) {
        for (auto it = 0; it < playersToRespond.size();) {
            clearScreen();
            std::cout << BOLD << "=== " << playersToRespond[it]->getName() << "'s Turn ===" << RESET << std::endl;
            out.countdown(5);
            clearScreen();
            out.showPool(pool);
            if (count == 0) {
                out.showFlops(tableCards);
            } else if (count == 1) {
                out.showTurn(tableCards);
            } else if (count == 2) {
                out.showRiver(tableCards);
            }
            Player* player = playersToRespond[it];
            std::cout << YELLOW << "Your Cards:" << RESET << std::endl;
            player->showCards();
            std::cout << std::endl;
            out.showBettingActions(minBet);
            int userInput;
            int bet = 0;
            getIntInput(userInput);
            while (userInput < 1 || userInput > 3) {
                std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
                getIntInput(userInput);
            }
            switch (userInput) {
                case 1:
                    playersToRespond.erase(playersToRespond.begin()+it);
                    playersPlaying.erase(playersPlaying.begin()+it);   
                    break;
                case 2:
                    bet = minBet;
                    if(player->correctBet(bet)) {
                        pool += bet;
                        std::cout << "pool: " << pool << std::endl;
                        player->setBet(bet);
                        playersToRespond.erase(playersToRespond.begin()+it);
                    } else {
                        std::cout << "You only have $" << player->getBank() << "left. Please try again." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                    break;
                case 3:
                    std::cout << "Enter bet amount: ";
                    getIntInput(bet);
                    while (bet < minBet) {
                        std::cout << "Invalid input. Please enter a number greater than " << minBet << "." << std::endl;
                        getIntInput(bet);
                    }
                    if (!player->correctBet(bet)) {
                        std::cout << "You only have $" << player->getBank() << "left. Please try again." << std::endl;
                        break;
                    }
                    pool += bet;
                    
                    minBet = bet;
                    player->setBet(bet);
                    playersToRespond.clear();
                    for (auto &p : playersPlaying) {
                        if (p->getName() != player->getName()) {
                            playersToRespond.push_back(p);
                        }
                    }
                    it = 0;
                    break;
                default:
                    std::cout << "Invalid input. Please try again." << std::endl;
                    break;
            }
        }
    }
    clearScreen();
}