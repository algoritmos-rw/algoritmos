#include <stdio.h>
#include "parser.h"
#include <string.h>

void imprimir_prueba(const char* nombre_prueba, bool evaluacion) {
	printf("%s: %s\n", nombre_prueba, evaluacion? "OK": "ERROR");
}

int main(int argc, const char** argv) {
	char* linea1 = "1,2,3,4";
	char* linea2 = "asd,qwe,zxc,dsa";
	fila_csv_t* linea1_parseada = parsear_linea_csv(linea1, 4);
	imprimir_prueba("prueba linea1 no es null", linea1_parseada);
	bool comparacion = strcmp("1", obtener_columna(linea1_parseada,0)) == 0;
	comparacion &= strcmp("2", obtener_columna(linea1_parseada,1)) == 0;
	comparacion &= strcmp("3", obtener_columna(linea1_parseada,2)) == 0;
	comparacion &= strcmp("4", obtener_columna(linea1_parseada,3)) == 0;
	imprimir_prueba("prueba linea1 elementos ok", comparacion);
	destruir_fila_csv(linea1_parseada, true);
	linea1_parseada = parsear_linea_csv(linea2, 4);
	comparacion = strcmp("asd", obtener_columna(linea1_parseada,0)) == 0;
	comparacion &= strcmp("qwe", obtener_columna(linea1_parseada,1)) == 0;
	comparacion &= strcmp("zxc", obtener_columna(linea1_parseada,2)) == 0;
	comparacion &= strcmp("dsa", obtener_columna(linea1_parseada,3)) == 0;
	imprimir_prueba("prueba linea2 elementos ok", comparacion);
	destruir_fila_csv(linea1_parseada, true);
	linea1_parseada = parsear_linea_csv("", 0);
	imprimir_prueba("parsear cadena vacia", linea1_parseada);
	destruir_fila_csv(linea1_parseada, false);
	return 0;
}