#ifndef METRIX_H
#define METRIX_H

#include "appcontext.h"

typedef struct {
    double min;
    double max;
    double mediana;
    int count;
} Metrix;

Metrix calculateMetrix(AppContext* context, const char* region, int columnIndex);

#endif // METRIX_H
