#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "../include/utils.h"

class Player {
public:
    Player(const std::string& name, int amount) : name(name), bank(amount), currentBet(0) {};
    void receiveCard(const int& card) { hand.push_back(card); }
    std::vector<int> getHand() const { return hand; }
    std::string getName() const { return name; }
    void showCards();
    void setBet(int bet) { 
        bank -= bet; 
        currentBet += bet;
    }
    int getBank() const { return bank; }
    void addBank(int amount) { bank += amount; }
    bool correctBet(int bet) const {return bet <= bank;};
    void clearHand() { hand.clear(); }
    int getHandValue() const;
    int handRank = -1;
    int getBet() const { return currentBet; }
    void clearBet() { currentBet = 0; }

private:
    std::string name;
    std::vector<int> hand;
    int bank;
    int currentBet = 0;
};

#endif // PLAYER_H