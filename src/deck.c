#include "deck.h"
#include "view.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

void fillSuits() {
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
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            // Calculates the corresponding number of its ASCII value
            value = deck_card->value - 49;
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
    // Invalid card - cannot be found
    return 2;
}

/**
 * Load a deck from a file. File must be a list of cards represented with 2 characters
 * eg. Ace of Hearts - "AH" with newline after each card. Returns the deck in a linked list
 * Used in LD command
 * @param fptr
 * @return cardDeck
 */
Linked_list *loadDeck(FILE *fptr) {
    fillSuits();
    char line[4];
    Linked_list *cardDeck = createLinkedList();
    // While file not empty, read a line, create a card, and add it to linked list.
    int counter = 1;
    while (fgets(line, sizeof line, fptr) != NULL) {
        Card *newCard = (Card *) malloc(sizeof(Card));
        newCard->value = line[0];
        newCard->suit = line[1];
        appendNode(cardDeck, newCard);
        if (checkCard(newCard) != 0) generateEmptyView("LD", "Error with card on line");
        ++counter;
    }
    return cardDeck;
}

/**
 * Save deck to a file
 * Used in SD command
 * @param list
 */
void saveDeck(Linked_list *list, FILE *fptr) {
    char line[3];
    line[2] = '\n';
    Node *node = list->head;
    // While linked list not null, write a card to the file.
    while (node != NULL) {
        Card *card = (Card *) node->key;
        line[0] = card->value;
        line[1] = card->suit;
        fwrite(line, 1, sizeof line, fptr);
        node = node->next;
    }
}

/**
 * Adds a card from the top of one deck to the bottom of another deck.
 * The tail is the top of the deck!
 * Used in the SI command
 * @param fromDeck  The deck from which the card is being moved
 * @param toDeck    The deck to which the card is being moved
 * @param toBottom  to Bottom (head) or to Top (tail)
 */
void moveToAnotherDeck(Linked_list *fromDeck, Linked_list *toDeck, bool toBottom) {
    if (fromDeck == NULL || toDeck == NULL) {
        //printf("ERROR");
        return;
    }

    Node *nodeBeingMoved = fromDeck->tail;
    fromDeck->tail = nodeBeingMoved->prev;

    // To prevent segmentation error
    if (fromDeck->tail != NULL)
        fromDeck->tail->next = NULL;

    // Add to an emtpy deck
    if (toDeck->size == 0) {
        nodeBeingMoved->prev = NULL;
        nodeBeingMoved->next = NULL;

        toDeck->head = nodeBeingMoved;
        toDeck->tail = nodeBeingMoved;
    }
    // Add to a non-empty deck
    else {
        if (toBottom) {
            nodeBeingMoved->next = toDeck->head;
            nodeBeingMoved->prev = NULL;

            toDeck->head->prev = nodeBeingMoved;
            toDeck->head = nodeBeingMoved;
        }
        else {
            nodeBeingMoved->next = NULL;
            nodeBeingMoved->prev = toDeck->tail;

            toDeck->tail->next = nodeBeingMoved;
            toDeck->tail = nodeBeingMoved;
        }
    }

    fromDeck->size--;
    toDeck->size++;
}
