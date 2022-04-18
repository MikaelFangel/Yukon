#include <stdio.h>
#include "linkedlist.h"

Linked_list *createLinkedList() {
    Linked_list *newLinkedList;
    newLinkedList = (Linked_list *) malloc(sizeof(Linked_list));

    newLinkedList->size = 0;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;

    return newLinkedList;
}

void addNode(Linked_list *list, void *key) {
    Node *newNode;
    newNode = (Node *) malloc(sizeof(Node));

    if (list->size == 0) {
        newNode->key = key;
        newNode->next = NULL;
        newNode->prev = NULL;

        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->key = key;
        newNode->prev = list->tail;
        newNode->next = NULL;
        list->tail = newNode;
    }

    list->size++;
}

void removeNode(Linked_list *list) {
    if(list->size == 0) {
        return;
    } else {
        Node tempNode = *(Node *) list->tail->prev;
        tempNode.next = NULL;
        free(list->tail);

        list->tail = &tempNode;
        list->size--;
    }
}

void toString(Linked_list *list) {
    /*void *node = head;
    while (node != NULL) {
        printf("%s", *node.);
        node = node.next;
    }*/
}