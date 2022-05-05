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
    appendCard(list, "1");
    appendCard(list, "2");
    appendCard(list, "3");
    appendCard(list, "4");
    appendCard(list, "5");
    appendCard(list, "6");
    appendCard(list, "7");
    appendCard(list, "8");
    appendCard(list, "9");
    appendCard(list, "10");

    if (strcmp(list->head->card, "1") != 0) {
        puts("linkedListAdd Error! Wrong node at head");
        status = false;
    }
    if (strcmp(list->tail->card, "10") != 0) {
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
    appendCard(list, "1");
    appendCard(list, "2");
    appendCard(list, "3");
    appendCard(list, "4");
    appendCard(list, "5");
    appendCard(list, "6");
    appendCard(list, &key);
    appendCard(list, "8");
    appendCard(list, "9");
    appendCard(list, "10");

    Node *result = findKey(list, &key);
    // void *result2 = findKey(list, &notFound);

    //printf("%c", *(char*) result->card);

    if (result->card != NULL && *(char*) result->card == '7')
        puts("findKeyTest: Test Passed!");
    else
        puts("findKeyTest Error!");
}

void moveToEmptyListTest() {
    FILE *fptr = fopen("../resources/default.txt", "r");
    Linked_list *loadedDeck = loadDeck(fptr);
    Linked_list *emptyLinkedList = createLinkedList();

    ListCard *key = (ListCard*) loadedDeck->head->card;

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
        ListCard *deckCard = (ListCard*) deckNode->card;
        ListCard *emptyCard = (ListCard*) emptyListNode->card;

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