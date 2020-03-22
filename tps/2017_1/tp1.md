---
title: TP 1
---

TP 1: complejidad computacional, manejo de archivos y cadenas
=============================================================
{:.no_toc}

Este trabajo práctico es *individual* y consiste de cuatro partes separadas, a ser entregadas el lunes 8 de mayo.

## Contenido
{:.no_toc}

1. TOC
{:toc}


# Complejidad computacional

Se desea implementar una función en C de firma `double* obtener_promedio_movil(int* arreglo, size_t n, size_t k)`, que calcule el promedio movil del arreglo, en ventana de tamaño `k` (supóngase que `k <= n`). El promedio móvil de un arreglo es el promedio del mismo, tomando solamente en cuenta los elementos que se encuentran en una posición dada +- k, calculándolo para todas las posiciones posibles. Lo que debe devolver la función es un arreglo (dinámico) cuyos valores sean el promedio móvil tomado desde cada posición.

Por ejemplo, supongamos el arreglo `{ 1, 3, 12, 6, 17, 9 }`, `n = 6`, `k = 1`.

    pm[0] = (1 + 3) / 2 = 2   (En este caso no hay más elementos hacia la izquierda)
    pm[1] = (1 + 3 + 12) / 3 = 5.3333
    pm[2] = (3 + 12 + 6) / 3 = 7
    pm[3] = (12 + 6 + 17) / 3 = 11.6666
    pm[4] = (6 + 17 + 9) / 3 = 10.6666
    pm[5] = (17 + 9) / 2 = 13   (En este caso, no hay más elementos hacia derecha)

Una solución trivial es realizar este cálculo tal cual está: por cada elemento en el arreglo original, calcular el promedio móvil. Esto implica recorrer el arreglo entero, y por cada elemento, recorrer _2K_ elementos, por lo que el orden de dicha solución es _O(nk)_. Se pide:

1. Implementar dicha solución.
2. Implementar una solución de orden lineal que *no dependa* del valor de _k_.
3. Implementar pruebas donde se pruebe ambas implementaciones para distintos valores de _n_ y _k_.
4. Escribir un breve informe (máximo cuatro párrafos) en dónde expliquen qué orden tiene la versión optimizada, incluyendo mediciones de las ejecuciones.


# Aplicaciones

## filesplit

Se pide implementar una utilidad llamada `filesplit`, que dado el nombre de un archivo y un tamaño `n` en bytes, divide el archivo orginal en varios archivos de hasta `n` bytes. Por ejemplo:

    $ cat lorem.txt
    Lorem ipsum dolor sit amet, consectetur adipisicing elit.

Al invocar el programa, deberá generar los siguientes archivos de salida:

    $ ./filesplit lorem.txt 24

    $ ls
    lorem.txt  lorem.txt_001 lorem.txt_002 lorem.txt_003

    $ cat lorem.txt_0001
    Lorem ipsum dolor sit am

    $ cat lorem.txt_0002
    et, consectetur adipisic

    $ cat lorem.txt_0003
    ing elit.

Con las siguientes consideraciones:

  - Se deberá validar que la cantidad de parámetros en la invocación sea exactamente dos.
  - Los archivos generados serán llamados como el original, con el sufijo `_xxxx` (se podrá considerar que no habrá más de 9999 archivos de salida).
  - No se podrá considerar que entra todo el archivo a dividir en memoria.

## fixcol

Se pide implementar una utilidad llamada `fixcol`, que dado el nombre de un archivo y un tamaño `n` en bytes, divida todas las líneas del archivo en columnas de hasta `n` columnas y las imprima por salida estándar. Por ejemplo:

    $ cat lorem.txt
    Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi aliquip ex ea commodo consequat.
    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.

El programa deberá producir la siguiente salida al ser invocado:

    $ ./fixcol lorem.txt 75
    Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod te
    mpor incididunt ut labore et dolore magna aliqua.
    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ali
    quip ex ea commodo consequat.
    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolor
    e eu fugiat nulla pariatur.

