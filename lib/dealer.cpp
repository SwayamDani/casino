#include "../include/dealer.h"
#include <algorithm>
#include <random>
#include <iostream>

dealer::dealer(): rd(), rng1(rd()){
    initializeDeck();
    shuffleDeck();
}

void dealer::initializeDeck() {
    deck.clear();
    for (int i = 0; i < 52; ++i) {
        deck.push_back(i);
    }
}

void dealer::shuffleDeck() {
    std::shuffle(deck.begin(), deck.end(), rng1);
}

int dealer::drawCard() {
    int card = deck.back();
    deck.pop_back();
    return card;
}

void dealer::dealPokerCards(std::vector<int>& hand) {
    int burnCard = drawCard();
    for (int i = 0; i < 3; ++i) {
        hand.push_back(drawCard());
    }
    burnCard = drawCard();
    hand.push_back(drawCard());
    burnCard = drawCard();
    hand.push_back(drawCard());
}

int dealer::spin_wheel() {
    std::uniform_int_distribution<int> dist(0, 36);
    return dist(rng1);
}