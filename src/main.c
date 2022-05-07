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
        }
        else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            break;
        }
        else {
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
            if (tmpDeck != NULL) {
                deleteLinkedList(*loadedDeck);
                *loadedDeck = tmpDeck;
            }

        }
        else if (strcasecmp("SW", command) == 0) {
            showDeck(*loadedDeck, "SW", "OK");
        }
        else if (strcasecmp("SI", command) == 0) {
            int split;

            // if split is not giving generate a random split
            if (numOfInputs == 1) {
                Linked_list *test = *loadedDeck;
                split = rand() % (test->size - 1) + 1;
            }
            else {
                split = atoi(arg);
            }

            // Tries to run SI if SI returns NULL then skip because SI handles the error
            Linked_list *result = SI(*loadedDeck, split);
            if (result != NULL) {
                *loadedDeck = result;
                showDeck(*loadedDeck, "SI", "OK");
            }
        }
        else if (strcasecmp("SR", command) == 0) {
            *loadedDeck = SR(*loadedDeck);
            showDeck(*loadedDeck, "SR", "OK");
        }
        else if (strcasecmp("SD", command) == 0) {

            if (numOfInputs == 1) {
                SD(*loadedDeck, "cards");
            }
            else {
                SD(*loadedDeck, arg);
            }
            showDeck(*loadedDeck, "SD", "Deck has been saved.");

        }
        else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            *gameRunning = false;
            break;
        }
        else {
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
        }
        else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            *gameRunning = false;
            break;
        }
        else if (strcasecmp("Q", command) == 0) {
            // TODO: View??

            generateEmptyView("Q", "OK. Your are now in the STARTUP Phase");
            break;
        }

            // TODO: Implement Game Moves
        else {
            gameMoves(buf, column_lists, foundation_lists);
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
