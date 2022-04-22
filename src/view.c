#include "view.h"
#include "deck.h"

int generateEmptyView(char lastCommand[], char message[]) {
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
    return 0;
}

int generateView(Node *head) {
    Node *current_node = head;

    // Creates an empty view
    if (current_node == NULL) {
        generateEmptyView("SW", "ERROR! No deck of cards is loaded");
        return 1;
    }

    clearView();
    generateColumns();
    Card *card = current_node->key;
    char value;
    char suit;

    for (int i = 1; i <= 8; i++) {
        for (int j = 0; j < 7; ++j) {
            if (card != NULL) {

                if (card->faceDown == true)
                    card->faceDown = false;

                value = card->value;
                suit = card->suit;

                printf("%c%c\t", value, suit);
                card = current_node->next;
            }
        }

        if (i % 2 == 1) {
            printf("\t[]\tF%d\n", i);
            current_node = current_node->next;
        }
        else {
            printf("\n");
        }
    }

    for (int j = 0; j < 7; ++j) {
        value = card->value;
        suit = card->suit;

        printf("%c%c\t", value, suit);
        card = current_node->next;

        if (card == NULL) break;
    }

    printCommandConsole("SW", "OK");
    return 0;
}

int generateColumns() {
    for (int i = 1; i <= 7; ++i) {
        printf("C%d\t", i);
    }
    printf("\n\n");
    return 0;
}

int printCommandConsole(char lastCommand[], char message[]) {
    printf("LAST Command: %s \n", lastCommand);
    printf("Message: %s \n", message);
    printf("INPUT > ");

    return 0;
}

/**
 * clears console depending on OS
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
