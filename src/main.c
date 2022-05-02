#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "view.h"
#include "deck.h"
#include "commands.h"
#include <string.h>

int main(void) {
// Source: https://intellij-support.jetbrains.com/hc/en-us/community/posts/115000763330-Debugger-not-working-on-Windows-CLion-
#if defined(_WIN32) || defined(_WIN64)
    setbuf(stdout, 0);
#endif

    char command[256], filepath[256], arg[256], buf[256];
    Linked_list* loadedDeck;
    bool deckLoaded = false;
    bool playPhase = true;
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

        if (strcasecmp("LD", command) == 0) {
            Linked_list *tmpDeck = LD(arg, numOfInputs);
            if (loadedDeck != NULL)
                loadedDeck = tmpDeck;
            free(tmpDeck);
        }
        else if (strcasecmp("SW", command) == 0) {
            showDeck(loadedDeck, "SW", "OK");
        }
        else if (strcasecmp("SI", command) == 0) {
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
        } else if (strcasecmp("SD", command) == 0) {

            if (numOfInputs == 1) {
                SD(loadedDeck, "cards");
            } else {
                SD(loadedDeck, arg);
            }
            showDeck(loadedDeck, "SD", "Deck has been saved.");

        } else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            break;
        }

        /** Play Phase*/
        else if (strcasecmp("P", command) == 0) {
            playPhase = true;
            // TODO: Generate needed linked lists for each column and foundation
            Linked_list *Column_lists[7] = {createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList(),  createLinkedList()};
            Linked_list *Foundation_lists[4] = {createLinkedList(), createLinkedList(), createLinkedList(), createLinkedList()};
            makePlayView(Column_lists, Foundation_lists, "P", "OK");

            while (playPhase) {
                fgets(buf, sizeof(buf), stdin);
                numOfInputs = sscanf(buf, "%s %s", command, arg);

                if (strcasecmp("Q", command) == 0) {
                    playPhase = false;
                    // TODO: View??
                    generateEmptyView("Q", "OK. Your are now in the STARTUP Phase");
                }

                // TODO: Implement Game Moves
                else {
                    const char delimeters[] = "-> :\n";
                    char *token;

                    /** GameMove stored in 2D char array
                     * gameMove[0] from column, eg C3
                     * gameMove[1] from card, ex H2
                     * gameMove[2] to column, ex C4
                     * Full command ex: C3:H2 -> C4
                     * Initialize with 0.
                     */
                    char gameMove[3][3] = {0};

                    token = strtok(buf, delimeters);

                    // Load gameMove in 2D array with string tokens
                    int i = 0;
                    while (token != NULL && i < 3) {
                        int j = 0;
                        while(j < 2) {
                            gameMove[i][j] = token[j];
                            ++j;
                        }
                        token = strtok(NULL, delimeters);
                        ++i;
                    }
                    generateEmptyView("Game Move", "OK");
                }
            }
        } else {
            generateEmptyView("", "Error! Invalid command");
        }
    }
    return 0;
}

