#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x<0){
        *(&y) = -x;
    }
    else{
        *(&y) = x;
    } 
}

int main(void) {
    int a=-10, res=0;
    absolute(a,res);
    printf("The absolute value of %d is %d\n", a, res);
    return EXIT_SUCCESS;
}

/*
el resultado es el mismo que la variable cuando fue inicializada. 
una alternativa para almacenar valores generados dentro de una 
funcion es usando punteros.
*/