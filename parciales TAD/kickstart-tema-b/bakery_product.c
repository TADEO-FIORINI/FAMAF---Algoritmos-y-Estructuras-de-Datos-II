/*
  @file bakery_product.c
  @brief Implements bakery product structure and methods
*/
#include <stdlib.h>
#include "bakery_product.h"

static const int AMOUNT_OF_PRODUCT_VARS = 7;

BakeryProduct bakery_product_from_file(FILE* file)
{
    BakeryProduct product;

    int res = fscanf(file, EXPECTED_PRODUCT_FILE_FORMAT, &product.sale_value, &product.yeast_cant, &product.yeast_price ,&product.butter_cant, &product.butter_price,
     &product.flour_cant, &product.flour_price);
    if (res != AMOUNT_OF_PRODUCT_VARS){
        fprintf(stderr, "Invalid array");
        exit(EXIT_FAILURE);
    }
    return product;
}

/*
  unsigned int flour_cant;
  unsigned int flour_price;
  unsigned int yeast_cant;
  unsigned int yeast_price;
  unsigned int butter_cant;
  unsigned int butter_price;
  unsigned int sale_value;

Weather weather_from_file(FILE* file)
{
    Weather weather;
    Completar aqui

    int res = fscanf(file, EXPECTED_WEATHER_FILE_FORMAT, &weather._average_temp, &weather._max_temp,
            &weather._min_temp, &weather._pressure, &weather._moisture, &weather._rainfall);
   
    if (res != AMOUNT_OF_WEATHER_VARS) {
        fprintf(stderr, "Invalid array");
        exit(EXIT_FAILURE);
    }
    return weather;
}
*/