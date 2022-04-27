#ifndef YUKON_COMMANDS_H
#define YUKON_COMMANDS_H

#include "linkedlist.h"
#include "deck.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>

int LD();

int SW();

int SR();

int SD();

Linked_list * SI(Linked_list*, int);

void QQ(Linked_list *lists[], int numberOfLists);

#endif //YUKON_COMMANDS_H
