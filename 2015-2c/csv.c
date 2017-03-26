#define _POSIX_C_SOURCE 200809L  // For getline().

#include "csv.h"
#include <stdlib.h>
#include <string.h>

void csv_terminar(csv_t *linea) {
    if (linea)
        free(linea->_buffer);
}

bool csv_siguiente(csv_t *l, FILE *fp) {
    ssize_t n = -1;

    if ((n = getline(&l->_buffer, &l->_tam, fp)) == -1) {
        return false;
    }

    l->_buffer[n - 1] = '\0';  // Eliminar el '\n' del final.
    l->primero = l->_buffer;

    split(l->delim, l->primero, &l->segundo);

    return true;
}

void split(char c, char *string, char **resto) {
    char *pos = strchr(string, c);

    if (pos == NULL) {
        *resto = strchr(string, '\0');
    }
    else {
        *pos++ = '\0';  // Dividir en dos cadenas.
        *resto = pos;
    }
}
