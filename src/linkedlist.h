#ifndef YUKON_LINKEDLIST_H
#define YUKON_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    void *key;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Linked_list;

Linked_list *createLinkedList();

void *findKey(Linked_list *list, void *key);

void addNode(Linked_list *list, void *key);

void insertNode(Linked_list *list, Node *nodeToInsert, Node *previousNode, bool insertBefore);

void removeNode(Linked_list *list);

void deleteLinkedList(Linked_list *list);

void LinkedListToString(Linked_list *list);

#endif //YUKON_LINKEDLIST_H
