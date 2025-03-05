#ifndef HANDEVALUATOR_H
#define HANDEVALUATOR_H

#include "node.h"
#include <vector>
#include <iostream>
#include <algorithm>

class handEvaluator {
    public:
    bool checkFlush(node *hand);
    bool checkStraight(node *hand);
    bool checkFourOfAKind(node *hand);
    bool checkFullHouse(node *hand);
    bool checkThreeOfAKind(node *hand);
    bool checkTwoPair(node *hand);
    bool checkPair(node *hand);
    bool checkRoyalStraight(node *hand);
    int checkHighCard(node *hand);
    int checkPairInt(node *hand) const;
    int checkThreeOfAKindInt(node *hand) const;
};

#endif