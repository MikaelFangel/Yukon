#include <stdio.h>
#include <stdbool.h>
#include "view.h"
#include "deck.h"
#include <string.h>

int main(void) {
    char input[256];
    char filepath[256];
    bool gameRunning = true;

    while (gameRunning) {
        generateView(true);
        scanf("%s %s", input, filepath);

        if (strcmp("LD", input) == 0) {
            // If filepath is not empty
            if (strcmp(filepath, "") != 0) {
                fillSuits();
                createDeck(filepath);
                printCommandConsole("LD", "");
            } else {
                printCommandConsole("LD", "The file does not exist");
            }
        } else {
            printCommandConsole("LD", "OK");
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

