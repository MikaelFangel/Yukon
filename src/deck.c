#include "deck.h"
#include "linkedlist.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

// TODO Implement with linked list
int fillSuits(Linked_list *list) {
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
int checkCard(Linked_list *list, Card deck_card) {
    int counter = 0;
    Node *node = list->head;
    // Given a card, go trough the linked list, and check if we can find a match
    while (node != NULL) {
        Card *card = (Card *) node;
        // Check linked list node up against the deck
        if (card->suit == deck_card.suit && card->value == deck_card.value) {
            if (!card->existsInGame) {
                ++counter;
                card->existsInGame = true;
                // If match, then stop looping
                break;
            } else {
                //Duplicate cards
                return -2;
            }
        } else {
            // No match - check next node
            node = node->next;
        }
    }
    // If no match in linked list, then the card does not exist
    if (node == NULL) {
        return -1;
    }
    return 0;
}
int createDeck(char filepath[]) {
    FILE *fptr;
    fptr = fopen(filepath, "r");
    if (fptr == NULL) {
        // Not sure if this works... should exit the method
        return -1;
    }
    char line[4];
    Linked_list *cardDeck = createLinkedList();
    // While file not empty, read a line, create a card, and add it to linked list.
    while (fgets(line, sizeof line, fptr) != NULL) {
        Card *newCard = (Card *) malloc(sizeof(Card));
        newCard->value = line[0];
        newCard->suit = line[1];
        addNode(cardDeck, newCard);
    }
    fclose(fptr);
    if (fillSuits(cardDeck) != 0) {
        // Do something. All cards does not exist.
    }
    return 0;
}