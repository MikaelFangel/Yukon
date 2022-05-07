#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "view.h"
#include "deck.h"
#include "commands.h"
#include <string.h>

void startUpPhase(Linked_list **loadedDeck, bool *gameRunning);

void playPhase(Linked_list **loadedDeck, bool *gameRunning);

bool checkIfWinner(Linked_list *foundations[]);

/**
 * @authors s215812 Silja Sandersen (50%), s215805 Mads Sørensen (30%), s215797 Mikael Fangel (20%)
 */
int main(void) {
// Source: https://intellij-support.jetbrains.com/hc/en-us/community/posts/115000763330-Debugger-not-working-on-Windows-CLion-
#if defined(_WIN32) || defined(_WIN64)
    setbuf(stdout, 0);
#endif

    char command[256], arg[256], buf[256];
    Linked_list *loadedDeck;
    bool deckLoaded = false;
    bool gameRunning = true;
    // Start view
    generateEmptyView("", "");

    /** The first command has to be load */
    while (!deckLoaded) {
        fgets(buf, sizeof(buf), stdin);
        int numOfInputs = sscanf(buf, "%s %s", command, arg);

        if (strcasecmp("LD", command) == 0) {
            loadedDeck = LD(arg, numOfInputs);
            if (loadedDeck != NULL)
                deckLoaded = true;
        } else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            break;
        } else {
            generateEmptyView("", "Error! The only valid command is LD");
        }
    }

    while (gameRunning) {
        startUpPhase(&loadedDeck, &gameRunning);

        if (gameRunning)
            playPhase(&loadedDeck, &gameRunning);
    }

    return 0;
}

/**
 * Runs the startUpPhase of the game where the player is allowed to load decks and shuffle them
 * @param loadedDeck currently loaded deck
 * @param gameRunning the current running state of the game
 */
void startUpPhase(Linked_list **loadedDeck, bool *gameRunning) {
    char command[256] = {0}, arg[256] = {0}, buf[256] = {0};

    // Ends the loop if the P commands is given and thereby signaling the play phase.
    while ((strcasecmp("P", command) != 0)) {
        fgets(buf, sizeof(buf), stdin);
        int numOfInputs = sscanf(buf, "%s %s", command, arg);

        if (strcasecmp("LD", command) == 0) {
            Linked_list *tmpDeck = LD(arg, numOfInputs);
            if (loadedDeck != NULL) {
                deleteLinkedList(*loadedDeck);
                *loadedDeck = tmpDeck;
            }
            deleteLinkedList(tmpDeck);
        } else if (strcasecmp("SW", command) == 0) {
            showDeck(*loadedDeck, "SW", "OK");
        } else if (strcasecmp("SI", command) == 0) {
            int split;

            // if split is not giving generate a random split
            if (numOfInputs == 1) {
                Linked_list * test = *loadedDeck;
                split = rand() % (test->size - 1) + 1;
            } else {
                split = atoi(arg);
            }

            // Tries to run SI if SI returns NULL then skip because SI handles the error
            Linked_list *result = SI(*loadedDeck, split);
            if (result != NULL) {
                *loadedDeck = result;
                showDeck(*loadedDeck, "SI", "OK");
            }
        } else if (strcasecmp("SR", command) == 0) {
            *loadedDeck = SR(*loadedDeck);
            showDeck(*loadedDeck, "SR", "OK");
        } else if (strcasecmp("SD", command) == 0) {

            if (numOfInputs == 1) {
                SD(*loadedDeck, "cards");
            } else {
                SD(*loadedDeck, arg);
            }
            showDeck(*loadedDeck, "SD", "Deck has been saved.");

        } else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            *gameRunning = false;
            break;
        } else {
            generateEmptyView("", "Error! Invalid command");
        }
    }
}

/**
 * Runs the runs the play phase of the game to allow players to move cards and disable not allowed commands
 * @param loadedDeck currently loaded deck
 * @param gameRunning the current running state of the game
 */
