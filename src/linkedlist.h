#ifndef YUKON_LINKEDLIST_H
#define YUKON_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Structs start here */
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

/** Methods start here */
Linked_list *createLinkedList();

Node *findKey(Linked_list *list, void *key);

void appendNode(Linked_list *list, void *key);

void insertNode(Linked_list *list, Node *nodeToInsert, Node *previousNode, bool insertBefore);

void removeNode(Linked_list *list);

void deleteLinkedList(Linked_list *list);

void LinkedListToString(Linked_list *list);

Node *findNodeFromCard(Linked_list *list, char value, char suit);

bool moveKeyFromOneLinkedListToAnother(Linked_list *from, void *keyFrom, Linked_list *to);

bool moveNodeFromOneLinkedListToAnother(Linked_list *from, Node *node, Linked_list *to);

#endif //YUKON_LINKEDLIST_H
