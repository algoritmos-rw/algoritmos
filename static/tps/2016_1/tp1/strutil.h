#ifndef STRUTIL_H
#define STRUTIL_H

#include <stddef.h>

/*
 * Devuelve una nueva cadena, allocada dinámicamente, con los primeros ‘n’
 * caracteres de la cadena ‘str’. El caller toma ownership de la cadena
 * devuelta.
 *
 * Devuelve NULL si no se pudo allocar memoria.
 */
char *substr(const char *str, size_t n);

/*
 * Devuelve en un arreglo dinámico terminado en NULL todos los subsegmentos de
 * ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * El caller toma ownership del vector devuelto. La función devuelve NULL si
 * falló alguna llamada a malloc(), o si ‘sep’ es '\0'.
 */
char **split(const char *str, char sep);

/*
 * Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL ‘strv’.
 *
 * El caller toma ownership de la cadena devuelta. La función devuelve NULL
 * si no se pudo allocar memoria.
 */
char *join(char **strv, char sep);

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char *strv[]);

#endif  // STRUTIL_H
