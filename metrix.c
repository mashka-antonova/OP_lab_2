#include "metrix.h"
#include "iterator.h"
#include <stdlib.h>
#include <string.h>
#include "appcontext.h"
#include "demography.h"

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


int compareDoubles(const void* a, const void* b) {
    double d1 = *(const double*)a;
    double d2 = *(const double*)b;
    return (d1 > d2) - (d1 < d2);
}

void startRegionIterator(Iterator* it, const char* region) {
  while (hasNext(it) && strcmp(((DemographicRecord*)get(it))->region, region) < 0)
    next(it);
}

int countRegionRecords(Iterator* it, const char* region) {
  int count = 0;
  while (hasNext(it) && strcmp(((DemographicRecord*)get(it))->region, region) == 0) {
    count++;
    next(it);
  }
  return count;
}

double* getSortedColumnValues(Iterator* startIt, int count, Column column) {
  double* values = (double*)malloc(count * sizeof(double));
  if (values != NULL) {
    for (int i = 0; i < count; i++) {
      values[i] = getValueByColumn((DemographicRecord*)get(startIt), column);
      next(startIt);
    }
    qsort(values, count, sizeof(double), compareDoubles);
  }
  return values;
}

int checkColumn(AppContext* context, Column column) {
  int isCorrect = 1;
  if (column < COL_YEAR || column > COL_URBANIZATION || column == COL_REGION) {
    context->programmStatus = ERR_INVALID_COLUMN;
    isCorrect = 0;
  }
  return isCorrect;
}

Metrix calculateMetrix(AppContext* context, const char* region, Column column) {
  Metrix metrix = {0, 0, 0, 0};
  if (context != NULL && context->list != NULL && context->list->head != NULL
      && region != NULL && checkColumn(context, column)) {

    Iterator it = begin(context->list);
    startRegionIterator(&it, region);
    Iterator startIt = it;
    int count = countRegionRecords(&it, region);

    if (count > 0) {
      double* values = getSortedColumnValues(&startIt, count, column);
      if (values != NULL) {
        metrix.min = values[0];
        metrix.max = values[count - 1];
        metrix.mediana = (count % 2 != 0) ? values[count / 2] : (values[count / 2 - 1] + values[count / 2]) / 2.0;
        metrix.count = count;
        free(values);
      }
    } else {
        context->programmStatus = ERR_INVALID_REGION;
    }
  }
  return metrix;
}
