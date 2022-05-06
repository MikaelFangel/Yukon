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
    // Splits the deck into two decks, which should be interleaved
    Linked_list *secondPile = createLinkedList();

    struct ListCard *card = firstPile->head;
    for (int i = 0; i < split; ++i) {
        card = card->next;
    }

    moveCardFromOneLinkedListToAnother(firstPile, card, secondPile);

    // Interleaves the two decks into a shuffled pile
    Linked_list *shuffledPile = createLinkedList();
    while (firstPile->size > 0 || secondPile->size > 0) {
        if (firstPile->size > 0) {
            prependCard(shuffledPile, *firstPile->tail);
            removeNode(firstPile);
        }
        if (secondPile->size > 0) {
            prependCard(shuffledPile, *secondPile->tail);
            removeNode(secondPile);
        }
    }

    //free(firstPile);
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

    struct ListCard *node = unshuffledPile->tail;
    while (node != NULL) {
        // Calculate a random placement within the ranges of the shuffled piles size.
        // Add with 1 to avoid zero division error.
        int placement = rand() % (shuffledPile->size + 1);

        // Finds the placement in the shuffled pile, so we know where to insert
        struct ListCard *shuffNode = shuffledPile->head;
        for (int i = 0; i < placement - 1; i++) {
            shuffNode = shuffNode->next;
        }

        // Randomize if the card is placed before or after the chosen placement
        int before = rand() % 2;
        insertNode(shuffledPile, node, shuffNode, before);

        node = node->prev;
    }

    // Avoid memory leak of deck piles
    // deleteLinkedList(unshuffledPile);
    return shuffledPile;
}

Linked_list **P(Linked_list *loadedDeck) {
    Linked_list *tmp = malloc(sizeof(Linked_list));
    *tmp = *loadedDeck;

    Linked_list *C1 = createLinkedList();
    Linked_list *C2 = createLinkedList();
    Linked_list *C3 = createLinkedList();
    Linked_list *C4 = createLinkedList();
    Linked_list *C5 = createLinkedList();
    Linked_list *C6 = createLinkedList();
    Linked_list *C7 = createLinkedList();

    // Node *current_node = tmp->tail;

    // Rows
    for (int i = 1; i <= 11; ++i) {
        if (tmp->size == 0) break; // current_node == NULL
        // Columns
        for (int j = 1; j <= 7; ++j) {
            // Check if NULL
            if (tmp->size == 0) break; // current_node == NULL ||

            Linked_list *toDeck = NULL;
            struct ListCard *card = tmp->tail;;
            card->faceDown = false;
            if (j == 1 && i <= 1) {
                toDeck = C1;
            } else if (j == 2 && i <= 6) {
                toDeck = C2;
                if (i <= 1) card->faceDown = true;
            } else if (j == 3 && i <= 7) {
                toDeck = C3;
                if (i <= 2) card->faceDown = true;
            } else if (j == 4 && i <= 8) {
                toDeck = C4;
                if (i <= 3) card->faceDown = true;
            } else if (j == 5 && i <= 9) {
                toDeck = C5;
                if (i <= 4) card->faceDown = true;
            } else if (j == 6 && i <= 10) {
                toDeck = C6;
                if (i <= 5) card->faceDown = true;
            } else if (j == 7 && i <= 11) {
                toDeck = C7;
                if (i <= 6) card->faceDown = true;
            }

            //moveToAnotherDeck(tmp, toDeck, false);
            // current_node = current_node->next;
        }
    }

    Linked_list **C_ptr = malloc(sizeof(Linked_list *) * 7);
    C_ptr[0] = C1;
    C_ptr[1] = C2;
    C_ptr[2] = C3;
    C_ptr[3] = C4;
    C_ptr[4] = C5;
    C_ptr[5] = C6;
    C_ptr[6] = C7;
    free(tmp);
    return C_ptr;
}
