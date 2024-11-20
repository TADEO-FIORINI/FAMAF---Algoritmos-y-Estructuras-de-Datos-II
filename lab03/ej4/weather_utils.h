#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h" 

int minima_temp_historica(WeatherTable a);
    /*Retorna la minima temperatura historica de Cordoba entre 1980 y 2016*/

void max_temp_anual(WeatherTable a, int output[YEARS]);
    /*Retorna un arreglo con la maxima temperatura dee cada año en Cordoba entre 198 y 2016*/

void mes_max_prec_anual (WeatherTable a, month_t output[YEARS]);
    /*Retorna un arreglo con el mes de mas precipitaciones por año entre 1980 y 2016*/