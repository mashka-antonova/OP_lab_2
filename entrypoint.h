#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

typedef enum {
    LOAD_DATA,
    CALCULATE_METRICS
} Operation;

typedef struct {
    const char* fileName; //
    const char* region;
    int column;
} AppParams;

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
