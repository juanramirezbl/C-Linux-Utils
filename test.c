#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include  "libreria.h"

int main(int argc, char *argv[]){
	int N=10; //valor predeterminado para el numero de lineas.
	int result = 0; //para almacenar el resultado de las funciones.
	
	//verificar que se haya proporcionado al menos 1 arg (el de la funcion)
	if (argc < 2) {
		fprintf(stderr, "Uso: %s -<funcion> [numero de lineas]\n", argv[0]);
		return 1;
	}
	
	//verificar que el primer argumento comienza con '-'
	if (argv[1][0] != '-'){
		fprintf(stderr, "El primer argumento debe comenzar con un guion (-).\n");
		return 1;
	}
	
	//procesar el segundo argumento como numero de lineas (si existe)
	if (argc > 2) {
		N = atoi(argv[2]);
		if (N <= 0) {
			fprintf(stderr,"Numero de lineas invalido, debe ser mayor que cero (%d).\n", N);
			return 1;
		}
	}
	
	
	
	//Seleccionar la funcion en base al primer argumento (sin contar el guion)
	if (strcmp(argv[1], "-head") == 0){
		result = head(N);
	}
	else if (strcmp(argv[1], "-tail") == 0){
		result = tail(N);
	}
	else if (strcmp(argv[1], "-longlines") == 0){
		result = longlines(N);
	}
	else{
		// si el primer argumento no coincide con ninguna funcion.
		fprintf(stderr, "Funcion no reconocida.\n");
		return 1;
	}
	
	return result;
	
	
}

