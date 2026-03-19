#ifndef METRIX_H
#define METRIX_H

typedef struct AppContext AppContext;

typedef struct {
    double min;
    double max;
    double mediana;
    int count;
} Metrix;

Metrix calculateMetrix(AppContext* context, const char* region, int columnIndex);

#endif // METRIX_H
