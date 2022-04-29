#include "view.h"


/**
 * Generates the start view or empty views with error messages
 * @param lastCommand For start view, type ""
 * @param message For start view, type ""
 * @return
 */
void generateEmptyView(char lastCommand[], char message[]) {
    clearView();
    generateColumns();
    int Fnum = 1;

    for (int i = 1; i <= 7; i++) {
        for (int j = 0; j < 8; ++j) {
            printf("\t");
        }

        if (i % 2 == 1) {
            printf("\t[]\tF%d\n", Fnum);
            Fnum++;
        } else {
            printf("\n");
        }
    }

    printCommandConsole(lastCommand, message);
}

/**
 * View after calling SW and LD
 * The tail of the list is the top of the deck!
 * @param deck_list the deck given as a Linked List
 * @param faceUp true of SW, false if LD, SI or SR
 */
void showDeck(Linked_list *deck_list, char command[], char statusMessage[]) {
    // Creates an empty view
    if (deck_list == NULL) {
        generateEmptyView("SW", "ERROR! No deck of cards is loaded");
        return;
    }

    Node *current_node = deck_list->tail;

    clearView();
    generateColumns();

    int Fnum = 1;
    Card *card = (Card *) current_node->key;;
    char value;
    char suit;

    for (int i = 1; i <= 8; i++) {
        for (int j = 0; j < 7; ++j) {
            if (card == NULL || current_node == NULL) {
                printf("\t");
                continue;
            }

            // It doesn't matter if the attribute faceDown on the card is true or false,
            // because the game hasn't started yet :)
            if (strcasecmp("SW", command) == 0) {
                value = card->value;
                suit = card->suit;
            } else {
                value = '[';
                suit = ']';
            }

            printf("%c%c\t", value, suit);
            current_node = current_node->prev;
            if (current_node != NULL)
                card = (Card *) current_node->key;
        }

        if (i % 2 == 1) {
            printf("\t[]\tF%d\n", Fnum);
            Fnum++;
        } else {
            printf("\n");
        }
    }

    // for (int j = 0; j < 7; ++j) {
    //     value = card->value;
    //     suit = card->suit;
    //
    //     printf("%c%c\t", value, suit);
    //     card = current_node->next;
    //
    //     if (card == NULL) break;
    // }

    printf("\n");
    printCommandConsole(command, statusMessage);
}

// Only used within this module
void generateColumns() {
    for (int i = 1; i <= 7; ++i) {
        printf("C%d\t", i);
    }
    printf("\n\n");
}

// Only used within this module
void printCommandConsole(char lastCommand[], char message[]) {
    printf("LAST Command: %s \n", lastCommand);
    printf("Message: %s \n", message);
    printf("INPUT > ");

    fflush(stdout);
}

/** Clears console depending on OS */
void clearView() {
    printf("\n\n\n");

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
