#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"

#define MAX_ERROR_MSG 256

typedef struct {
    LinkedList* list;
    int totalRows;
    int errorRows;
    char lastError[MAX_ERROR_MSG];
} AppContext;

#endif // APPCONTEXT_H
