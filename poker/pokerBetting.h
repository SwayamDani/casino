#ifndef POKERBETTING_H
#define POKERBETTING_H

#include "vector"
#include "../include/player.h"
#include "pokerOutput.h"

class pokerBetting{
    pokerOutput out;
    int pool = 0;
    public:
    void takeBets(std::vector<Player*>& playersPlaying, const int count, const std::vector<int>& tableCards);
};

#endif

