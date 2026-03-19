#include "logic.h"
#include "load_file_data.h"
#include <stdlib.h>

void runLoadDataTask(AppContext* context, const char* fileName) {
  if (context->list != NULL)
    disposeList(context->list);

  context->list = initLinkedList();
  context->totalRows = 0;
  context->errorRows = 0;
  context->programmStatus = STATUS_OK;

  if (!loadDemographyData(context, fileName))
    context->programmStatus = ERR_FILE_OPEN;
}

void runCalculateMetricsTask(AppContext* context, const char* region, int column) {
  context->metrix = calculateMetrix(context, region, column);
}
