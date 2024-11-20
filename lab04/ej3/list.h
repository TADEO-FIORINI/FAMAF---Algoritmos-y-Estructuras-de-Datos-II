#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int list_elem;
typedef struct _list * list;

list empty(void);
    // {crea una lista vacia}

list addl(list l, list_elem e);
    // {añade un elemento por izquierda }

list addr(list l, list_elem e);
    // {añade un elemento por derecha}

bool is_empty(list l);
    // {chequea si la lista es vacia}

list_elem head(list l);
    // {devuelve el primer elemento de la lista}
    // {PRE: !is_empty(l)}

list tail(list l);
    // {elimina el primer elemento de la lista}
    // {PRE: !is_empty(l)}

unsigned int length(list l);
    // {devuelve la cantidad de elementos de la lista}

list concat(list l1, list l2);
    // {agrega al final de l1 los elementos de l2 comenzando por el primero}

list_elem index(list l, unsigned int n);
    // {devuelve el elemento que esta en la posicion n}
    // PRE: length(l)>n

list take(list l, unsigned int n);
    // {conserva los primeros n elementos de la lista}
    // PRE: length(l)>n

list drop(list l, unsigned int n);
    // {elimina los primeros n elementos de la lista}

list copy(list l);
    // {copia la lista l en otra lista}

list destroy(list l);
    // {libera la memoria se es necesario}

#endif