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

    char command[256], filename[256], arg[256], buf[256];
    Linked_list *LoadedDeck;
    bool deckLoaded = false;
    bool startupPhase = true, gameRunning = true;
    generateEmptyView("", "");

    while (!deckLoaded) {
        fgets(buf, sizeof(buf), stdin);
        char *inputs;
        inputs = strtok(buf, " ");

        if (strcasecmp("LD", inputs) == 0 || strcasecmp("LD\n", inputs) == 0) {
            /** If arg is not empty */
            inputs = strtok(NULL, "\n");
            if (inputs != NULL) {
                strncpy(arg, "../resources/", 256);
                strcat(arg, inputs);
                strcat(arg, ".txt");

                FILE *file = fopen(arg, "r");

                /** If file exists */
                if (file != NULL) {
                    LoadedDeck = loadDeck(file);
                    showDeck(LoadedDeck, false);
                    deckLoaded = true;
                    fclose(file);
                } else {
                    generateEmptyView("LD", "The file does not exist");
                }

            /** If no filename is given, load unshuffled deck */
            } else {
                FILE *defaultDeck = fopen("../resources/default.txt", "r");
                LoadedDeck = loadDeck(defaultDeck);
                showDeck(LoadedDeck, false);
                deckLoaded = true;
                fclose(defaultDeck);
            }
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
            showDeck(LoadedDeck, true);
        } else if (strcasecmp("SD", command) == 0) {

            /*strncpy(arg, "../resources/", 256);
            strcat(arg, inputs);
            strcat(arg, ".txt");*/


            //SD(LoadedDeck, filepath);

        } else if (strcasecmp("SI", command) == 0) {
            int split;
            if (numOfInputs == 1) {
                split = rand() % (LoadedDeck->size - 1) + 1;
            } else {
                split = atoi(arg);
                if (split == 0) {
                    generateEmptyView("SI", "ERROR! You can't split on something that ain't a number.");
                } else if (split >= LoadedDeck->size) {
                    generateEmptyView("SI", "ERROR! You can't split on a number bigger than"
                                            " the number of cards in the deck.");
                }
            }
            LoadedDeck = SI(LoadedDeck, split);
        } else if (strcasecmp("QQ", command) == 0) {
            QQ(0, 0);
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

