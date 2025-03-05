#ifndef POKEROUTPUT_H
#define POKEROUTPUT_H

#include "../include/utils.h"

class pokerOutput{
    private:
    const std::string suits[4] = { "♥", "♦", "♣", "♠" };
    const std::string ranks[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    public:
    void showFlops(const std::vector<int>& tableCards) const;
    void showTurn(const std::vector<int>& tableCards) const;
    void showRiver(const std::vector<int>& tableCards) const;
    void showRules() const;
    void showPool(const int) const;
    void showBettingActions(const int) const;
    void countdown(const int) const;
};

#endif