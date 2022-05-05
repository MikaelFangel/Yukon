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

    char command[256], arg[256], buf[256];
    Linked_list* loadedDeck;
    bool deckLoaded = false;
    bool gameRunning = true, playPhase = true;
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
        } else {
            generateEmptyView("", "Error! The only valid command is LD");
        }
    }

    /** Startup Phase */
    while (gameRunning) {
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
        }
        else if (strcasecmp("SR", command) == 0) {
            loadedDeck = SR(loadedDeck);
            showDeck(loadedDeck, "SR", "OK");
        }
        else if (strcasecmp("SD", command) == 0) {

            if (numOfInputs == 1) {
                SD(loadedDeck, "cards");
            } else {
                SD(loadedDeck, arg);
            }
            showDeck(loadedDeck, "SD", "Deck has been saved.");

        }
        else if (strcasecmp("QQ", command) == 0) {
            puts("Ending Yukon...");
            break;
        }

        /** Play Phase*/
        else if (strcasecmp("P", command) == 0) {
            playPhase = true;
            Linked_list **column_lists = P(loadedDeck);
            Linked_list *foundation_lists[4] = {createLinkedList(), createLinkedList(),
                                                createLinkedList(), createLinkedList()};
            generatePlayView(column_lists, foundation_lists, "P", "OK");

            while (playPhase) {
                fgets(buf, sizeof(buf), stdin);
                numOfInputs = sscanf(buf, "%s %s", command, arg);

                if (strcasecmp("LD", command) == 0 || strcasecmp("SW", command) == 0
                    || strcasecmp("SI", command) == 0 || strcasecmp("SR", command) == 0
                    || strcasecmp("SD", command) == 0) {
                    generatePlayView(column_lists, foundation_lists,
                                     command, "ERROR! Command not available in the PLAY phase");
                }
                else if (strcasecmp("QQ", command) == 0) {
                    puts("Ending Yukon...");
                    gameRunning = false;
                    break;
                }
                else if (strcasecmp("Q", command) == 0) {
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
                        while(j < 2) {
                            gameMove[i][j] = token[j];
                            ++j;
                        }
                        token = strtok(NULL, delimeters);
                        ++i;
                    }

                    // Get columns/foundation numbers
                    int from = gameMove[0][1] - 49;
                    int to = gameMove[2][1] - 49;

                    // Get card. 0. value : 1. suit
                    char fromCard[2];
                    Linked_list *fromList = NULL;
                    Linked_list *toList = NULL;
                    // Check if <FROM> is Column (C) or Foundation (F).
                    if (gameMove[0][0] == 'C') {
                        // Set <FROM>> list and card
                        fromCard[0] = gameMove[1][0];
                        fromCard[1] = gameMove[1][1];
                        fromList = column_lists[from];
                         // If <FROM> is C, then we check <TO> for either C or F. If none, then we can error handle
                         if (gameMove[2][0] == 'C') toList = column_lists[to];
                         else if(gameMove[2][0] == 'F') toList = foundation_lists[to];
                         else; // TODO: Error handling if not C or F is typed in <TO>
                    } else if (gameMove[0][0] == 'F') {
                        // If <FROM> is F, then we can only move to a C. We use the top on F as the card from.
                        fromList = foundation_lists[from];
                        toList = column_lists[to];
                        Card *tempCard = (Card *) fromList->head->key;
                        fromCard[0] = tempCard->value;
                        fromCard[1] = tempCard->suit;
                    } else; // TODO: Error handling if not C or F is typed in <FROM>
                    Node *nodeFrom = findNodeFromCard(fromList, fromCard[0], fromCard[1]);

                    // Move the card to the now column
                    // TODO: Discuss which method is best. Search by key or by node
                    // TODO: Validate move
                    //moveKeyFromOneLinkedListToAnother(column_lists[from], nodeFrom->key, column_lists[to]);
                    moveNodeFromOneLinkedListToAnother(fromList, nodeFrom, toList);

                    // Show deck
                    generatePlayView(column_lists, foundation_lists, "Move command", "OK");
                }
            }
        } else {
            generateEmptyView("", "Error! Invalid command");
        }
    }
    return 0;
}

