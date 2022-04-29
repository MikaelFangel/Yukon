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
            showDeck(loadedDeck, false);
            fclose(file);
        } else {
            generateEmptyView("LD", "The file does not exist");
            return NULL;
        }

        /** If no filepath is given, load unshuffled deck */
    } else {
        FILE *defaultDeck = fopen("../resources/default.txt", "r");
        loadedDeck = loadDeck(defaultDeck);
        showDeck(loadedDeck, false);
        fclose(defaultDeck);
    }

    return loadedDeck;
}

int SD(Linked_list *list, char filepath[]) {
    FILE *fptr = fopen(filepath, "w");
    saveDeck(list, fptr);
    fclose(fptr);
    return 0;
}

/**
 * Shuffles the deck in an interleaved manner
 * The tail of the list is the top of the deck!
 * @param firstPile deck you want to shuffle
 * @param split Where to split the deck
 * @return A shuffled deck
 */
Linked_list *SI(Linked_list *firstPile, int split) {
    // Node *tmp = firstPile->tail->key;
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

Linked_list *SR(Linked_list *unshuffledPile) {
    Linked_list *shuffledPile = createLinkedList();

    // Source: https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    srand(time(0));

    Node *node = unshuffledPile->head;
    while (node != NULL) {
        int placement;
        if (shuffledPile->size > 0) {
            placement = rand() % shuffledPile->size + 1;
        } else {
            placement = 0;
        }

        Node *shuffNode = shuffledPile->head;
        for (int i = 0; i < placement; i++) {
            if (shuffNode->next == NULL) {
                break;
            }

            shuffNode = shuffNode->next;
        }
        int before = rand() % 2;
        insertNode(shuffledPile, node, shuffNode, before);

        node = node->next;
    }
    return 0;
}

void QQ(Linked_list *lists[], int numberOfLists) {
    for (int i = 0; i < numberOfLists; i++) {
        deleteLinkedList(lists[i]);
    }

    puts("Ending Yukon...");
    exit(0);
}
