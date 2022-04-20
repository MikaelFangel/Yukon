#ifndef YUKON_LINKEDLIST_H
#define YUKON_LINKEDLIST_H

#include <stdlib.h>

typedef struct {
    void *key;
    void *next;
    void *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Linked_list;

Linked_list *createLinkedList();

void addNode(Linked_list *list, void *key);
void removeNode(Linked_list *list);
void deleteLinkedList(Linked_list *list);

#endif //YUKON_LINKEDLIST_H
