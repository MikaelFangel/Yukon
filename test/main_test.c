#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../src/commands.h"
#include "../src/linkedlist.h"

void linkedListAdd();

void findCardTest();

void moveToEmptyListTest();

int main(void) {
    linkedListAdd();
    findCardTest();
    moveToEmptyListTest();

    return 0;
}

void linkedListAdd() {
    bool status = true;

    Linked_list *list = createLinkedList();
    struct ListCard card;
    card.value = 'A';
    card.suit = 'C';
    card.faceDown = true;
    card.existsInGame = true;
    appendCard(list, card);

    card.value = '2';
    appendCard(list, card);

    for (int i = ('2' + 1); i <= '9'; ++i) {
        card.value = i;
        appendCard(list, card);
    }

    if (list->head->value != 'A' && list->head->suit != 'C') {
        puts("linkedListAdd Error! Wrong node at head");
        status = false;
    }
    if (list->tail->value != '9' && list->tail->suit != 'C') {
        puts("linkedListAdd Error! Wrong node at tail");
        status = false;
    }
    if (list->size != 9) {
        puts("linkedListAdd Error! Wrong size of list");
        status = false;
    }

    if (status == true) {
        puts("linkedListAdd: Test Passed!");
    }

    deleteLinkedList(list);
}

void findCardTest() {
    Linked_list *list = createLinkedList();
    struct ListCard card;
    card.value = 'A';
    card.suit = 'C';
    card.faceDown = true;
    card.existsInGame = true;
    appendCard(list, card);

    card.value = '2';
    appendCard(list, card);

    for (int i = ('2' + 1); i <= '9'; ++i) {
        card.value = i;
        appendCard(list, card);
    }

    struct ListCard *result = findNodeFromCard(list, '9', 'C');
    struct ListCard *result2 = findNodeFromCard(list, 'A', 'C');
    struct ListCard *result3 = findNodeFromCard(list, '5', 'C');
    struct ListCard *notFound = findNodeFromCard(list, '3', 'S');

    if (result != NULL && result->value == '9' &&
    result2 != NULL && result2->value == 'A' &&
    result3 != NULL && result3->value == '5' &&
    notFound == NULL)
        puts("findCardTest: Test Passed!");
    else
        puts("findCardTest Error!");
}


void moveToEmptyListTest() {
    FILE *fptr = fopen("../resources/default.txt", "r");
    Linked_list *loadedDeck = loadDeck(fptr);
    Linked_list *emptyLinkedList = createLinkedList();

    struct ListCard *key = loadedDeck->head;

    moveCardFromOneLinkedListToAnother(loadedDeck, key, emptyLinkedList);

    if(loadedDeck->size == 0 && emptyLinkedList->size == 52) {
        puts("moveToEmptyListTest: Size Test Passed!");
    } else {
        puts("moveToEmptyListTest ERROR! Size Test Failed");
    }

    loadedDeck = loadDeck(fptr);

    struct ListCard *deckNode = loadedDeck->head;
    struct ListCard *emptyListNode = emptyLinkedList->head;

    bool error = false;

    while(deckNode != NULL && emptyListNode != NULL) {
        struct ListCard *deckCard =  deckNode;
        struct ListCard *emptyCard = emptyListNode;

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