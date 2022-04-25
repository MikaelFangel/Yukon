#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "linkedlist.h"

void generateEmptyView(char lastCommand[], char message[]);
int showDeck(Linked_list *deck_list, bool faceUp);
int generateColumns();
void clearView();
int printCommandConsole(char lastCommand[], char message[]);

#endif