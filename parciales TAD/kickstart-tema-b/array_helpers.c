/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "array_helpers.h"
static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES [CITIES] = {
  "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"
};
static const char* SEASON_NAMES [SEASONS] = {"Low", "High" };


/**
* @brief returns true when reach last line in products file
* @return True when is the last line of the file, False otherwise
*/
/*static bool is_last_line(unsigned int city) {
  return city == CITIES - 1u;
}*/

void array_dump(BakeryProductTable a) {
  for (unsigned int city = 0u; city < CITIES; ++city) {
    for(unsigned int season = 0u; season < SEASONS; ++season){
      fprintf(stdout, "%s in season %s: Sales value %u flour (%u,%u) Butter (%u,%u)  Yeast (%u,%u)  ",
        CITY_NAMES[city], SEASON_NAMES[season],a[city][season].sale_value ,a[city][season].flour_cant, 
        a[city][season].flour_price, a[city][season].butter_cant,
        a[city][season].butter_price,  a[city][season].yeast_cant,
        a[city][season].yeast_price);
      fprintf(stdout, "\n");   
    }
  }
}

unsigned int worst_profit(BakeryProductTable a) {
  unsigned int worst_earnings = INT_MAX, collected, investment, earnings;
  
  for (unsigned int city = 0u; city < CITIES; city++){
    for (unsigned int season = 0u; season < SEASONS; season++){
       collected = a[city][season].sale_value;
       investment = a[city][season].flour_cant * a[city][season].flour_price 
          + a[city][season].yeast_cant * a[city][season].yeast_price 
          + a[city][season].butter_cant * a[city][season].butter_price;
        earnings = collected - investment;
        if (earnings < worst_earnings){
          worst_earnings = earnings;
        }
    }
  }
    return worst_earnings;
  }

void array_from_file(BakeryProductTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }
  // here your code!!!
   int city = 0;
   int season = 0;
  while(!feof(file)){
    int res = fscanf(file, "##%d??%d", &city, &season);
    
    if (res != EXPECTED_DIM_VALUE){
        fprintf(stderr, "Invalid array.\n");
        exit(EXIT_FAILURE);
    }
    BakeryProduct product = bakery_product_from_file(file);
    array[city][season] = product;


  }

  fclose(file);
}

/*


 unsigned int k_year = 0u;
    unsigned int k_month = 0u;
    unsigned int k_day = 0u;
    while (!feof(file)) {
        int res = fscanf(file, " %u %u %u ", &k_year, &k_month, &k_day);
        if (res != 3) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        Weather weather = weather_from_file(file);
        Completar acá: Guardar la medición de clima en el arreglo multidimensional 
        array[k_year-FST_YEAR][k_month-1][k_day-1]._average_temp = weather._average_temp;
        array[k_year-FST_YEAR][k_month-1][k_day-1]._max_temp = weather._max_temp;
        array[k_year-FST_YEAR][k_month-1][k_day-1]._min_temp = weather._min_temp;
        array[k_year-FST_YEAR][k_month-1][k_day-1]._pressure = weather._pressure;
        array[k_year-FST_YEAR][k_month-1][k_day-1]._moisture = weather._moisture;
        array[k_year-FST_YEAR][k_month-1][k_day-1]._rainfall = weather._rainfall;  
    }
    fclose(file);
}
*/