#ifndef LECTURA_H
#define LECTURA_H

#include <stdio.h>

/*
 * Lee una línea de un archivo o entrada estándar hasta encontrar un caracter
 * de fin de línea o el fin del archivo . Devuelve un char* con el contenido
 * leído en memoria dinámica, o NULL cuando se llega al final del archivo.
 * La cadena devuelta debe liberarse con free() cuando no se necesite más.
 *
 * Uso:
 *
 *    FILE *file = fopen(...);
 *    char *linea = leer_linea(file);
 *
 * O, para entrada estándar:
 *
 *    char *linea = leer_linea(stdin);
 */
char* leer_linea(FILE *fp);

#endif // LECTURA_H
