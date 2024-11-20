#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "weather_utils.h"

int minima_temp_historica(WeatherTable a){
    int minima = INT_MAX;
    for (int year=0; year<YEARS; year++){
        for (month_t month=january; month<=december; month++){
            for (int day=0; day<DAYS; day++){
                if (a[year][month][day]._min_temp < minima){
                    minima = a[year][month][day]._min_temp;
                }
            }
        }
    }
    return minima;
}

void max_temp_anual(WeatherTable a, int output[YEARS]){
    int maxima;
    for (int year=0; year<YEARS; year++){
        maxima = INT_MIN;
        for (month_t month=january; month<=december; month++){
            for (int day=0; day<DAYS; day++){
                if (maxima < a[year][month][day]._max_temp){
                    maxima = a[year][month][day]._max_temp;
                }
            }
        }
        output[year] = maxima;
    }
}

void mes_max_prec_anual(WeatherTable a, month_t output[YEARS]){
    int prom_prec_mensual;
    struct Dato{
        int prec;
        month_t month;
    };
    struct Dato dato; 
    dato.prec = INT_MIN;
    for (int year=0; year<YEARS; year++){
        prom_prec_mensual = 0;
        for (month_t month=january; month<=december; month++){
            for (int day=0; day<DAYS; day++){
                prom_prec_mensual = prom_prec_mensual + a[year][month][day]._rainfall;
                }   
            prom_prec_mensual = prom_prec_mensual / DAYS;
            if (dato.prec < prom_prec_mensual){
                dato.prec = prom_prec_mensual;
                dato.month = month;
            }
        }
        output[year] = dato.month;
    }
}