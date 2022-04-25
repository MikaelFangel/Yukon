#include <stdio.h>
#include <stdbool.h>
#include "view.h"
#include "deck.h"
#include <string.h>

int main(void) {
//    Source: https://intellij-support.jetbrains.com/hc/en-us/community/posts/115000763330-Debugger-not-working-on-Windows-CLion-
#if defined(_WIN32) || defined(_WIN64)
    setbuf(stdout, 0);
#endif

    char input[256];
    char filepath[] = {"../resources/"};
    char filename[256];
    char buf[256];
    Linked_list *LoadedDeck;
    bool deckLoaded = false;
    bool startupPhase = true;
    bool gameRunning = true;
    generateEmptyView("", "");

    while (!deckLoaded) {
        fgets(buf, 256, stdin);
        int numOfInputs = sscanf(buf, "%s %s", input, filename);

        if (strcasecmp("LD", input) == 0) {
            // If filepath is not empty
            if (numOfInputs == 2) {
                strcat(filepath, filename);
                strcat(filepath, ".txt");

                FILE *file = fopen(filepath, "r");
                if (file != NULL) {
                    fillSuits();
                    LoadedDeck = loadDeck(file);
                    // DeckToString(&LoadedDeck);
                    // LinkedListToString(&test);
                    generateEmptyView("LD", "OK");
                    deckLoaded = true;
                    fclose(file);
                } else {
                    generateEmptyView("LD", "The file does not exist");
                }
            } else if (numOfInputs == 1) {
                //    TODO: Load an unsorted LoadedDeck!
            } else {
                generateEmptyView("", "Unexpected input. Try again.");
            }
        } else {
            generateEmptyView("", "Error! The only valid command is LD");
        }
    }

    // Startup Phase
    while (startupPhase) {
        fgets(buf, 256, stdin);
        // filepath = ../resources/default.txt
        int numOfInputs = sscanf(buf, "%s %s", input, filepath);

        if (strcasecmp("SW", input) == 0) {
            showDeck(LoadedDeck, true);
        }

        startupPhase = false;
    }

    // Play Phase
    // TODO: Implement
    while (gameRunning) {

        gameRunning = false;
    }

    return 0;

}


/*fillSuits(NULL);

for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; ++j) {
        printf("%c ", deck[i][j].value);
    }
}*/

