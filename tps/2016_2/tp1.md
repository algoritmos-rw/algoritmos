---
title: TP 1
---

TP 1: manejo de archivos y cadenas
==================================
{:.no_toc}

Este trabajo práctico es *individual* y consiste de cuatro partes separadas, a ser entregadas el viernes 14 de octubre.

## Contenido
{:.no_toc}

1. TOC
{:toc}


# Aplicaciones

## paste

Se pide implementar una utilidad similar al programa [paste](http://ss64.com/bash/paste.html), que dados dos archivos, concatena su contenido de a líneas e imprime el resultado por salida estándar.

Por ejemplo, dado el siguiente par de archivos:

    $ cat anios.txt
    1996
    2007
    2013
    2016
    2016

    $ cat ciudades.txt
    Bogotá
    La Boca
    Lanús
    Nuñez
    Avellaneda

Al invocar el programa, su salida deberá ser la siguiente:

    $ ./paste anios.txt ciudades.txt
    1996  Bogotá
    2007  La Boca
    2013  Lanús
    2016  Nuñez
    2016  Avellaneda

Con las siguientes consideraciones:

  - Se deberá validar que la cantidad de parámetros en la invocación sea exactamente dos.
  - El separador que se usará para cada línea será '\t' (el caracter de tabulación).
  - Si los archivos tienen una cantidad diferente de líneas, se imprimirán sólo aquéllas líneas que tengan registros para los dos archivos y se emitirá una salida de error (-1) para informar al usuario.
  - El programa sólo debe almacenar en memoria una línea del archivo por vez.


## more

En este ejercicio se pide implementar una simplificación de la utilidad de Unix [more](http://ss64.com/bash/more.html) para mostrar por pantalla el contenido de un archivo.

El programa recibirá dos parámetros: el nombre de un archivo y un número entero _N_ que indica la cantidad inicial de líneas del archivo a ser mostradas por pantalla. Una vez impresas las primeras _N_ líneas, el programa mostrará una nueva línea del archivo cada vez que el usuario envíe un salto de línea (con la tecla enter) por entrada estándar.

Se deberá validar que el archivo exista y que el número _N_ sea entero positivo.


## dc

Para este ejercicio se pide implementar una simplificación del programa [dc](http://ss64.com/bash/dc.html). Este programa procesará la entrada estándar y la interpretará como un cálculo en [notación polaca inversa](https://en.wikipedia.org/wiki/Reverse_Polish_notation), imprimiendo por salida estándar el resultado.

El siguiente será el comportamiento esperado:

    $ echo "4 2 +" | ./dc
    6
    $ echo "2 9 4 + *" | ./dc
    26

Con las siguientes consideraciones:

- Los símbolos en la entrada pueden ser o bien números u operaciones. Todos ellos deben estar separados por espacios.
- Por simplicidad, sólo se esperan las siguientes operaciones: suma (+), resta (-), multiplicación (\*) y división (/).
- Si la entrada consta de varias líneas, se considerarán como cálculos independientes; y sus resultados se imprimirán de forma separada en líneas separadas.
- Si la expresión en la entrada no es válida, se interrumpirá inmediatamente el programa y se devolverá al sistema operativo un código de error.


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
     * de ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
     * cadenas que contiene son allocadas dinámicamente.
     *
     * Quien llama a la función toma responsabilidad de la memoria dinámica del
     * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
     * malloc(), o si ‘sep’ es '\0'.
     */
    char** split(const char* str, char sep);

Considerar los siguientes casos borde:

    split("abc,,def", ',')  →  ["abc", "", "def"]
    split("abc,def,", ',')  →  ["abc", "def", ""]
    split(",abc,def", ',')  →  ["", "abc", "def"]

    split("", ',')  →  [""]
    split(",", ',') →  ["", ""]


## join()

La función `join()` es la inversa de `split()``. Concatena un arreglo de cadenas terminado en NULL mediante un caracter de separación:

    // Ejemplo de uso de join
    char **strv = split("abc,def,ghi", ',');
    char *resultado = join(strv, ';');  // "abc;def;ghi"

    char **palabras = split("Hola mundo", ' ');
    char *otro_resultado = join(palabras, ',');  // "Hola,mundo"

El prototipo y documentación es:

    /*
     * Devuelve una cadena, allocada dinámicamente, resultado de unir todas las
     * cadenas del arreglo terminado en NULL ‘strv’.
     *
     * Quien llama a la función toma responsabilidad de la memoria dinámica de la
     * cadena devuelta. La función devuelve NULL si no se pudo allocar memoria.
     */
    char* join(char** strv, char sep);

Casos borde:

    join([])        →  ""
    join([""])      →  ""
    join(["abc"])   →  "abc"
    join(["", ""])  →  ","


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

Por ejemplo, si more usara un hash y dc usase un árbol, el archivo `deps.mk` consistiría de las siguientes dos líneas:

    # deps.mk: cada línea indica de qué OBJETOS se compone el programa.
    tac: tac.o hash.o
    tail: tail.o arbol.o

En el caso de haber creado una biblioteca de funcionalidad común, `lib.c`, se debería indicar también `lib.o` como dependencia:

    tac: tac.o lib.o hash.o
    tail: tail.o lib.o arbol.o

Para la compilación, pueden invocar a gcc a mano como hasta ahora o, de manera opcional, emplear el siguiente Makefile:

    # Flags de gcc. Se usan automáticamente para compilar *.c → *.o
    CFLAGS := -g -std=c99 -Wall -Wformat=2
    CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
    CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

    # Se pueden comentar durante el desarrollo.
    CFLAGS += -Werror

    # Si se ejecuta `make` a secas, se compilarán paste, more, bc y strutil.
    #
    # También se puede invocar `make paste`, `make more`, `make dc` o `make strutil.o` para
    # compilar una parte del TP solamente.

    all: paste more dc strutil.o

    include deps.mk

# Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.
La entrega incluye, obligatoriamente, un informe en formato PDF y los siguientes archivos de código:

- `paste.c`
- `more.c`
- `dc.c`
- `strutil.c` con las imlementaciones de las funciones `split`, `join` y `free_strv`.
- `pila.c`, `cola.c` y `lista.c` (las implementaciones del alumno de estos TDA; se debe incluir los archivos .h también)
- un archivo `deps.mk` con las dependencias del proyecto en formato make

La entrega se realiza:

1. por mail a la casilla de TPs (tps.7541rw@gmail.com): todos los archivos mencionados en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. En el asunto deben indicar: `TP1 - <Padrón> - <Apellido>`.
2. en papel durante la clase (si su ayudante lo requiere), tanto el informe como el código. No es necesario reimprimir el código de los TDA.


El informe deberá consistir de las siguientes partes:

  - carátula con los datos personales del alumno y el ayudante asignado.
  - análisis y diseño de la solución, en particular: algoritmos y estructuras de datos utilizados; orden de ejecución de cada programa o función.
