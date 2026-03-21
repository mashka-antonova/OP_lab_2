#include "metrix.h"
#include "iterator.h"
#include <stdlib.h>
#include <string.h>
#include "appcontext.h"

double getValueByColumn(DemographicRecord* record, int column) {
  double value = 0;
  switch (column) {
    case 1: value = record->year;
      break;
    case 3: value = record->natural_population_growth;
      break;
    case 4: value = record->birth_rate;
      break;
    case 5: value = record->death_rate;
      break;
    case 6: value = record->general_demographic_weight;
      break;
    case 7: value = record->urbanization;
      break;

    default: value = 0;
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
  while (hasNext(it) && strcmp(get(it)->region, region) < 0)
    next(it);
}

int countRegionRecords(Iterator* it, const char* region) {
  int count = 0;
  while (hasNext(it) && strcmp(get(it)->region, region) == 0) {
    count++;
    next(it);
  }
  return count;
}

double* getSortedColumnValues(Iterator* startIt, int count, int column) {
  double* values = (double*)malloc(count * sizeof(double));
  if (values != NULL) {
    for (int i = 0; i < count; i++) {
      values[i] = getValueByColumn(get(startIt), column);
      next(startIt);
    }
    qsort(values, count, sizeof(double), compareDoubles);
  }
  return values;
}

Metrix calculateMetrix(AppContext* context, const char* region, int column) {
  Metrix metrix = {0, 0, 0, 0};
  if (context != NULL && context->list != NULL && context->list->head != NULL && region != NULL) {

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
    }
  }
  return metrix;
}
