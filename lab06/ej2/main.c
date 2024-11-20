#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX_LENGTH 100
int main() {
    bool exit = false;
    while(!exit){
        printf("****COMPARAR DOS CADENAS****\n");
        printf("\n1. Ver ejemplo generico");
        printf("\n2. Escribir cadenas");
        printf("\n\nSeleccionar una opcion: ");
        unsigned int select; 
        scanf("%u",&select);
        string str1;
        string str2;
        if (select == 1){
            str1 = string_create("computacion");
            str2 = string_create("computadora");
        }
        else if (select == 2){
            char string1[MAX_LENGTH];
            char string2[MAX_LENGTH];
            printf("\n\nIngresa la primer cadena: ");
            scanf("%s", string1);
            printf("\nIngresa la segunda cadena: ");
            scanf("%s", string2);
            str1 = string_create(string1);
            str2 = string_create(string2);
        }
        else{
            return EXIT_FAILURE;
        }
        // Comparar las cadenas utilizando string_less()
        printf("\n\nComparar las cadenas utilizando string_less()\n");
        bool isLess = string_less(str1, str2);
        if (isLess) {
            printf("%s es alfabeticamente menor que %s\n", string_ref(str1), string_ref(str2));
        }
        else {
            printf("%s NO es alfabeticamente menor que %s\n", string_ref(str1), string_ref(str2));
        }
        printf("\n\n");
        // Comparar las cadenas utilizando string_eq()
        printf("Comparar las cadenas utilizando string_eq()\n");
        if (string_eq(str1, str2)) {
            printf("%s es igual que %s\n", string_ref(str1), string_ref(str2));
        }
        else {
            printf("%s es distinta de %s\n", string_ref(str1), string_ref(str2));
        }
        // Liberar memoria de las cadenas
        string_destroy(str1);
        string_destroy(str2);

        printf("\n\n¿Quiere continuar en el programa?\n1. Si\n0. No\n");
        printf("\nSeleccionar una opcion: ");
        scanf("%u", &select);
        if (select == 0){
            exit = true;
        }
    }
    return EXIT_SUCCESS;
}
