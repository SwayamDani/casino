#include <gtest/gtest.h>
#include "../poker/handEvaluator.h"
#include "../poker/declareWinner.h"
#include "../poker/pokerBetting.h"
#include "../poker/pokerGame.h"
#include "../poker/pokerOutput.h"
#include "../include/player.h"

// Function to create a linked list from a vector of integers
node* createHand(const std::vector<int>& cards) {
    if (cards.empty()) return nullptr;
    node* head = new node;
    head->data = cards[0];
    node* current = head;
    for (size_t i = 1; i < cards.size(); ++i) {
        current->next = new node;
        current = current->next;
        current->data = cards[i];
    }
    current->next = head;
    return head;
}

// Function to delete a circular linked list
void deleteHand(node* head) {
    if (!head) return;
    node* current = head->next;
    while (current != head) {
        node* next = current->next;
        delete current;
        current = next;
    }
    delete head;
}

// Hand Evaluator Tests
class HandEvaluatorTest : public ::testing::Test {
protected:
    handEvaluator he;
};

TEST_F(HandEvaluatorTest, CheckFlush) {
    node* hand = createHand({0, 1, 2, 3, 4});
    EXPECT_TRUE(he.checkFlush(hand));
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckStraight) {
    node* hand = createHand({0, 1, 2, 3, 4});
    EXPECT_TRUE(he.checkStraight(hand));
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckFourOfAKind) {
    node* hand = createHand({1, 1, 1, 1, 2});
    EXPECT_TRUE(he.checkFourOfAKind(hand));
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckPair) {
    node* hand = createHand({1, 4, 2, 3, 1});
    EXPECT_TRUE(he.checkPair(hand));
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckFullHouse) {
    node* hand = createHand({1, 1, 2, 2, 2});
    EXPECT_TRUE(he.checkFullHouse(hand));
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckHighCard) {
    node* hand = createHand({1, 2, 3, 4, 12});
    EXPECT_EQ(he.checkHighCard(hand), 12);
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckRoyalFlush) {
    node* hand = createHand({8, 9, 10, 11, 12});
    EXPECT_TRUE(he.checkRoyalStraight(hand));
    deleteHand(hand);
}

TEST_F(HandEvaluatorTest, CheckInvalidHand) {
    node* hand = createHand({1, 1, 1});
    EXPECT_FALSE(he.checkFullHouse(hand));
    deleteHand(hand);
}

// Declare Winner Tests
class DeclareWinnerTest : public ::testing::Test {
protected:
    declareWinner dw;
};

TEST_F(DeclareWinnerTest, MultiplePlayersTiebreaker) {
    std::vector<Player*> players;
    Player* player1 = new Player("Player 1", 1000);
    Player* player2 = new Player("Player 2", 1000);
    player1->receiveCard(10);
    player1->receiveCard(11);
    player2->receiveCard(12);
    player2->receiveCard(13);
    players.push_back(player1);
    players.push_back(player2);
    std::vector<int> tableCards = {0, 1, 2, 3, 4};
    dw.checkWinner(players, tableCards, 500);
    delete player1;
    delete player2;
}

TEST_F(DeclareWinnerTest, InvalidTableCards) {
    std::vector<Player*> players;
    Player* player = new Player("Player 1", 1000);
    players.push_back(player);
    std::vector<int> tableCards = {0, 1};
    EXPECT_NO_THROW(dw.checkWinner(players, tableCards, 500));
    delete player;
}

// Poker Betting Tests
class PokerBettingTest : public ::testing::Test {
protected:
    pokerBetting pb;
};

TEST_F(PokerBettingTest, PlayerGoesAllIn) {
    Player* player = new Player("Player", 200);
    player->setBet(200);
    EXPECT_EQ(player->getBank(), 0);
    delete player;
}

TEST_F(PokerBettingTest, InvalidBet) {
    Player* player = new Player("Player", 100);
    EXPECT_FALSE(player->correctBet(200));
    delete player;
}

// Poker Output Tests
class PokerOutputTest : public ::testing::Test {
protected:
    pokerOutput po;
};

TEST_F(PokerOutputTest, DisplayPool) {
    testing::internal::CaptureStdout();
    po.showPool(500);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("500"), std::string::npos);
}
