#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "deck.h"
#include "linkedlist.h"

void generateEmptyView(char lastCommand[], char message[]);
void showDeck(Linked_list *deck_list, char command[], char statusMessage[]);
void generateColumns();
void clearView();
void printCommandConsole(char lastCommand[], char message[]);
void makePlayView(Linked_list *C1, Linked_list *C2, Linked_list *C3, Linked_list *C4, Linked_list *C5,
                  Linked_list *C6, Linked_list *C7, Linked_list *F1, Linked_list *F2, Linked_list *F3,
                  Linked_list *F4, char lastCommand[], char message[]);

#endif