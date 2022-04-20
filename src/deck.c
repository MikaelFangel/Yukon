#include "deck.h"
#include "linkedlist.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

// TODO Implement with linked list
int fillSuits() {
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
    return 0;
}
int checkCard(Card *deck_card) {
    int counter = 0;
    int suit_value;
    int value;
    switch (deck_card->suit) {
        case 'C' :
            suit_value = 1;
            break;
        case 'D' :
            suit_value = 2;
            break;
        case 'H' :
            suit_value = 3;
            break;
        case 'S' :
            suit_value = 4;
            break;
        default:
            // Error handling?
            break;
    }
    switch (deck_card->value) {
        case 'A':
            value = 1;
            break;
        case '2':
            value = 2;
            break;
        case '3':
            value = 3;
            break;
        case '4':
            value = 4;
            break;
        case '5':
            value = 5;
            break;
        case '6':
            value = 6;
            break;
        case '7':
            value = 7;
            break;
        case '8':
            value = 8;
            break;
        case '9':
            value = 9;
            break;
        case 'T':
            value = 10;
            break;
        case 'J':
            value = 11;
            break;
        case 'Q':
            value = 12;
            break;
        case 'K':
            value = 13;
            break;
        default:
            //Error handling?
            break;
    }

    if (deck[suit_value][value].suit == deck_card->suit && deck[suit_value][value].value == deck_card->value) {
        if (!deck_card->existsInGame) {
            ++counter;
            deck_card->existsInGame = true;
            return 0;
        } else {
            //Duplicate cards
            return 1;
        }
    }
    // Card cannot be found
    return 2;
}
int createDeck(char filepath[]) {
    FILE *fptr;
    fptr = fopen(filepath, "r");
    if (fptr == NULL) {
        // Not sure if this works... should exit the method
        return 1;
    }
    char line[4];
    Linked_list *cardDeck = createLinkedList();
    // While file not empty, read a line, create a card, and add it to linked list.
    while (fgets(line, sizeof line, fptr) != NULL) {
        Card *newCard = (Card *) malloc(sizeof(Card));
        newCard->value = line[0];
        newCard->suit = line[1];
        addNode(cardDeck, newCard);
        checkCard(newCard);
    }
    fclose(fptr);
    return 0;
}