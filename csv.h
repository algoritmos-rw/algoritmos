#ifndef CSV_H
#define CSV_H

#include <stdbool.h>
#include <stdio.h>

/* Función para leer un archivo CSV o similar de dos columnas. Al crear
   el parser, se indica cuál es el caracter de separación.

Uso
===

    FILE* archivo = fopen(...);
    csv_t linea = {.delim = ','};

    while (csv_siguiente(&linea, archivo)) {
      printf("Primer campo: %s\n", linea.primero);
      printf("Segundo campo: %s\n", linea.segundo);
    }

    csv_terminar(&linea);
    fclose(archivo);

O, para los comandos
====================

    csv_t cmd = {.delim = ':'};

    while (csv_siguiente(&linea, stdin)) {
      printf("Nombre comando: %s\n", linea.primero);
      printf("Parámetros comando: %s\n", linea.segundo);
    }

    csv_terminar(&linea);

*/

typedef struct {
    char delim;
    char *primero;
    char *segundo;
    size_t _tam;
    char *_buffer;
} csv_t;

bool csv_siguiente(csv_t *linea, FILE *fp);
void csv_terminar(csv_t *linea);

// Trunca una cadena en la primera ocurrencia de un determinado carácter, y
// apunta "resto" al resto. Si el carácter no está presente en la función,
// "resto" es la cadena vacía. Esta función *no* reserva memoria.
// Ejemplos:
//
//    split(':', "hola:adios") -> resto = "adios"
//    split(':', "hola")  -> resto = ""
//    split(':', "hola:") -> resto = ""
void split(char c, char *string, char **resto);

#endif  // CSV_H
