#include <stdio.h>
#include "libreria.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024
#define LINE_BLOCK_SIZE 1 

int head(int N){
	int count = 0; //contador de lineas leidas
	char *line = NULL; //inicializacion del puntero.
	
	if (N <= 0){ //Control de argumentos.
		fprintf(stderr,"El valor N debe ser positivo.\n");
		return 1;
	}
	
	//reserva en memoria dinamica para el buffer line
	line = malloc(MAX_LINE_LENGTH * sizeof(char));
	if (line == NULL){
		fprintf(stderr, "Error en la asginacion de memeria.\n");
		return 1;
	}
	
	
	
	while(fgets(line, MAX_LINE_LENGTH, stdin)) {
		if (count >= N) break; // si se alcanza N se detiene.
		printf("%s", line);//Imprime la linea leida.
		count++;
	}
	
	free(line);//liberamos la memeria asignada.
	
	return 0;
	
}

int tail(int N){
	int start = 0;
	int lines_to_print = 0;
	int count = 0; //contador de lineas leidas.
	int index = 0; // indice circular para la posicion del buffer.
	char **buffer = NULL; // inicializacion del buffer.
	
	if (N <= 0){ //Control de argumentos.
		fprintf(stderr,"El valor N debe ser positivo.\n");
		return 1;
	}
	
	//Creamos un buffer circular para almacenar las ultimas N lineas
	buffer = malloc(N * sizeof(char*));
	if (buffer == NULL){
		fprintf(stderr, "Error en la asignacion de memoria.\n");
		return 1;
	}
	
	//Inicializar el buffer y reservar en memoria para cada linea.
	for(int i = 0; i < N; i++) {
		buffer[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
		if (buffer[i] == NULL) {
			fprintf(stderr,"Error en la asignacion de memoria para una linea.\n");
			for (int j = 0; j < i; j++){
				free(buffer[j]);
			}
			free(buffer[i]);
			return 1;
		}
	}
	

	
	
	
	//Leer lineas usando fgets
	
	while (fgets(buffer[index], MAX_LINE_LENGTH, stdin) != NULL){
		index = (index + 1) % N;
		count++;
	}
	
	//Imprimir las ultimas N lineas almacenadas en el buffer
	
	start = (count < N) ? 0 : index;
	lines_to_print = (count < N) ? count : N;
	
	for (int i = 0; i < lines_to_print; i++) {
		printf("%s", buffer[(start + i) % N]);
	}
	
	//Liberar la memoria asignada para el buffer.
	for (int i = 0; i < N; i++){
		free(buffer[i]);
	}
	free(buffer);
	
	return 0;
}



int compare_lines(const void *a, const void *b) {
    // Convertimos los punteros a los tipos correctos
    const char *line_a = *(const char **)a;
    const char *line_b = *(const char **)b;
    
    // Calculamos la diferencia en longitudes
    return strlen(line_b) - strlen(line_a);
}


int longlines(int N) {
    char *caracteres = NULL;      // Buffer para cada línea individual
    char **lineas = NULL;          // Buffer para guardar las líneas
    int cap_l = LINE_BLOCK_SIZE;   // Capacidad inicial de almacenamiento de lineas
    int num_lineas = 0;
    int long_linea = 0;
  
    if (N <= 0){ //Control de argumentos.
	    fprintf(stderr,"El valor N debe ser positivo.\n");
	    return 1;
    }
	
    // Reservamos espacio inicial para las líneas
    lineas = malloc(cap_l * sizeof(char *));
    if (lineas == NULL) {
        fprintf(stderr, "Error de memoria al asignar líneas\n");
        return 1;
    }

    // Reservamos espacio para la línea
    caracteres = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (caracteres == NULL) {
        fprintf(stderr, "Error de memoria al asignar buffer temporal\n");
        free(lineas);
        return 1;
    }

    // Leemos todas las líneas de la entrada estándar con fgets
    while (fgets(caracteres, MAX_LINE_LENGTH, stdin) != NULL) {
        long_linea = strlen(caracteres);

        // Eliminamos el salto de línea al final
        if (caracteres[long_linea - 1] == '\n') {
            caracteres[long_linea - 1] = '\0';
            long_linea--;
        }

        // Si alcanzamos necesitamos mas capacidad la aumentamos con realloc
        if (num_lineas >= cap_l) {
            cap_l += LINE_BLOCK_SIZE;
            char **temp = realloc(lineas, cap_l * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "Error de memoria al expandir líneas\n");
                for (int i = 0; i < num_lineas; i++) {
                    free(lineas[i]);
                }
                free(lineas);
                free(caracteres);
                return 1;
            }
            lineas = temp;
        }

        //Guardamos la linea en el buffer de lineas
        lineas[num_lineas] = strdup(caracteres);
        if (lineas[num_lineas] == NULL) {
            fprintf(stderr, "Error de memoria al duplicar la línea\n");
            for (int i = 0; i < num_lineas; i++) {
                free(lineas[i]);
            }
            free(lineas);
            free(caracteres);
            return 1;
        }
        num_lineas++;
    }

    // Utilizamos el qsort para ordenar las lineas de mayor a menor
    qsort(lineas, num_lineas, sizeof(char *), compare_lines);

    // Imprimimos las N líneas más largas
    for (int i = 0; i < N && i < num_lineas; i++) {
        printf("%s\n", lineas[i]);
        free(lineas[i]);
    }

    // Liberar el resto de las líneas
    for (int i = N; i < num_lineas; i++) {
        free(lineas[i]);
    }
    free(lineas);
    free(caracteres);

    return 0;
}
