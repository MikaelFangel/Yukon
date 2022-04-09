#include <stdio.h>
#include <stdbool.h>
#include "view.h"
#include "deck.h"
#include "linkedlist.h"

int main(void) {
    char input[256];
    char filename[256];
    bool gameRunning = true;

    while(gameRunning) {
        generateView(true);
        scanf("%s %s", input, filename);

        gameRunning = false;
    }

    fillSuits(NULL);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; ++j) {
            printf("%c ", deck[i][j].value);
        }
    }

    return 0;
}
