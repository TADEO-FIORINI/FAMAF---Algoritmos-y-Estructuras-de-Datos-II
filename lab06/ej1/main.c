/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);
    
    /*menu de opciones*/
    bool exit = false;
    int select;
    while (!exit){
        printf("1 ........ Mostrar árbol por pantalla\n2 ........ Agregar un elemento\n3 ........ Eliminar un elemento\n4 ........ Chequear existencia de elemento\n5 ........ Mostrar longitud del árbol\n6 ........ Mostrar raiz, máximo y mínimo del árbol\n7 ........ Salir\n\nSelecciona una opcion: ");
        scanf("%d",&select);
        if (select==1){
            abb_dump(tree);
            printf("\n\n");
        }
        else if (select==2){
            abb_elem new_elem;
            printf("Seleccione el elemento a añadir: ");
            scanf("%d",&new_elem);
            tree = abb_add(tree,new_elem);
            printf("\n");
        }
        else if (select==3){
            abb_elem remove_elem;
            printf("Seleccione el elemento a eliminar: ");
            scanf("%d",&remove_elem);
            tree = abb_remove(tree,remove_elem);
            printf("\n");
        }
        else if (select==4){
            abb_elem check_elem;
            printf("Seleccione el elemento a chequear: ");
            scanf("%d",&check_elem);
            if (abb_exists(tree,check_elem)){
                printf("El elemento %d existe en el arbol\n\n",check_elem);
            }
            else{
                printf("El elemento %d NO existe en el arbol\n\n",check_elem);
            }
        }
        else if (select==5){
            printf("La longitud del arbol es %u\n\n",abb_length(tree));
        }
        else if (select==6){
            if (!abb_is_empty(tree)) {
                printf("\n");
                printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),abb_min(tree),abb_max(tree));
            }
            else {
                printf("\nÁrbol vacío\n");
            }
            printf("\n");
        }
        else if (select==7){
            exit=true;
        }
        else{
            printf("Opcion invalida\n");
        }
    }
    tree = abb_destroy(tree);
    return (EXIT_SUCCESS);
}
