#include "../include/dealer.h"
#include "../include/player.h"
#include "../include/utils.h"
#include "pokerBetting.h"
#include "pokerGame.h"
#include "declareWinner.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>    

void pokerGame::endGame() {
    std::cout << "Ending Game..." << std::endl;
    pool = 0;
    count = 0;
    gameOver = false;
    tableCards.clear();
    for (auto& player : playersPlaying) {
        player->clearHand();
    }
}
void pokerGame::playGame(std::vector<Player*> players) {
    clearScreen();
    dealer dealer1;
    count = 0;
    playersPlaying = players;
    
    for (auto i = 0; i<2; i++){
        for (auto& player : playersPlaying) {
            player->receiveCard(dealer1.drawCard());
        }
    }
    dealer1.dealPokerCards(tableCards);
    bets.takeBets(playersPlaying, count, tableCards);
    if (dw.checkWinner(playersPlaying, pool)) {
        endGame();
    }
    count++;
    bets.takeBets(playersPlaying, count, tableCards);
    if (dw.checkWinner(playersPlaying, pool)) {
        endGame();
    }
    count++;
    bets.takeBets(playersPlaying, count, tableCards);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    clearScreen();
    dw.checkWinner(playersPlaying, tableCards, pool);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for (auto& player : playersPlaying) {
        player->showCards();
    }
    endGame();
}
pokerGame::pokerGame(std::vector<Player*> players) {
    out.showRules();
    playGame(players);
    std::cout << "Game over!" << std::endl;
    std::cout << "Enter 0 to exit, or 1 to play again." << std::endl;
    int input = 1;
    while (input != 0) {
        getIntInput(input);
        while (input != 0 && input != 1) {
            std::cout << "Invalid input. Please enter 0 or 1." << std::endl;
            getIntInput(input);
        }
        if (input == 1) {
            playGame(players);
            std::cout << "Game over!" << std::endl;
            std::cout << "Enter 0 to exit, or 1 to play again." << std::endl;
        }
    }
}
