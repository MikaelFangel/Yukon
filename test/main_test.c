#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../src/commands.h"
#include "../src/linkedlist.h"

void linkedListAdd();

void findKeyTest();

void QQTest();

int main(void) {
    linkedListAdd();
    findKeyTest();

    // Need to be last because it ends the game.
    QQTest();

    return 0;
}

void linkedListAdd() {
    bool status = true;

    Linked_list *list = createLinkedList();
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

    if (strcmp(list->head->key, "1") != 0) {
        puts("linkedListAdd Error! Wrong node at head");
        status = false;
    }
    if (strcmp(list->tail->key, "10") != 0) {
        puts("linkedListAdd Error! Wrong node at tail");
        status = false;
    }
    if (list->size != 10) {
        puts("linkedListAdd Error! Wrong size of list");
        status = false;
    }

    if (status == true) {
        puts("linkedListAdd: Test Passed!");
    }

    deleteLinkedList(list);
}

void findKeyTest() {
    char key = '7';
    char notFound = '9';

    Linked_list *list = createLinkedList();
    addNode(list, "1");
    addNode(list, "2");
    addNode(list, "3");
    addNode(list, "4");
    addNode(list, "5");
    addNode(list, "6");
    addNode(list, &key);
    addNode(list, "8");
    addNode(list, "9");
    addNode(list, "10");

    Node *result = findKey(list, &key);
    // void *result2 = findKey(list, &notFound);

    //printf("%c", *(char*) result->key);

    if (result->key != NULL && *(char*) result->key == '7')
        puts("findKeyTest: Test Passed!");
    else
        puts("findKeyTest Error!");
}

void QQTest() {
    Linked_list *list1 = createLinkedList();
    Linked_list *list2 = createLinkedList();
    Linked_list *list3 = createLinkedList();

    addNode(list1, "1");
    addNode(list2, "2");
    addNode(list2, "3");
    addNode(list3, "4");

    Linked_list *columns[3] = {list1, list2, list3};

    QQ(columns, 3);
}