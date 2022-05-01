#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../src/commands.h"
#include "../src/linkedlist.h"

void linkedListAdd();

void findKeyTest();

void moveToEmptyListTest();

int main(void) {
    linkedListAdd();
    findKeyTest();
    moveToEmptyListTest();

    return 0;
}

void linkedListAdd() {
    bool status = true;

    Linked_list *list = createLinkedList();
    appendNode(list, "1");
    appendNode(list, "2");
    appendNode(list, "3");
    appendNode(list, "4");
    appendNode(list, "5");
    appendNode(list, "6");
    appendNode(list, "7");
    appendNode(list, "8");
    appendNode(list, "9");
    appendNode(list, "10");

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
    appendNode(list, "1");
    appendNode(list, "2");
    appendNode(list, "3");
    appendNode(list, "4");
    appendNode(list, "5");
    appendNode(list, "6");
    appendNode(list, &key);
    appendNode(list, "8");
    appendNode(list, "9");
    appendNode(list, "10");

    Node *result = findKey(list, &key);
    // void *result2 = findKey(list, &notFound);

    //printf("%c", *(char*) result->key);

    if (result->key != NULL && *(char*) result->key == '7')
        puts("findKeyTest: Test Passed!");
    else
        puts("findKeyTest Error!");
}

void moveToEmptyListTest() {
    FILE *fptr = fopen("../resources/default.txt", "r");
    Linked_list *loadedDeck = loadDeck(fptr);
    Linked_list *emptyLinkedList = createLinkedList();

    Card *key = (Card*) loadedDeck->head->key;

    moveKeyFromOneLinkedListToAnother(loadedDeck, key, emptyLinkedList);

    if(loadedDeck->size == 0 && emptyLinkedList->size == 52) {
        puts("moveToEmptyListTest: Size Test Passed!");
    } else {
        puts("moveToEmptyListTest ERROR! Size Test Failed");
    }

    loadedDeck = loadDeck(fptr);

    Node *deckNode = loadedDeck->head;
    Node *emptyListNode = emptyLinkedList->head;

    bool error = false;

    while(deckNode != NULL && emptyListNode != NULL) {
        Card *deckCard = (Card*) deckNode->key;
        Card *emptyCard = (Card*) emptyListNode->key;

        if(deckCard->value != emptyCard->value || deckCard->suit != emptyCard->suit) {
            error = true;
            break;
        }

        deckNode = deckNode->next;
        emptyListNode = emptyListNode->next;
    }

    if(error) {
        puts("moveToEmptyListTest ERROR! Consistency Test Failed");
    } else {
        puts("moveToEmptyListTest: Consistency Test Passed!");
    }

    fclose(fptr);
}