#ifndef NODE_H
#define NODE_H

#include "../include/player.h"

struct node {
    Player *player;
    int data;
    node* next;
    int highCard = -1;
    int handRank = -1;
};

#endif // NODE_H
