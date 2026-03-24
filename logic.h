#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

int compareRecords(const void* a, const void* b); //
void runLoadDataTask(AppContext* context, const char* fileName);
void runCalculateMetricsTask(AppContext* context, const char* region, Column column); //

#endif // LOGIC_H
