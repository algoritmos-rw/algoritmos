#include "parser.h"

struct fila {
	char** datos;
	size_t columnas;
}; 

static bool debe_continuar(char* caracter) {
	return (caracter) && (*caracter) && (*caracter != '\n');
}

static fila_csv_t* crear_fila_csv(size_t columnas) {
	fila_csv_t* output = malloc(sizeof(fila_csv_t));
	if (!output) return NULL;
	output->columnas = columnas;
	output->datos = malloc(sizeof(char*) * columnas);
	if (!output->datos){
		free(output);
		return NULL;
	}
	return output;
}

char* obtener_columna(fila_csv_t* fila, size_t columna) {
	return columna < fila->columnas ? fila->datos[columna] : NULL;
}

void destruir_fila_csv(fila_csv_t* fila, bool debe_destruir) {
	
	if (debe_destruir) for (size_t i = 0; i < fila->columnas; i++) {
		free(fila->datos[i]);
	}
	free(fila->datos);
	free(fila);
}

fila_csv_t* parsear_linea_csv(char* linea, size_t columnas) {
	fila_csv_t* output = crear_fila_csv(columnas);
	if (!output) return NULL;
	char* primero = linea;
	char* ultimo = linea;
	size_t columna_actual = 0;
	while (columna_actual < columnas && debe_continuar(primero)) {
		ultimo++;
		if ((*ultimo != ',') && (*ultimo) && (*ultimo != '\n')) {
			continue;
		}
		size_t largo = ((size_t)(ultimo - primero)) + 1;
		output->datos[columna_actual] = malloc(sizeof(char) * largo);
		if (!output->datos[columna_actual]) {
			output->columnas = columna_actual;
			destruir_fila_csv(output, true);
			return NULL;
		}
		strncpy(output->datos[columna_actual], primero, largo);
		output->datos[columna_actual++][largo-1] = '\0';
		primero = ultimo + 1;
	}
	return output;
}
