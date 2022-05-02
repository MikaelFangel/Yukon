#ifndef YUKON_COMMANDS_H
#define YUKON_COMMANDS_H

#include "linkedlist.h"
#include "deck.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Linked_list *LD(char arg[], int numOfInputs);

Linked_list *SR(Linked_list *unshuffledPile);

void SD(Linked_list *list, char arg[]);

Linked_list *SI(Linked_list *, int);

Linked_list *P(Linked_list *);

#endif //YUKON_COMMANDS_H
