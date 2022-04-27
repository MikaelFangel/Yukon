#include "commands.h"

int LD() {
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

void QQ(Linked_list *lists[], int numberOfLists) {
    for (int i = 0; i < numberOfLists; i++) {
        deleteLinkedList(lists[i]);
    }

    puts("Ending Yukon...");
    exit(0);
}
