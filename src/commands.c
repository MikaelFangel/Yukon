#include "commands.h"

Linked_list *LD(char arg[], int numOfInputs) {
    char filepath[256];
    Linked_list *loadedDeck;

    /** If filepath is not empty */
    if (numOfInputs == 2) {
        strncpy(filepath, "../resources/", 256);
        strcat(filepath, arg);
        strcat(filepath, ".txt");

        FILE *file = fopen(filepath, "r");

        /** If file exists */
        if (file != NULL) {
            loadedDeck = loadDeck(file);
            showDeck(loadedDeck, "LD", "OK");
            fclose(file);
        } else {
            generateEmptyView("LD", "The file does not exist");
            return NULL;
        }

        /** If no filepath is given, load unshuffled deck */
    } else {
        FILE *defaultDeck = fopen("../resources/default.txt", "r");
        loadedDeck = loadDeck(defaultDeck);
        showDeck(loadedDeck, "LD", "No name specified unshuffled deck loaded");
        fclose(defaultDeck);
    }

    return loadedDeck;
}

void SD(Linked_list *list, char arg[]) {
    char filepath[256];
    strncpy(filepath, "../resources/", 256);
    strcat(filepath, arg);
    strcat(filepath, ".txt");
    FILE *fptr = fopen(filepath, "w");
    saveDeck(list, fptr);
    fclose(fptr);
}

/**
 * Shuffles the deck in an interleaved manner
 * The tail of the list is the top of the deck!
 * @param firstPile deck you want to shuffle
 * @param split Where to split the deck
 * @return A shuffled deck
 */
Linked_list *SI(Linked_list *firstPile, int split) {
    Linked_list *secondPile = createLinkedList();

    for (int i = 0; i < split; ++i) {
        moveToAnotherDeck(firstPile, secondPile);
    }

    Linked_list *shuffledPile = createLinkedList();
    while (firstPile->size > 0 || secondPile->size > 0) {
        if (firstPile->size > 0)
            moveToAnotherDeck(firstPile, shuffledPile);
        if (secondPile->size > 0)
            moveToAnotherDeck(secondPile, shuffledPile);
    }

    free(firstPile);
    free(secondPile);

    return shuffledPile;
}

/**
 * Shuffles the deck in a random manner where tail is the top of the deck and head the bottom.
 * @param unshuffledPile the pile to be shuffled
 * @return the shuffled pile of cards
 */
Linked_list *SR(Linked_list *unshuffledPile) {
    Linked_list *shuffledPile = createLinkedList();

    // Seed the random function with system time
    // Source: https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    srand(time(0));

    Node *node = unshuffledPile->tail;
    while (node != NULL) {
        // Calculate a random placement within the ranges of the shuffled piles size.
        int placement;
        if (shuffledPile->size > 0) {
            placement = rand() % shuffledPile->size + 1;
        } else {
            placement = 0;
        }

        // Finds the placement in the shuffled pile, so we know where to insert
        Node *shuffNode = shuffledPile->head;
        for (int i = 0; i < placement - 1; i++) {
            shuffNode = shuffNode->next;
        }

        // Randomize if the card is placed before or after the chosen placement
        int before = rand() % 2;
        insertNode(shuffledPile, node, shuffNode, before);

        node = node->prev;
    }

    // Avoid memory leak of deck piles
    deleteLinkedList(unshuffledPile);
    return shuffledPile;
}