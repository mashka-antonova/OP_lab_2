#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "list.h"

#define MAX_ERROR_MSG 256

typedef struct {
    LinkedList list;
    int totalRows;
    int errorRows;
    char lastError[MAX_ERROR_MSG];
} AppContext;


void context_init(AppContext* ctx);

#endif // ENTRYPOINT_H
