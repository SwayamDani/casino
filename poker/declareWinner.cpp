#include "declareWinner.h"
#include "handEvaluator.h"

void declareWinner::freeCircularList(node* head) {
    if (!head) return;
    // If the list contains only one node, its next pointer should point to itself.
    if (head->next == head) {
        delete head;
        return;
    }
    // Otherwise, traverse and free nodes until we loop back to head.
    node* current = head->next;
    while (current != head) {
        node* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
}

int declareWinner::determineWinner(const std::vector<int> &handRanks, const std::vector<node*>&hands, int pot) {
    int highestHand = 10;
    int highestHandIndex = 0;
    std::vector<int> tiedPlayers;

    // First find the best hand rank
    for (int i = 0; i < handRanks.size(); i++) {
        if (handRanks[i] < highestHand) {
            highestHand = handRanks[i];
            highestHandIndex = i;
            tiedPlayers.clear();
            tiedPlayers.push_back(i);
        }
        else if (handRanks[i] == highestHand) {
            tiedPlayers.push_back(i);
        }
    }

    // If only one player has the best hand, they win
    if (tiedPlayers.size() == 1) {
        std::cout << "\n\033[1;32m🏆 " << hands[highestHandIndex]->player->getName() << " wins with ";
        switch(highestHand) {
            case 1: std::cout << "Royal Flush!\033[0m\n"; break;
            case 2: std::cout << "Straight Flush!\033[0m\n"; break;
            case 3: std::cout << "Four of a Kind!\033[0m\n"; break;
            case 4: std::cout << "Full House!\033[0m\n"; break;
            case 5: std::cout << "Flush!\033[0m\n"; break;
            case 6: std::cout << "Straight!\033[0m\n"; break;
            case 7: std::cout << "Three of a Kind!\033[0m\n"; break;
            case 8: std::cout << "Two Pair!\033[0m\n"; break;
            case 9: std::cout << "One Pair!\033[0m\n"; break;
            case 10: std::cout << "High Card!\033[0m\n"; break;
        }
        std::cout << "\033[1;33m💰 Won $" << pot << "!\033[0m\n";
        hands[highestHandIndex]->player->addBank(pot);
        return highestHandIndex;
    }

    // If multiple players tie, compare high cards
    int highestCard = -1;
    std::vector<int> winners;
    
    for (int index : tiedPlayers) {
        int currentHighCard = h.checkHighCard(hands[index]);
        if (currentHighCard > highestCard) {
            highestCard = currentHighCard;
            winners.clear();
            winners.push_back(index);
        }
        else if (currentHighCard == highestCard) {
            winners.push_back(index);
        }
    }

    // If still tied after high card comparison
    if (winners.size() > 1) {
        int splitPot = pot / winners.size();
        std::cout << "\n\033[1;36m🤝 The pot of $" << pot << " will be split between: ";
        for (size_t i = 0; i < winners.size(); i++) {
            hands[winners[i]]->player->addBank(splitPot);
            std::cout << hands[winners[i]]->player->getName();
            if (i < winners.size() - 1) std::cout << " and ";
        }
        std::cout << "\n💰 Each player receives $" << splitPot << "\033[0m\n";
        return winners[0]; // Return first winner for split pot handling
    }

    std::cout << "\n\033[1;32m🏆 " << hands[winners[0]]->player->getName() << " wins with high card!\033[0m\n";
    hands[winners[0]]->player->addBank(pot);
    std::cout << "\033[1;33m💰 Won $" << pot << "!\033[0m\n";
    return winners[0];
}

void declareWinner::checkWinner(const std::vector<Player*> &players, const std::vector<int> &tableCards, const int pot) {
    
    if (tableCards.size() != 5) {
        std::cout << "\033[1;31m❌ Invalid number of table cards. Expected 5, got " << tableCards.size() << "\033[0m" << std::endl;
        return;
    }
    
    std::cout << "\n\033[1;35m🎲 Checking for winner...\033[0m\n";
    std::cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";
    std::vector<node*> hands;
    for (auto& player : players) {
        node *head = new node;
        node *current = head;
        current->player = player;
        std::vector<int> playerHand = player->getHand();
        current->data = playerHand[0];
        current->next = new node;
        current = current->next;
        current->data = playerHand[1];
        current->next = new node;
        current = current->next;
        for (auto i = 0; i < 5; ++i) {
            current->data = tableCards[i];
            if(i!=4){
                current->next = new node;
                current = current->next;
            }
        }
        current->next = head;
        hands.push_back(head);
    }
    int it = 0;
    std::vector<int> handRanks;
    for (auto& hand : hands) {
        std::cout << "\033[1;36m👤 Player: " << players[it]->getName() << "\033[0m\n";
        int rank = 10;  // Default to high card
        if (h.checkRoyalStraight(hand)) {
            rank = 1;
            std::cout << "   Hand: \033[1;33m🃏 Royal Flush\033[0m\n";
        }
        else if (h.checkFlush(hand) && h.checkStraight(hand)) {
            rank = 2;
            std::cout << "   Hand: \033[1;33m🃏 Straight Flush\033[0m\n";
        }
        else if (h.checkFourOfAKind(hand)) {
            rank = 3;
            std::cout << "   Hand: \033[1;33m🃏 Four of a Kind\033[0m\n";
        }
        else if (h.checkFullHouse(hand)) {
            rank = 4;
            std::cout << "   Hand: \033[1;33m🃏 Full House\033[0m\n";
        }
        else if (h.checkFlush(hand)) {    
            rank = 5;
            std::cout << "   Hand: \033[1;33m🃏 Flush\033[0m\n";
        } 
        else if (h.checkStraight(hand)) {
            rank = 6;
            std::cout << "   Hand: \033[1;33m🃏 Straight\033[0m\n";
        } 
        else if (h.checkThreeOfAKind(hand)) {
            rank = 7;
            std::cout << "   Hand: \033[1;33m🃏 Three of a Kind\033[0m\n";
        } 
        else if (h.checkTwoPair(hand)) {  // Fixed: was checking ThreeOfAKind twice
            rank = 8;
            std::cout << "   Hand: \033[1;33m🃏 Two Pair\033[0m\n";
        } 
        else if (h.checkPair(hand)) {
            rank = 9;
            std::cout << "   Hand: \033[1;33m🃏 Pair\033[0m\n";
        }
        else {
            std::cout << "   Hand: \033[1;33m🃏 High Card\033[0m\n";
        }
        handRanks.push_back(rank);  // Add the rank to the vector
        std::cout << "   High Card: " << h.checkHighCard(hand) << "\n";
        it++;
        std::cout << "\033[1;34m─────────────────────────────────────\033[0m\n";
    }

    // Calculate total pot from all players' bets
    int totalPot = 0;
    for (auto& player : players) {
        totalPot += player->getBet();
        std::cout << "\033[1;33m💰 Player " << player->getName() << " bet: $" << player->getBet() << "\033[0m\n";  // Debug output
    }
    std::cout << "\033[1;32m💰 Total pot: $" << pot << "\033[0m\n";  // Debug output
    std::cout << "\033[1;34m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m\n";

    int index = determineWinner(handRanks, hands, pot);
    
    // Clear all players' bets after determining winner
    for (auto& player : players) {
        player->clearBet();
    }

    for (auto head : hands) {
        freeCircularList(head);
    }
}

bool declareWinner::checkWinner(const std::vector<Player*> &players, const int pool) {
    if(players.size() == 1) {
        std::cout << "\n\033[1;32m🏆 " << players[0]->getName() << " wins the pot of $" << pool << "!\033[0m\n";
        players[0]->addBank(pool);
        return true;
    }
    return false;
}