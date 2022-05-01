#include "linkedlist.h"

/**
 * Creates an empty linked list and return a pointer to the list.
 * @return pointer to newly created linked list
 */
Linked_list *createLinkedList() {
    Linked_list *newLinkedList;
    newLinkedList = (Linked_list *) malloc(sizeof(Linked_list));

    newLinkedList->size = 0;
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;

    return newLinkedList;
}

/**
 * Add a new node to the end of and existing list based on the key pointer.
 * @param list list to add new node to
 * @param key key to add as node to the list
 */
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

/**
 * Inserts a node in an existing linked list either before of after another specified node in the list.
 * @param list list to perform insert on
 * @param nodeToInsert node to added to linked list
 * @param previousNode node before the node to insert
 * @param insertBefore should the node be insert before or after
 */
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

/**
 * Removes a node of the end of the list.
 * @param list list to remove node from
 */
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

/**
 * Delete an entire linked list and all of its nodes using the remove node function
 * @param list list to the delete
 */
void deleteLinkedList(Linked_list *list) {
    while (list->size > 0) {
        removeNode(list);
    }

    free(list);
}

/**
 * Finds a node in a linked list based on the key value
 * @param list list to search
 * @param key key to find
 * @return the node in the linked list if found and NULL if node is not in the list
 */
Node *findKey(Linked_list *list, void *key) {
    Node *node = list->head;
    while (node != NULL && node->key != key) {
        node = node->next;
    }

    return node;
}

/**
 * Moves a key from anywhere in a linked list to the end of another
 * @param from list to move from
 * @param keyFrom key to move
 * @param to list to move to
 * @return true if successful and fall if unsuccessful
 */
bool moveKeyFromOneLinkedListToAnother(Linked_list *from, void *keyFrom, Linked_list *to) {
    // Finds the node corresponding to the key, so it can be detached from the linked list and added to the other
    bool result = false;
    Node *node = findKey(from, keyFrom);
    Node *prevNode = to->tail;

    // Checks how many nodes that are going to be moved so that we can calculate the new list size
    int nodesMoved = 0;
    Node *lastMovedNode = node;
    while (lastMovedNode != NULL) {
        nodesMoved++;
        lastMovedNode = lastMovedNode->next;
    }

    // Ends function if not found and to allow error handling
    if(node != NULL) {
        // Detach node from its list
        if (node->prev != NULL)
            node->prev->next = NULL;

        from->tail = node->prev;
        from->size = from->size - nodesMoved;

        // Linking
        node->prev = prevNode;
        if(prevNode != NULL) {
            prevNode->next = node;
        } else {
            to->head = prevNode;
        }

        to->tail = lastMovedNode;
        to->size = to->size + nodesMoved;

        result = true;
    }

    return result;
}

void LinkedListToString(Linked_list *list) {
    Node *node = list->head;
    while (node != NULL) {
        printf("%c\n", *(char *) node->key);
        node = node->next;
    }
}