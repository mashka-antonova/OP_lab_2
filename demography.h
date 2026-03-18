#ifndef DEMOGRAPHY_C
#define DEMOGRAPHY_C

#define MAX_REGION_NAME 128

typedef struct {

    int year;
    char region[MAX_REGION_NAME];
    double natural_population_growth;
    double birth_rate;
    double death_rate;
    double general_demographic_weight;
    double urbanization;

} DemographicRecord;

#endif // DEMOGRAPHY_C
