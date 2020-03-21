#include <stdlib.h>
#include <stdio.h> // sprintf
#include "fraccion.h"

struct fraccion {
	int numerador;
	int denominador;
};

void simplificar(int* num, int* den) {
	if (*num == 0) {
		return;
	}
	// Si el denominador es negativo, entonces invierto.
	// Entonces si el numerador era negativo, ambos quedan positivos,
  // y si no me queda el negativo en el numerador.
	if (*den < 0) {
		*num *= -1;
		*den *= -1;
	}
	int max_posible_divisor = *num < *den ? *num : *den;
	for (int i = 2; i < max_posible_divisor; i++) {
		while (*num % i == 0 && *den % i == 0) {
			*num /= i;
			*den /= i;
		}
	}
}

fraccion_t* fraccion_crear(int numerador, int denominador) {
	if (denominador == 0) {
		return NULL;
	}
	fraccion_t* fraccion = malloc(sizeof(fraccion_t));
	if (!fraccion) {
		return NULL;
	}

	fraccion->numerador = numerador;
	fraccion->denominador = denominador;
	// Para evitar que al ir multiplicando se generen overflows
	simplificar(&fraccion->numerador, &fraccion->denominador);
	return fraccion;
}

void fraccion_destruir(fraccion_t* fraccion) {
	free(fraccion);
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2) {
	int denominador = f1->denominador * f2->denominador;
	fraccion_t* nueva = fraccion_crear(f1->numerador * f2->denominador + f2->numerador * f1->denominador, denominador);
	if (!nueva) {
		return NULL;
	}
	fraccion_destruir(f1);
	fraccion_destruir(f2);
	return nueva;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2) {
	fraccion_t* nueva = fraccion_crear(f1->numerador * f2->numerador, f1->denominador * f2->denominador);
	if (!nueva) {
		return NULL;
	}
	fraccion_destruir(f1);
	fraccion_destruir(f2);
	return nueva;
}

int fraccion_parte_entera(fraccion_t* fraccion) {
	return fraccion->numerador / fraccion->denominador;
}

size_t largo_numero(int num) {
	if (num == 0) {
		return 1;
	}
	size_t cant = 0;
	while (num > 0) {
		cant++;
		num /= 10;
	}
	return cant;
}

char* fraccion_representacion(fraccion_t* fraccion) {
	// Se puede suponer un tamaño maximo para esta cadena, como por ejemplo 10
	// Pero solo por una cuestion de mostrar el "cómo se haría", lo mostramos:
	size_t largo_num = largo_numero(fraccion->numerador);
	if (fraccion->denominador == 1) {
		int es_negativo = fraccion->numerador < 0 ? 1 : 0;
		char* cadena = calloc(largo_num + 1 + es_negativo, sizeof(char));
		if (!cadena) {
			return NULL;
		}
		sprintf(cadena, "%d", fraccion->numerador);
		return cadena;
	}

	size_t largo_den = largo_numero(fraccion->denominador);
	int es_negativo = fraccion->numerador < 0 ? 1 : 0;
	char* cadena = calloc(largo_num + largo_den + 2 + es_negativo, sizeof(char));
	if (!cadena) {
		return NULL;
	}
	sprintf(cadena, "%d/%d", fraccion->numerador, fraccion->denominador);
	return cadena;
}

