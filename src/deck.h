#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include <stdbool.h>
#include "linkedlist.h"

#define SUIT_SIZE 13
 typedef struct {
    char suit;
    char value;
    bool faceDown;
    bool existsInGame;
} Card;

extern Card clubs[SUIT_SIZE];
extern Card diamonds[SUIT_SIZE];
extern Card hearts[SUIT_SIZE];
extern Card spades[SUIT_SIZE];

extern Card *deck[4];

int fillSuits();
int createDeck(char filepath[]);
int validateDeck(Linked_list *list);

#endif