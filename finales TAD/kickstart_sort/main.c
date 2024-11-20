#include <stdio.h>
#include <stdlib.h>
#include "sorted_list.h"

int main()
{
    bool quit = false;
    sorted_list_t list = sorted_list_empty();
    while (!quit){
        printf("Lista actual: ");
        sorted_list_print(list);
        printf("\nTamaño lista actual: %u",sorted_list_length(list));
        printf("\n1)Agregar\n2)head\n3)index\n4)tail\n5)take\n6)drop\n0)quit");
        int select;
        printf("\n\nSeleccionar una opcion: ");
        scanf("%d",&select);
        if (select==1){
            elem_t elem;
            printf("Selecciona un elemnto: ");
            scanf("%d",&elem);
            list = sorted_list_append(list,elem);
        }
        else if (select==2){
            if (!sorted_list_is_empty(list)){
                printf("\nhead es %d",sorted_list_head(list));
            }
            else{
                printf("\nlista vacia!");
            }
        }
        else if (select==3){
            printf("\nSelecciona una posicion: ");
            unsigned int index;
            scanf("%u",&index);
            if (index < sorted_list_length(list)){
                printf("\nEl elemento de la posicion %u es %d\n\n",index,sorted_list_elem_at(list,index));
            }
            else{
                printf("\nindice fuera de rango!");
            }
        }
        else if (select==4){
            list = sorted_list_tail(list);
        }
        else if (select==5){
            printf("\nSeleccionar cuantos elementos se quieren tomar: ");
            unsigned int take;
            scanf("%u",&take);
            sorted_list_t copy = sorted_list_take(list,take);
            list = sorted_list_destroy(list);
            list = copy;
        }
        else if (select==6){
            printf("\nSeleccionar cuantos elementos se quieren tirar: ");
            unsigned int drop;
            scanf("%u",&drop);
            sorted_list_t copy = sorted_list_drop(list,drop);
            list = sorted_list_destroy(list);
            list = copy;
        }
        else{
            quit = true; 
        }
        printf("\n\n");
    }
    list = sorted_list_destroy(list);
    return 0;
}
