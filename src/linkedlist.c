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
        list->tail->next = newNode;
        newNode->next = NULL;
        list->tail = newNode;
    }

    list->size++;
}

void removeNode(Linked_list *list) {
    if (list->size == 0) {
        return;
    } else {
        Node tempNode = *(Node *) list->tail->prev;
        tempNode.next = NULL;
        if(list->tail->key != NULL)
            free(list->tail->key);
        free(list->tail);

        list->tail = &tempNode;
        list->size--;
    }
}

void deleteLinkedList(Linked_list *list) {
    if (list->size > 0) {
        Node *node = list->head;
        while (node != NULL) {
            Node *tempNode = node;
            node = node->next;
            if(tempNode->key != NULL)
                free(tempNode->key);
            free(tempNode);
        }
    }

    free(list);
}

void *findKey(Linked_list *list, void *key) {
    Node *node = list->head;
    while (node != NULL && node->key != key) {
        node = node->next;
    }

    return node;
}

void moveKeyFromOneLinkedListToAnother(Linked_list *from, void *keyFrom, Linked_list *to, void *keyTo) {

}

void LinkedListToString(Linked_list *list) {
    Node *node = list->head;
    while (node != NULL) {
        printf("%c\n", *(char *) node->key);
        node = node->next;
    }
}