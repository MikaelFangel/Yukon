#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "linkedlist.h"

int generateEmptyView(char lastCommand[], char message[]);
int generateView(Linked_list *deck_list);
int generateColumns();
void clearView();
int printCommandConsole(char lastCommand[], char message[]);

#endif