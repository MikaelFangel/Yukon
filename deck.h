//
// Created by mikael on 04/04/2022.
//
#include <stdio.h>
#include <stdbool.h>

#define SUIT_SIZE 13

struct card {
    char suit;
    char value;
    bool faceDown;
    bool existsInGame;
};

struct card clubs[SUIT_SIZE];
struct card diamonds[SUIT_SIZE];
struct card hearts[SUIT_SIZE];
struct card spades[SUIT_SIZE];

struct card *deck[4] = {clubs, diamonds, hearts, spades};

int fillSuits(const char *fileName);

// TODO Implement with linked list
int fillSuits(const char *fileName) {

    if (fileName == NULL) {

        for (int i = 0; i < 4; i++) {
            deck[i][0].value = 'A';

            for (int j = 1; j < 10; ++j) {
                deck[i][j].value = (j + 1) + '0';
            }

            deck[i][9].value = 'T';
            deck[i][10].value = 'J';
            deck[i][11].value = 'Q';
            deck[i][12].value = 'K';
        }

    }
}