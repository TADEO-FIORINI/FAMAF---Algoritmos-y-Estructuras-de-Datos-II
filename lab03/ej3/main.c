#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000
#define ARGS 2

static void dump(char a[], unsigned int length) {
	for (unsigned int i=0u; i < length; i++) {
		printf("%c", a[i]);
	}
	printf("\n");
}

void sort_data(unsigned int indexes[],char letters[],char sorted[],unsigned int length){
	for(unsigned int i = 0u; i < length ;i++){
		sorted[indexes[i]] = letters[i];
	}
}

unsigned int data_from_file(const char *path,unsigned int indexes[],char letters[],unsigned int max_size){
	FILE *file = fopen(path,"r");
	if(file == NULL){
		printf("No se ha podido leer el archivo o no existe\n");
		exit(EXIT_FAILURE);
	}
	unsigned int i=0;
	while(!feof(file) && i < max_size){
		fscanf(file,"%u -> *%c* ",&indexes[i],&letters[i]);
		i++;
	}
	return i;
}

int main(int argc, char *argv[]) {
	
	if(argc != ARGS){
		printf("Formato invalido\n");
		printf("Usage: $./programa ruta\n");
		exit(EXIT_FAILURE);

	}
	unsigned int indexes[MAX_SIZE];
	char letters[MAX_SIZE];
	unsigned int length=0;
	length = data_from_file(argv[1],indexes,letters,MAX_SIZE);
	char sorted[MAX_SIZE];
	sort_data(indexes,letters,sorted,length); 
	dump(sorted, length);

	return EXIT_SUCCESS;
}

