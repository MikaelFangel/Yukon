#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "view.h"
#include "deck.h"
#include "commands.h"
#include <string.h>

int main(void) {
//    Source: https://intellij-support.jetbrains.com/hc/en-us/community/posts/115000763330-Debugger-not-working-on-Windows-CLion-
#if defined(_WIN32) || defined(_WIN64)
    setbuf(stdout, 0);
#endif

    char command[256], filepath[256], arg[256], buf[256];
    Linked_list* loadedDeck;
    bool deckLoaded = false;
    bool startupPhase = true, gameRunning = true;
    generateEmptyView("", "");

    while (!deckLoaded) {
        fgets(buf, sizeof(buf), stdin);
        int numOfInputs = sscanf(buf, "%s %s", command, arg);

        if (strcasecmp("LD", command) == 0) {
            loadedDeck = LD(arg, numOfInputs);
            if (loadedDeck != NULL)
                deckLoaded = true;
        } else {
            generateEmptyView("", "Error! The only valid command is LD");
        }
    }

    /** Startup Phase */
    while (true) {
        fgets(buf, sizeof(buf), stdin);
        // arg = ../resources/default.txt
        int numOfInputs = sscanf(buf, "%s %s", command, arg);

        if (strcasecmp("SW", command) == 0) {
            showDeck(loadedDeck, "SW", "OK");
        } else if (strcasecmp("SD", command) == 0) {

            /*strncpy(arg, "../resources/", 256);
            strcat(arg, inputs);
            strcat(arg, ".txt");*/


            //SD(loadedDeck, filepath);

        } else if (strcasecmp("SI", command) == 0) {
            int split;
            if (numOfInputs == 1) {
                split = rand() % (loadedDeck->size - 1) + 1;
                loadedDeck = SI(loadedDeck, split);
                showDeck(loadedDeck, "SI", "OK");
            } else {
                split = atoi(arg);
                if (split == 0) {
                    generateEmptyView("SI", "ERROR! You can't split on zero or something that ain't a number.");
                } else if (split >= loadedDeck->size) {
                    generateEmptyView("SI", "ERROR! You can't split on a number bigger than"
                                            " the number of cards in the deck.");
                } else {
                    loadedDeck = SI(loadedDeck, split);
                    showDeck(loadedDeck, "SI", "OK");
                }
            }
        } else if (strcasecmp("SR", command) == 0) {
            loadedDeck = SR(loadedDeck);
            showDeck(loadedDeck, "SR", "OK");
        } else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            break;
        }
            /** Play Phase*/
        else if (strcasecmp("P", command) == 0) {
            gameRunning = true;
            // TODO: Implement view
            generateEmptyView("P", "OK");
            // TODO: Implement Game Moves
            while (gameRunning) {
                fgets(buf, sizeof(buf), stdin);
                numOfInputs = sscanf(buf, "%s %s", command, arg);
                if (strcasecmp("Q", command) == 0) {
                    gameRunning = false;
                    // TODO: View??
                    generateEmptyView("Q", "OK. Your are now in the STARTUP Phase");
                } else {
                    generateEmptyView("", "Error! Invalid command");
                }
            }
        } else {
            generateEmptyView("", "Error! Invalid command");
        }
    }
    return 0;
}

