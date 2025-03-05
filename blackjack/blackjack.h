#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>
#include <chrono>
#include <thread>
#include <limits>
#include "../include/player.h"

class Blackjack {
private:
    void playGame(std::vector<Player*>& players);
    void printCards(const std::vector<int>& hand);
    void handleBetting(std::vector<Player*>& players);
    void processWinnings(std::vector<Player*>& players, Player* dealerPlayer);
    
public:
    Blackjack(std::vector<Player*>& players);
};

#endif // BLACKJACK_H