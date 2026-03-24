#include "logic.h"
#include "load_file_data.h"
#include "demography.h"
#include <string.h>

int compareRecords(const void* a, const void* b) {
    const DemographicRecord* recA = (const DemographicRecord*)a;
    const DemographicRecord* recB = (const DemographicRecord*)b;
    int res = strcmp(recA->region, recB->region);
    if (res == 0)
      res = recA->year - recB->year;
    return res;
}

void runLoadDataTask(AppContext* context, const char* fileName) {
  if (context->list != NULL)
    clearList(context->list);

  *context = (AppContext){.list = initLinkedList(sizeof(DemographicRecord))};

  if (!loadDemographyData(context, fileName))
    context->programmStatus = ERR_FILE_OPEN;
}

void runCalculateMetricsTask(AppContext* context, const char* region, int column) {
  context->programmStatus = STATUS_OK;
  context->metrix = calculateMetrix(context, region, column);
}
