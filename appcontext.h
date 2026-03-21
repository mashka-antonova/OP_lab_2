#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"
#include "metrix.h"

typedef enum {
    STATUS_OK,
    ERR_FILE_OPEN,
    ERR_INVALID_HEADER,
    ERR_MALLOC_FAILED,
    ERR_EMPTY_DATA,
    ERR_INVALID_REGION,
    ERR_INVALID_COLUMN,
} Status;

typedef struct AppContext {
    LinkedList* list;
    int totalRows;
    int errorRows;
    Status programmStatus;
    Metrix metrix;
} AppContext;

#endif // APPCONTEXT_H
