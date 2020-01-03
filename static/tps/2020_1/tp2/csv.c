#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
#include "strutil.h"

struct csv_file_iter {
	FILE* archivo;
	char** actual;
};

bool leer_linea(csv_file_iter_t* reader) {
	char* linea = NULL;
	size_t capacidad = 0;
	if (getline(reader->archivo, &linea, &capacidad) <= 0) {
		reader->actual = NULL;
		return false;
	}
	reader->actual = split(linea, ',');
	return reader->actual != NULL;
}

csv_file_iter_t* csv_file_iter_crear(const char* ruta_csv) {
	csv_file_iter_t reader = malloc(sizeof(csv_file_iter_t));
	if (!reader) return NULL;

	reader->archivo = fopen(ruta_csv, 'r');
	if (!reader->archivo) {
		free(reader);
		return NULL;
	}
	leer_linea(reader);
	return reader;
}

bool csv_file_iter_al_final(const csv_file_iter_t* reader) {
	return reader->actual == NULL;
}

char** csv_file_iter_ver_actual(const csv_file_iter_t* reader) {
	if (csv_file_iter_al_final(reader)) {
		return NULL;
	}
	return reader->actual;
}

bool csv_file_iter_avanzar(csv_file_iter_t* reader) {
	if (csv_file_iter_al_final(reader)) {
		return false;
	}
	free_strv(reader->actual);
	leer_linea(reader);
	return true;
}

void csv_file_iter_destruir(csv_file_iter_t* reader) {
	if (!csv_file_iter_al_final(reader)) {
		free_strv(reader->actual);
	}
	fclose(reader->archivo);
	free(reader);
}
