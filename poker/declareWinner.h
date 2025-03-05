#ifndef DECLAREWINNER_H
#define DECLAREWINNER_H

#include "../include/player.h"
#include "handEvaluator.h"
#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>

class declareWinner {
    public:
    void checkWinner(const std::vector<Player*> &, const std::vector<int>&, const int);
    bool checkWinner(const std::vector<Player*> &, const int);
    private:
    handEvaluator h;
    void freeCircularList(node* head);
    int determineWinner(const std::vector<int> &, const std::vector<node*>&, int);
};

#endif // DECLAREWINNER_H


