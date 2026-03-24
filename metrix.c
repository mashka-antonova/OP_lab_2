#include "metrix.h"
#include "iterator.h"
#include <stdlib.h>
#include <string.h>
#include "appcontext.h"
#include "demography.h"

#define INIT_CAPACITY 10

double getValueByColumn(DemographicRecord* record, Column column) {
  double value = 0;
  switch (column) {
    case COL_YEAR:
      value = record->year;
      break;
    case COL_NPG:
      value = record->natural_population_growth;
      break;
    case COL_BIRTH_RATE:
      value = record->birth_rate;
      break;
    case COL_DEATH_RATE:
      value = record->death_rate;
      break;
    case COL_GDW:
      value = record->general_demographic_weight;
      break;
    case COL_URBANIZATION:
      value = record->urbanization;
      break;
    default:
      break;
  }
  return value;
}

int checkColumn(AppContext* context, Column column) {
  int isCorrect = 1;
  if (column < COL_YEAR || column > COL_URBANIZATION || column == COL_REGION) {
    context->programmStatus = ERR_INVALID_COLUMN;
    isCorrect = 0;
  }
  return isCorrect;
}

void updateMinMax(Metrix* metrix, double val, int n) {
  if (n == 0 || val < metrix->min)
    metrix->min = val;
  if (n == 0 || val > metrix->max)
    metrix->max = val;
}


double* collectData(AppContext* ctx, const char* region, Column col, int* n, Metrix* metrix) {
  int cap = INIT_CAPACITY;
  double* values = (double*)malloc(cap * sizeof(double));
  Iterator it = begin(ctx->list);
  while (values && hasNext(&it)) {
    DemographicRecord* record = (DemographicRecord*)get(&it);
    int cmp = strcmp(record->region, region);
    if (cmp == 0) {
      if (*n >= cap) {
        double* values = (double*)realloc(values, (cap *= 2) * sizeof(double));
        if (!values)
          break;
    }
    double val = getValueByColumn(record, col);
    values[*n] = val;
    updateMinMax(metrix, val, *n);
    (*n)++;
    }
  }
  return values;
}

int compareDoubles(const void* a, const void* b) {
  double d1 = *(const double*)a;
  double d2 = *(const double*)b;
  return (d1 > d2) - (d1 < d2);
}

Metrix calculateMetrix(AppContext* context, const char* region, Column column) {
  Metrix metrix = {0};
  int count = 0;
  double* vals = NULL;

  if (context && context->list && context->list->head && region && checkColumn(context, column)) {
    vals = collectData(context, region, column, &count, &metrix);
    if (count > 0 && vals) {
      qsort(vals, count, sizeof(double), compareDoubles);
      metrix.mediana = (count % 2 != 0) ? vals[count / 2] : (vals[count / 2 - 1] + vals[count / 2]) / 2.0;
    }
    else if (!vals)
      context->programmStatus = ERR_MALLOC_FAILED;
    else
      context->programmStatus = ERR_INVALID_REGION;
    free(vals);
  }

  return metrix;
}
