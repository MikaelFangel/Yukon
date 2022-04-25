#include "commands.h"

int LD() {
    return 0;
}

void QQ(Linked_list *lists[], int numberOfLists) {
    for (int i = 0; i < numberOfLists; i++) {
        deleteLinkedList(lists[i]);
    }

    puts("Ending Yukon...");
    exit(0);
}