Con las siguientes consideraciones:

  - Se deberá validar que la cantidad de parámetros en la invocación sea exactamente dos.
  - No se podrá considerar que entra todo el archivo a dividir en memoria.


# Manejo de cadenas

Se pide implementar las funciones del archivo [strutil.h](strutil.h) que se describen a continuación. Para la implementación de estas funciones no se puede hacer uso de TDAs:

## split()

La función split() divide una cadena en subcadenas en cada ocurrencia de un caracter de separación determinado. Por ejemplo, separando por comas:

    split("abc,def,ghi", ',')  →  ["abc", "def", "ghi"]

En C, devolveremos el resultado como un arreglo dinámico de cadenas dinámicas terminado en `NULL`. Esto es:

    // Ejemplo de arreglo dinámico de cadenas
    char **strv = malloc(sizeof(char*) * 4);
    strv[0] = strdup("abc");
    strv[1] = strdup("def");
    strv[2] = strdup("ghi");
    strv[3] = NULL;

El prototipo y la documentación de `split()`` queda en:

    /*
     * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
     * de 'str' separados por el carácter 'sep'. Tanto el arreglo devuelto como las
     * cadenas que contiene son allocadas dinámicamente.
     *
     * Quien llama a la función toma responsabilidad de la memoria dinámica del
     * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
     * malloc(), o si 'sep' es '\0'.
     */
    char** split(const char* str, char sep);

Considerar los siguientes casos borde:

    split("abc,,def", ',')  →  ["abc", "", "def"]
    split("abc,def,", ',')  →  ["abc", "def", ""]
    split(",abc,def", ',')  →  ["", "abc", "def"]

    split("", ',')  →  [""]
    split(",", ',') →  ["", ""]


## join()

La función `join()` es la inversa de `split()`. Concatena un arreglo de cadenas terminado en NULL mediante un caracter de separación:

    // Ejemplo de uso de join
    char **strv = split("abc,def,ghi", ',');
    char *resultado = join(strv, ';');  // "abc;def;ghi"

    char **palabras = split("Hola mundo", ' ');
    char *otro_resultado = join(palabras, ',');  // "Hola,mundo"

El prototipo y documentación es:

    /*
     * Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
     * cadenas del arreglo terminado en NULL 'strv'.
     *
     * Quien llama a la función toma responsabilidad de la memoria dinámica de la
     * cadena devuelta. La función devuelve NULL si no se pudo allocar memoria o
     * o si 'sep' es '\0'.
     */
    char* join(char** strv, char sep);

Casos borde:

    join([], ",")        →  ""
    join([""], ",")      →  ""
    join(["abc"], ",")   →  "abc"
    join(["", ""], ",")  →  ","


Complejidad algorítmica: se espera que la función tenga complejidad O(n) (Siendo n la longitud de la cadena resultante).

Las pruebas del corrector automático proveen una indicación. Este sería un test con comportamiento lineal:

    [ RUN      ] test_join.test_cuadratico_10000
    [       OK ] test_join.test_cuadratico_10000 (7 ms)
    [ RUN      ] test_join.test_cuadratico_20000
    [       OK ] test_join.test_cuadratico_20000 (14 ms)
    [ RUN      ] test_join.test_cuadratico_30000
    [       OK ] test_join.test_cuadratico_30000 (17 ms)
    [ RUN      ] test_join.test_cuadratico_40000
    [       OK ] test_join.test_cuadratico_40000 (27 ms)
    [ RUN      ] test_join.test_cuadratico_50000
    [       OK ] test_join.test_cuadratico_50000 (33 ms)
    [ RUN      ] test_join.test_cuadratico_60000
    [       OK ] test_join.test_cuadratico_60000 (40 ms)

Y este con comportamiento cuadrático:

    [ RUN      ] test_join.test_cuadratico_10000
    [       OK ] test_join.test_cuadratico_10000 (48 ms)
    [ RUN      ] test_join.test_cuadratico_20000
    [       OK ] test_join.test_cuadratico_20000 (618 ms)
    [ RUN      ] test_join.test_cuadratico_30000
    [       OK ] test_join.test_cuadratico_30000 (1354 ms)
    [ RUN      ] test_join.test_cuadratico_40000
    [       OK ] test_join.test_cuadratico_40000 (2425 ms)
    [ RUN      ] test_join.test_cuadratico_50000
    [       OK ] test_join.test_cuadratico_50000 (4019 ms)
    [ RUN      ] test_join.test_cuadratico_60000
    [       OK ] test_join.test_cuadratico_60000 (5722 ms)

## free_strv()

`free_strv()` libera la memoria asociada con un arreglo dinámico de cadenas dinámicas:

    /*
     * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
     */
    void free_strv(char *strv[]);

# Consideraciones

## Lectura de archivos

Para la lectura de flujos se recomienda usar la función [getline()](http://man7.org/linux/man-pages/man3/getline.3.html).

    ssize_t getline(char** buffer, size_t* capacidad, FILE* archivo);

La principal ventaja de esta función es que automáticamente reserva la memoria dinámica necesaria para almacenar la línea. No se necesita invocar manualmente malloc() a mano, ni preocuparse por los tamaños de los buffers.

Sí se necesita, no obstante, liberar memoria al terminar: getline() llama a malloc() pero transfiere la responsabilidad de la memoria al usuario.

La reserva de memoria dinámica se consigue llamando a la función punteros a un buffer igual a NULL y a una capacidad 0:

    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t longitud = getline(&linea, &capacidad, archivo);
    // Se debe liberar la memoria al terminar de usarla.
    free(linea);

La función getline() se encuentra definida en la cabecera `stdio.h`. Como es una función de POSIX.1-2008, hay que declarar un identificador para indicar que la queremos usar:

    // Al principio de tail.c y tac.c (antes de otros include):
    #define _POSIX_C_SOURCE 200809L
    #include <stdio.h>
    #include <string.h>

## deps.mk

Se debe incluir un archivo deps.mk para indicar al corrector automático cómo compilar la entrega.
En particular, se debe indicar qué TDA emplea cada programa.

Por ejemplo, si fixcol usara una lista enlazada y filesplit usase un vector dinámico, el archivo `deps.mk` consistiría de las siguientes dos líneas:

    # deps.mk: cada línea indica de qué OBJETOS se compone el programa.
    fixcol: fixcol.o lista.o
    filesplit: filesplit.o vd.o

En el caso de haber creado una biblioteca de funcionalidad común, `lib.c`, se debería indicar también `lib.o` como dependencia:

    fixcol: fixcol.o lista.o lib.o
    filesplit: filesplit.o vd.o lib.o

Para la compilación, pueden invocar a gcc a mano como hasta ahora o, de manera opcional, emplear el siguiente Makefile:

    # Flags de gcc. Se usan automáticamente para compilar *.c → *.o
    CFLAGS := -g -std=c99 -Wall -Wformat=2
    CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
    CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

    # Se pueden comentar durante el desarrollo.
    CFLAGS += -Werror

    # Si se ejecuta `make` a secas, se compilarán prom_movil.o, fixcol, filesplit y strutil.o .
    #
    # También se puede invocar `make fixcol`, `make filesplit` o `make strutil.o` para
    # compilar una parte del TP solamente.

    all: fixcol filesplit strutil.o prom_movil.o

    include deps.mk

# Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.
La entrega incluye, obligatoriamente, un pequeño informe en formato PDF para la sección de complejidad, y los siguientes archivos de código:

- `fixcol.c`
- `filesplit.c`
- `prom_movil.c` con la imlementación de `obtener_promedio_movil`.
- `strutil.c` con las imlementaciones de las funciones `split`, `join` y `free_strv`.
- un archivo `deps.mk` con las dependencias del proyecto en formato make

La entrega se realiza:

1. por mail a la casilla de TPs (`tps.7541rw@gmail.com`): todos los archivos mencionados en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. En el asunto deben indicar: `TP1 - <Padrón> - <Apellido>`.
2. en papel durante la clase (si su ayudante lo requiere), tanto el informe como el código. No es necesario reimprimir el código de los TDA.
