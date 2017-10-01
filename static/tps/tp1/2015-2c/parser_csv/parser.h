#ifndef PARSERH
#define PARSERH

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* tipo de dato abstracto de la fila del csv */
typedef struct fila fila_csv_t;

/* parsea una linea de csv
	input:
		- linea: cadena en formato csv valido
		- columnas: cantidad de columnas a leer de la línea 
	output:
		- un puntero a una estructura fila_csv_t con las columnas parseadas o NULL en caso de fallo */
fila_csv_t* parsear_linea_csv(char* linea, size_t columnas);


/* obtiene el valor de una columna del csv
	input:
		- fila: un struct fila valido
		- columnas: cantidad de columnas a leer de la línea
	output:
		- un puntero al valor de la columna especificada */
char* obtener_columna(fila_csv_t* fila, size_t columna);

/* libera la memoria de la estructa creada al parsear.
	input:
		- fila: puntero a una estructura fila creada en el llamado a parsear_linea_csv
		- liberar_datos: flag que indica si la funcion debe o no destruir los valoes de las columnas
*/
void destruir_fila_csv(fila_csv_t* fila, bool liberar_datos);

#endif
