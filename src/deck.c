#include "deck.h"
#include "linkedlist.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

// TODO Implement with linked list
int fillSuits(FILE *fptr) {

    if (fptr == NULL) {

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

    } else {
        char line[3];
        Linked_list *cardDeck = createLinkedList();
        // While file not empty, read a line, create a card, and add it to linked list.
        while (fgets(line, sizeof line, fptr) != NULL) {
            Card *newCard = (Card *) malloc(sizeof(Card));
            newCard->value = line[0];
            newCard->suit = line[1];
            newCard->existsInGame = true;
            addNode(cardDeck,newCard);
        }
    }
}