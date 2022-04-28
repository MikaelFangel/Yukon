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

void insertNode(Linked_list *list, Node *nodeToInsert, Node *previousNode, bool insertBefore) {
    Node *nodeCopy;
    nodeCopy = (Node *) malloc(sizeof(Node));

    nodeCopy->key = nodeToInsert->key;
    if (list->size == 0) {
        nodeCopy->next = NULL;
        nodeCopy->prev = NULL;

        list->tail = nodeCopy;
        list->head = nodeCopy;
    } else {
        if (insertBefore) {
            if (previousNode->next != NULL && previousNode->prev != NULL) {
                nodeCopy->next = previousNode;
                nodeCopy->prev = previousNode->prev;

                previousNode->prev->next = nodeCopy;
                previousNode->prev = nodeCopy;
            } else if (previousNode->prev == NULL) {
                nodeCopy->next = previousNode;
                nodeCopy->prev = NULL;
                previousNode->prev = nodeCopy;

                list->head = nodeCopy;
            } else if (previousNode->next == NULL) {
                nodeCopy->next = previousNode;
                nodeCopy->prev = previousNode->prev;

                previousNode->prev->next = nodeCopy;
                previousNode->prev = nodeCopy;
            }
        } else {
            if (previousNode->next != NULL && previousNode->prev != NULL) {
                nodeCopy->next = previousNode->next;
                nodeCopy->prev = previousNode;

                previousNode->next->prev = nodeCopy;
                previousNode->next = nodeCopy;
            } else if (previousNode->next == NULL) {
                nodeCopy->next = NULL;
                nodeCopy->prev = previousNode;
                previousNode->next = nodeCopy;

                list->tail = nodeCopy;
            } else if (previousNode->prev == NULL) {
                nodeCopy->next = previousNode->next;
                nodeCopy->prev = previousNode;

                previousNode->next->prev = nodeCopy;
                previousNode->next = nodeCopy;
            }
        }
    }

    list->size++;
}

void removeNode(Linked_list *list) {
    if (list->size == 0) {
        return;
    } else {
        Node *node = list->tail;
        if (node->prev != NULL) {
            Node *prevNode = node->prev;
            prevNode->next = NULL;
            list->tail = prevNode;
        }

        free(node);
        list->size--;
    }
}

void deleteLinkedList(Linked_list *list) {
    while (list->size > 0) {
        removeNode(list);
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