void playPhase(Linked_list **loadedDeck, bool *gameRunning) {
    Linked_list **column_lists = P(*loadedDeck);
    Linked_list *foundation_lists[4] = {createLinkedList(), createLinkedList(),
                                        createLinkedList(), createLinkedList()};
    generatePlayView(column_lists, foundation_lists, "P", "OK");

    char command[256] = {0}, arg[256] = {0}, buf[256] = {0};
    while ((strcasecmp("Q", command) != 0)) {
        fgets(buf, sizeof(buf), stdin);
        int numOfInputs = sscanf(buf, "%s %s", command, arg);

        if (strcasecmp("LD", command) == 0 || strcasecmp("SW", command) == 0
            || strcasecmp("SI", command) == 0 || strcasecmp("SR", command) == 0
            || strcasecmp("SD", command) == 0) {
            generatePlayView(column_lists, foundation_lists,
                             command, "ERROR! Command not available in the PLAY phase");
        } else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            *gameRunning = false;
            break;
        } else if (strcasecmp("Q", command) == 0) {
            // TODO: View??

            generateEmptyView("Q", "OK. Your are now in the STARTUP Phase");
            break;
        }

            // TODO: Implement Game Moves
        else {
            const char delimeters[] = "-> :\n";
            char *token;

            /** GameMove stored in 2D char array
             * gameMove[0] from column, eg C3
             * gameMove[1] from card, ex 2H
             * gameMove[2] to column, ex C4 or F2
             * Full command ex: C3:2H -> C4
             * Initialize with 0.
             */
            char gameMove[3][3] = {0};

            token = strtok(buf, delimeters);

            // Load gameMove in 2D array with string tokens
            int i = 0;
            while (token != NULL && i < 3) {
                int j = 0;
                while (j < 2) {
                    gameMove[i][j] = token[j];
                    ++j;
                }
                token = strtok(NULL, delimeters);
                ++i;
            }

            // Get columns/foundation numbers
            int from = gameMove[0][1] - 49;
            int to = gameMove[2][1] - 49;
            //if (to <= 0 || to >= 8 || from <= 0 || from >= 8) { generatePlayView(column_lists, foundation_lists, "Move", "Error not a valid column number"); continue;}

            // Get card either from gaveMove or from head of Foundation/Column. 0. value : 1. suit
            char fromCard[2];
            bool toFoundation = false;

            Linked_list *fromList = NULL;
            Linked_list *toList = NULL;
            // Check if <FROM> is Column (C) or Foundation (F).
            if (gameMove[0][0] == 'C') {
                // Set <FROM> list and card
                fromCard[0] = gameMove[1][0];
                fromCard[1] = gameMove[1][1];
                fromList = column_lists[from];
                // If <FROM> is C, then we check <TO> for either C or F. If none, then we can error handle
                if (gameMove[2][0] == 'C') toList = column_lists[to];
                else if (gameMove[2][0] == 'F') {
                    toList = foundation_lists[to];
                    toFoundation = true;
                } // TODO: More validation can be added to check for correct foundation number.
                else {
                    generatePlayView(column_lists, foundation_lists, "Move", "ERROR. Not a valid <TO> command.");
                    continue;
                }
            } else if (gameMove[0][0] == 'F') {
                // If <FROM> is F, then we can only move to a C. We use the top on F as the card from.
                int toColumn = gameMove[1][1] - 49;
                // TODO: Add validation for toColumn in range 1 - 7
                fromList = foundation_lists[from];
                toList = column_lists[toColumn];
                struct ListCard *tempCard = fromList->tail;
                fromCard[0] = tempCard->value;
                fromCard[1] = tempCard->suit;
            } else {
                generatePlayView(column_lists, foundation_lists, "Move", "ERROR. Not a valid <FROM> command.");
                continue;
            }
            struct ListCard *nodeFrom = findNodeFromCard(fromList, fromCard[0], fromCard[1]);

            if (nodeFrom == NULL) {
                generatePlayView(column_lists, foundation_lists, "Move", "ERROR. Card cannot be found");
                continue;
            }

            // Move the card to the new column
            if (moveValidation(nodeFrom, toList->tail, toFoundation) == false) {
                generatePlayView(column_lists, foundation_lists, "Move", "Invalid move");
                continue;
            }
            moveCardFromOneLinkedListToAnother(fromList, nodeFrom, toList);

            // Show deck
            generatePlayView(column_lists, foundation_lists, "Move command", "OK");
        }

        bool winner = checkIfWinner(foundation_lists);
        if (winner) {
            generateEmptyView("", "Game Won");

            // gameRunning is the inverse of if there is a winner and is set to stop the game.
            *gameRunning = !winner;
        }
    }
}

/**
 * Checks if all four foundations are full and thereby determines if the game has a winner or not
 * @author s215797 Mikael Fangel
 * @param foundations
 * @return true if all foundations a full
 */
bool checkIfWinner(Linked_list *foundations[]) {
    int filledFoundations = 0;
    for (int i = 0; i < 4; i++) {
        if (foundations[i]->size == SUIT_SIZE)
            filledFoundations++;
    }

    return filledFoundations == 4;
}
