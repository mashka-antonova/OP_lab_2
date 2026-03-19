#include "entrypoint.h"
#include "logic.h"

void doOperation(Operation operation, AppContext* context, AppParams* params) {
  switch (operation) {
    case LOAD_DATA:
      runLoadDataTask(context, params->fileName);
      break;

    case CALCULATE_METRICS:
      runCalculateMetricsTask(context, params->region, params->column);
      break;
  }
}
