#include "handEvaluator.h"

bool handEvaluator::checkFlush(node *hand) {  
    node* current = hand;
    do {
        int count = 1;
        int suit = current->data / 13;
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data / 13 == suit) {
                count++;
            }
            if (count >= 5) {
                checkHighCard(hand);
                return true;
            }
        }
        current = current->next;
    }
    while(current != hand);
    return false;
}

bool handEvaluator::checkStraight(node *hand) {
    node *curr = hand;
    do {
        int count = 1;
        node *current = curr;
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13 + 1) {
                count++;
                current = current2;
            }
            if (count >= 5) {
                checkHighCard(hand);
                return true;
            }
        }
        curr = curr->next;
    }
    while(curr!=hand);
    return false;
}

bool handEvaluator::checkFourOfAKind(node *hand) {
    node* current = hand;
    do {
        int count = 1;
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13) {
                count++;
            }
            if (count == 4) {
                checkHighCard(hand);
                return true;
            }
        }
        current = current->next;
    }
    while(current != hand);
    return false;
}

bool handEvaluator::checkThreeOfAKind(node *hand) {
    node* current = hand;
    do {
        int count = 1;
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13) {
                count++;
            }
        }
        if (count == 3) {
            checkHighCard(hand);
            return true;
        }
        current = current-> next;
    }
    while(current != hand);
    return false;
}

int handEvaluator::checkThreeOfAKindInt(node *hand) const {
    node* current = hand;
    do {
        int count = 1;
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13) {
                count++;
            }
        }
        if (count == 3) {
            return current->data % 13;
        }
        current = current->next;
    }
    while(current != hand);
    return -1;
}

bool handEvaluator::checkFullHouse(node *hand) {
    int threeOfAKind = checkThreeOfAKindInt(hand);
    if (threeOfAKind == -1) {
        return false;
    }
    
    node* current = hand;
    do {
        if (current->data % 13 == threeOfAKind) {
            current = current->next;
            continue;
        }
        
        int count = 1;
        node* current2 = current->next;
        while (current2 != current) {
            if (current2->data % 13 == current->data % 13 && current2->data % 13 != threeOfAKind) {
                count++;
            }
            current2 = current2->next;
        }
        if (count == 2) {
            checkHighCard(hand);
            return true;
        }
        current = current->next;
    }
    while (current != hand);
    return false;
}

bool handEvaluator::checkPair(node *hand) {
    int count = 0;
    node* current = hand;
    do {
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13) {
                count++;
            }
            if (count == 2) {
                checkHighCard(hand);
                return true;
            }
        }
        current = current->next;
    }
    while(current != hand);
    return false;
}

int handEvaluator::checkPairInt(node *hand) const {
    int count = 0;
    node* current = hand;
    do {
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13) {
                count++;
            }
            if (count == 2) {
                return current->data % 13;
            }
        }
        current = current->next;
    }
    while(current != hand);
    return -1;
}

bool handEvaluator::checkTwoPair(node *hand) {
    int count = 0;
    int pair1 = checkPairInt(hand);
    if (pair1 == -1) {
        return false;
    }
    node* current = hand;
    do {
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13 && current2->data % 13 != pair1) {
                count++;
            }
            if (count == 2) {
                checkHighCard(hand);
                return true;
            }
        }
        current = current->next;
    }
    while(current != hand);
    return false;
}

int handEvaluator::checkHighCard(node *hand) {
    int highCard = -1;
    node *current = hand;
    do {
        if (current->data % 13 > highCard) {
            highCard = current->data % 13;
        }
        current = current->next;
    }
    while(current!=hand);
    return highCard;
}

bool handEvaluator::checkRoyalStraight(node *hand) {
    node* curr = hand;
    do {
        int count = 1;
        node *current = curr;
        for(node *current2 = current->next; current2 != current; current2 = current2->next) {
            if (current2->data % 13 == current->data % 13 + 1 && current2->data % 13 >= 8  && current->data/13 == current2->data/13) {
                count++;
                current = current2;
            }
            if (count >= 5) {
                return true;
            }
        }
        curr = curr->next;
    }
    while(curr != hand);
    return false;
}