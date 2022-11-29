#ifndef COMMANDS_H
#define COMMANDS_H

#include "stack.h"
#include "list.h"

int compare(const void*, const void*);

link a(link, tSTACK, int);
void A(tSTACK, int);
void l(link, int);
void p(int);
void P(link, tSTACK, int);
link r(link, int);
void s(int);
void g(link, tSTACK, int);
link x(link, tSTACK);

#endif