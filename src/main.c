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
    char filepath[256];
    bool gameRunning = true;
    generateEmptyView("", "");

    Linked_list *list = loadDeck("../Resources/deck.txt");

    while (gameRunning) {
        scanf("%s %s", input, filepath);

        if (strcmp("SW", input) == 0) {
            generateView(list);
        }

        if (strcmp("LD", input) == 0) {
            // If filepath is not empty
            if (strcmp(filepath, "") != 0) {
                fillSuits();
                // Linked_list test = loadDeck(filepath);
                // DeckToString(&test);
                //LinkedListToString(&test);
                printCommandConsole("LD", "");
            } else {
                printCommandConsole("LD", "The file does not exist");
            }
        }

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

