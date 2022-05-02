#include "view.h"

// If a deck of more than (7 columns * 8 rows) = 56 cards is desired, increase this constant
const int MAX_NUM_OF_ROWS = 8;


/**
 * Generates the start view or empty views with error messages
 * @param lastCommand For start view, type ""
 * @param message For start view, type ""
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
        }
        else {
            printf("\n");
        }
    }

    printCommandConsole(lastCommand, message);
}

/**
 * View after calling STARTUP commands
 * The tail of the list is the top of the deck!
 *
 * It doesn't matter if the attribute faceDown on the card is true or false,
 * because the game hasn't started yet :)
 *
 * @param deck_list the deck given as a Linked List
 * @param faceUp true of SW, false if LD, SI or SR
 */
void showDeck(Linked_list *deck_list, char command[], char statusMessage[]) {
    // Creates an empty view
    if (deck_list == NULL) {
        generateEmptyView(command, "ERROR! No deck of cards is loaded");
        return;
    }

    Node *current_node = deck_list->tail;

    clearView();
    generateColumns();

    // Foundation number
    int Fnum = 1;
    Card *card = (Card *) current_node->key;;
    char value, suit;

    // Loop determining whether a foundation should be printed or not
    for (int i = 1; i <= MAX_NUM_OF_ROWS; i++) {
        // Loop to print the cards in the columns
        for (int j = 0; j < 7; ++j) {
            if (card == NULL || current_node == NULL) {
                printf("\t");
                continue;
            }

            // Show faceUp
            if (strcasecmp("SW", command) == 0) {
                value = card->value;
                suit = card->suit;
            }
                // Show faceDown
            else {
                value = '[';
                suit = ']';
            }

            printf("%c%c\t", value, suit);
            current_node = current_node->prev;
            if (current_node != NULL)
                card = (Card *) current_node->key;
        }

        // Only prints if uneven and less than 8. Only 4 foundations should be printed.
        if (i % 2 == 1 && i < 8) {
            printf("\t[]\tF%d\n", Fnum);
            Fnum++;
        }
        else {
            printf("\n");
        }
    }

    printf("\n");
    printCommandConsole(command, statusMessage);
}

/**
 * Column: Printed from head to tail
 * Foundation: Only tail is printed
 * @param C_ptr
 * @param F_ptr
 * @param lastCommand
 * @param message
 */
void makePlayView(Linked_list *C_ptr[7], Linked_list *F_ptr[4], char lastCommand[], char message[]) {
    clearView();
    generateColumns();

    Linked_list *current_column;
    Node *current_node;
    Card *card;
    int F_num = 1;
    char value;
    char suit;

    // This loop is for Foundations
    for (int i = 1; i <= MAX_NUM_OF_ROWS; i++) {
        // This loop is for Columns
        for (int j = 0; j < 7; ++j) {
            current_column = C_ptr[j];

            // Check if NULL
            if (current_column != NULL) {
                if (current_node != NULL && current_node->prev != NULL && current_node != current_column->head)
                    current_node = current_node->next;
                else
                    current_node = current_column->head;
                if (current_node != NULL)
                    card = (Card *) current_node->key;
            }

            if (card == NULL || current_node == NULL || current_column == NULL) {
                printf("\t");
                continue;
            }

            // Check if faceUp or faceDown
            if (card->faceDown == false) {
                value = card->value;
                suit = card->suit;
            }
            else {
                value = '[';
                suit = ']';
            }

            printf("%c%c\t", value, suit);
        }

        // Prints foundations
        Linked_list *current_foundation;
        Node *current_F;
        Card *Foundation_Card;
        if (i % 2 == 1 && i < 8) {
            current_foundation = F_ptr[F_num - 1];

            // Check if NULL
            if (current_foundation != NULL) {
                current_F = current_foundation->tail;
                if (current_node != NULL)
                    Foundation_Card = (Card *) current_F->key;
            }

            if (card == NULL || current_node == NULL || current_foundation == NULL) {
                printf("\t[]\tF%d\n", F_num);
                continue;
            }
            else {
                value = Foundation_Card->value;
                suit = Foundation_Card->suit;
                printf("\t%c%c\tF%d\n", value, suit, F_num);
            }
            F_num++;
        }
        else {
            printf("\n");
        }
    }

    printCommandConsole(lastCommand, message);
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

/**
 * Clears console depending on OS
 * Only used within view.c
 */
void clearView() {
    printf("\n\n\n");

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
