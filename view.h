#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int generateView(bool isEmpty);
int generateColumns();
int clearView();
int printCommandConsole(char lastCommand[], char message[]);

#endif