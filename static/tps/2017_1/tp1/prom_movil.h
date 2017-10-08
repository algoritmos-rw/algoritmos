#ifndef PROM_MOVIL_H
#define PROM_MOVIL_H

#include <stddef.h>

/*
 * Devuelve un arreglo dinámico en dónde se almacene el promedio móvil del
 * arreglo pasado por parámetro considerando el parámetro k.
 */
double* obtener_promedio_movil(int* arreglo, size_t n, size_t k);

#endif  // PROM_MOVIL_H
