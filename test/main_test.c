#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../src/linkedlist.h"

void linkedListAdd();

int main(void) {
    linkedListAdd();

    return 0;
}

void linkedListAdd() {
    bool status = true;

    Linked_list * list = createLinkedList();
    addNode(list, "1");
    addNode(list, "2");
    addNode(list, "3");
    addNode(list, "4");
    addNode(list, "5");
    addNode(list, "6");
    addNode(list, "7");
    addNode(list, "8");
    addNode(list, "9");
    addNode(list, "10");

    if(strcmp(list->head->key, "1") != 0) {
        printf("linkedListAdd Error! Wrong node at head");
        status = false;
    }
    if(strcmp(list->tail->key, "10") != 0) {
        printf("linkedListAdd Error! Wrong node at tail");
        status = false;
    }
    if(list->size != 10) {
        printf("linkedListAdd Error! Wrong size of list");
        status = false;
    }

    if(status == true) {
        puts("linkedListAdd: Test Passed!");
    }
}