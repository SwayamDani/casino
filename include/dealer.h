#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include <string>
#include <random>

class dealer {
public:
    dealer();
    void shuffleDeck();
    int drawCard();
    void dealPokerCards(std::vector<int>& hand);
    int spin_wheel();

private:
    std::vector<int> deck;
    void initializeDeck();
    std::random_device rd;
    std::mt19937 rng1;
};

#endif // DEALER_H