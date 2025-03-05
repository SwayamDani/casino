#ifndef ROULETTE_H
#define ROULETTE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include "../include/dealer.h"
#include "../include/player.h"

class roulette {
private:
    dealer dealer_roulette;
    Player* player;
    int bet_amount;
    
    // UI helper methods
    void displayRouletteWheel();
    void displayBettingOptions();
    
    // Animation methods
    void animateRouletteSpinning(int finalNumber);
    void displayCircularWheel(const std::vector<int>& wheelNumbers, int currentPos, const std::unordered_set<int>& redNumbersLocal, int rotation);
    void displayWheelAnimation(const std::vector<int>& wheelNumbers, int currentPos, const std::unordered_set<int>& redNumbersLocal);
    
public:
    roulette(Player* player); 
    void play();
    void process_bet(char game_type);
};

#endif // ROULETTE_H