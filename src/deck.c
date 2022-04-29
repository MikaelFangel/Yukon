#include "deck.h"
#include "linkedlist.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

// TODO Implement with linked list
int fillSuits() {
    char suits[4] = {'C', 'D', 'H', 'S'};

    for (int i = 0; i < 4; i++) {
        deck[i][0].value = 'A';
        deck[i][0].suit = suits[i];

        for (int j = 1; j < 10; ++j) {
            deck[i][j].value = (j + 1) + '0';
            deck[i][j].suit = suits[i];
        }

        deck[i][9].value = 'T';
        deck[i][9].suit = suits[i];
        deck[i][10].value = 'J';
        deck[i][10].suit = suits[i];
        deck[i][11].value = 'Q';
        deck[i][11].suit = suits[i];
        deck[i][12].value = 'K';
        deck[i][12].suit = suits[i];
    }

    return 0;
}

int checkCard(Card *deck_card) {
    int suit_value;
    int value;
    switch (deck_card->suit) {
        case 'C' :
            suit_value = 0;
            break;
        case 'D' :
            suit_value = 1;
            break;
        case 'H' :
            suit_value = 2;
            break;
        case 'S' :
            suit_value = 3;
            break;
        default:
            // Error handling?
            break;
    }
    switch (deck_card->value) {
        case 'A':
            value = 0;
            break;
        case '2':
            value = 1;
            break;
        case '3':
            value = 2;
            break;
        case '4':
            value = 3;
            break;
        case '5':
            value = 4;
            break;
        case '6':
            value = 5;
            break;
        case '7':
            value = 6;
            break;
        case '8':
            value = 7;
            break;
        case '9':
            value = 8;
            break;
        case 'T':
            value = 9;
            break;
        case 'J':
            value = 10;
            break;
        case 'Q':
            value = 11;
            break;
        case 'K':
            value = 12;
            break;
        default:
            //Error handling?
            break;
    }

    Card *card_to_test = &deck[suit_value][value];

    if (card_to_test->suit == deck_card->suit && card_to_test->value == deck_card->value) {
        if (!deck_card->existsInGame) {
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

Linked_list *loadDeck(FILE *fptr) {
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
    return cardDeck;
}
int saveDeck(Linked_list *list) {
    FILE *fptr;
    fptr = fopen("/Users/mads/CLionProjects/Yukon/Resources/test.txt", "w");
    char line[3];
    line[2] = '\n';
    Node *node = list->head;
    // While linked list not null, write a card to the file.
    while (node != NULL) {
        Card *card = (Card*) node->key;
        line[0] = card->value;
        line[1] = card->suit;
        fwrite(line, 1, sizeof line, fptr);
        node = node->next;
    }
    fclose(fptr);
    return 0;
}

/**
 * Adds a card from the top of one deck to the bottom of another deck.
 * The tail is the top of the deck!
 * Used in the SI command
 * @param toDeck
 * @param nodeBeingMoved
 */
void moveToAnotherDeck(Linked_list *fromDeck, Linked_list *toDeck) {
    Node *nodeBeingMoved = fromDeck->tail;
    fromDeck->tail = nodeBeingMoved->prev;
    if (fromDeck->tail != NULL)
        fromDeck->tail->next = NULL;

    if (toDeck->size == 0) {
        nodeBeingMoved->prev = NULL;
        nodeBeingMoved->next = NULL;

        toDeck->head = nodeBeingMoved;
        // toDeck->head->next = NULL;
        // toDeck->head->prev = NULL;

        toDeck->tail = nodeBeingMoved;
        // toDeck->tail->next = NULL;
        // toDeck->tail->prev = NULL;
    }
    else {
        nodeBeingMoved->next = toDeck->head;
        nodeBeingMoved->prev = NULL;

        toDeck->head->prev = nodeBeingMoved;
        toDeck->head = nodeBeingMoved;
    }

    fromDeck->size--;
    toDeck->size++;
}
