#ifndef POKERGAME_H
#define POKERGAME_H

#include "../include/dealer.h"
#include "../include/player.h"
#include "../include/utils.h"
#include "declareWinner.h"
#include "pokerOutput.h"
#include "pokerBetting.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

class pokerGame{
private:
    std::vector<int> tableCards;
    std::vector<Player*> playersPlaying;
    pokerOutput out;
    pokerBetting bets;
    declareWinner dw;
    bool gameOver = false;
    int pool = 0;
    int count = 0;
    void takeBets();
    void endGame();
    void playGame(std::vector<Player*>);

public:
    pokerGame(std::vector<Player*>);
};

#endif