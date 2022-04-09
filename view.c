#include "view.h"

int generateView(bool isEmpty) {
    clearView();
    generateColumns();

    if(isEmpty) {
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < 8; ++j) {
                printf("\t");
            }
            printf("[]\tF%d\n", i);
        }
        printCommandConsole("", "");
    }

    return 0;
}

int generateColumns() {
    for (int i = 1; i <= 7; ++i) {
        printf("C%d\t", i);
    }
    printf("\n\n");
    return 0;
}

int printCommandConsole(char lastCommand[], char message[]) {
    printf("LAST Command: %s \n", lastCommand);
    printf("Message: %s \n", message);
    printf("INPUT > ");

    return 0;
}

int clearView() {
    system("clear");
    return 0;
}