---
title: TP1 – Manejo de archivos, cadenas y TDAs básicos
math: true
trabajo: TP1
---
{% assign TP = site.data.trabajos[page.trabajo] %}

# Trabajo Práctico 1
{:.no_toc}

## Contenido
{:.no_toc}

* Contenido
{:toc}

El Trabajo Práctico número 1 tiene fecha de entrega para el **10 de mayo**, y
está divido en tres partes:
* implementación de funciones auxiliares para cadenas ([`strutil`](#manejo-de-cadenas))
* implementación de aplicación [fixcol](#fixcol)
* implementación de interprete del lenguaje [Brainfuck](https://es.wikipedia.org/wiki/Brainfuck)

## Manejo de cadenas

Se pide implementar las funciones del archivo adjunto en [el sitio de descargas]({{site.skel}}) que se describen a
continuación. Se permite utilizar cualquier función de [string.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html), aunque se desaconseja el uso de strtok. Para la implementación de estas funciones no se puede hacer uso de TDAs.

Se recomienda leer la documentación de las siguientes funciones del módulo de `string.h`:
- `strlen`
- `strcpy`, `strncpy`
- `strcat`, `strncat`
- `strcmp`
- `memcpy`

### substr()

La función `substr()` permite obtener un prefijo de longitud $$k$$ de una cadena dada.

Por ejemplo, la llamada `substr("Hola mundo", 6)` devolvería la cadena `"Hola m"`. El resultado debe ser una
nueva cadena de memoria dinámica con dichos caracteres (y, por supuesto, el carácter de fin de cadena).
Ejemplos de uso:
``` cpp
substr("Hola mundo", 6)         → "Hola m"
const char* ejemplo = "Ejemplo"
substr(ejemplo + 2, 2)          → "em"
substr("", 2)                   → ""
substr("Algoritmos", 30)        → "Algoritmos"
```

Complejidad algorítmica: se espera que la función tenga complejidad $$\mathcal{O}(k)$$.


### split()

La función `split()` divide una cadena en subcadenas en cada ocurrencia de un
caracter de separación determinado. Por ejemplo, separando por comas:

``` cpp
split("abc,def,ghi", ',')  →  ["abc", "def", "ghi"]
```

En C, devolveremos el resultado como un arreglo dinámico de cadenas dinámicas
terminado en `NULL`. Esto es:

``` cpp
// Ejemplo de arreglo dinámico de cadenas
char **strv = malloc(sizeof(char*) * 4);
strv[0] = strdup("abc");
strv[1] = strdup("def");
strv[2] = strdup("ghi");
strv[3] = NULL;
```

Considerar los siguientes casos borde:

``` cpp
split("abc,,def", ',')  →  ["abc", "", "def"]
split("abc,def,", ',')  →  ["abc", "def", ""]
split(",abc,def", ',')  →  ["", "abc", "def"]
split("abc", '\0')      →  ["abc"]

split("", ',')  →  [""]
split(",", ',') →  ["", ""]
```

Complejidad algorítmica: se espera que la función tenga complejidad $$\mathcal{O}(n)$$ (Siendo $$n$$ la longitud de la
cadena resultante).

### join()

La función `join()` es la inversa de `split()`. Concatena un arreglo de cadenas terminado en NULL mediante un caracter
de separación:

``` cpp
// Ejemplo de uso de join
char **strv = split("abc,def,ghi", ',');
char *resultado = join(strv, ';');  // "abc;def;ghi"

char **palabras = split("Hola mundo", ' ');
char *otro_resultado = join(palabras, ',');  // "Hola,mundo"
```

Casos borde:
``` cpp
join([""], ',')             →  ""
join(["abc"], ',')          →  "abc"
join(["", ""], ',')         →  ","
join([], ',')               →  "" // Join de arreglo vacío, {NULL} en C.
join(["abc", "def"], '\0')  →  "abcdef"
```

Complejidad algorítmica: se espera que la función tenga complejidad $$\mathcal{O}(n)$$ (Siendo $$n$$ la longitud de la
cadena resultante).

Las pruebas del corrector automático proveen una indicación del comportamiento de `join()` (si bien **todas las funciones deben correr en tiempo lineal**, `join()` provee una dificultad de implementación mayor a `split()` o
`substr()`).

Este sería un test con comportamiento lineal:

    [ RUN      ] test_join.test_complejidad_10000
    [       OK ] test_join.test_complejidad_10000 (7 ms)
    [ RUN      ] test_join.test_complejidad_20000
    [       OK ] test_join.test_complejidad_20000 (14 ms)
    [ RUN      ] test_join.test_complejidad_30000
    [       OK ] test_join.test_complejidad_30000 (17 ms)
    [ RUN      ] test_join.test_complejidad_40000
    [       OK ] test_join.test_complejidad_40000 (27 ms)
    [ RUN      ] test_join.test_complejidad_50000
    [       OK ] test_join.test_complejidad_50000 (33 ms)
    [ RUN      ] test_join.test_complejidad_60000
    [       OK ] test_join.test_complejidad_60000 (40 ms)

Y este con comportamiento cuadrático:

    [ RUN      ] test_join.test_complejidad_10000
    [       OK ] test_join.test_complejidad_10000 (48 ms)
    [ RUN      ] test_join.test_complejidad_20000
    [       OK ] test_join.test_complejidad_20000 (618 ms)
    [ RUN      ] test_join.test_complejidad_30000
    [       OK ] test_join.test_complejidad_30000 (1354 ms)
    [ RUN      ] test_join.test_complejidad_40000
    [       OK ] test_join.test_complejidad_40000 (2425 ms)
    [ RUN      ] test_join.test_complejidad_50000
    [       OK ] test_join.test_complejidad_50000 (4019 ms)
    [ RUN      ] test_join.test_complejidad_60000
    [       OK ] test_join.test_complejidad_60000 (5722 ms)


### free_strv()

`free_strv()` libera la memoria asociada con un arreglo dinámico de cadenas dinámicas:

Si bien no es obligatorio probar la biblioteca, es muy recomendable hacer pruebas unitarias para comprobar el correcto
funcionamiento, en particular para los casos borde.


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

### Observaciones

  - Se deberá validar que la cantidad de parámetros en la invocación sea exactamente dos.
  - No se podrá considerar que entra todo el archivo a dividir en memoria.


## Brainfuck

Los amigos del instituto del cerebro nos pidieron que implementemos un intérprete del famoso lenguaje llamado
[Brainfuck](https://es.wikipedia.org/wiki/Brainfuck), este lenguaje cuenta con la característica que tiene muy pocas
instrucciones posibles (sólo 7) y tambien por tener un compilador o
[intérprete](https://es.wikipedia.org/wiki/Int%C3%A9rprete_(inform%C3%A1tica)) muy pequeño y fácil de implementar.

Un link útil para probar este lenguaje es este [intérprete online](https://copy.sh/brainfuck/).

Su tarea es implementar un intérprete de Brainfuck en el lenguaje C. El programa deberá ejecutarse de la siguiente forma:
```
    $ ./bf <ruta al archivo>
```
Donde `ruta al archivo` es la ruta al archivo a interpretar. Por ejemplo: `./bf ejemplo.bf`. En caso que no se
indique ruta al archivo, deberá leerse de entrada estándar (similar a como hace el intérprete de Python).

Se brinda en [el sitio de descargas]({{site.skel}}) un set (reducido) de archivos de prueba de ejemplo.
La forma de ejecutar dichas pruebas es:
```
    $ ./pruebas.sh ruta/a/ejecutable/bf
```

Tener en cuenta que estas pruebas contemplan casos triviales, y algunos muy complejos. Para pruebas intermedias
recomendamos implementar las suyas, pudiendo utilizar el intérprete provisto para confirmar resultados.
Se pueden seguir agregando pruebas utilizando el mismo formato que las anteriores: tener un archivo "xx_in" que servirá
de entrada al programa (instrucción ','), otro "xx_script" que deberá tener el código a interpretar, otro "xx_out" que
corresponderá con la salida esperada, y otro de "xx.test" que deberá contener la descripción de la prueba.

### Observaciones

  - Todos los caracteres diferentes a los definidos por el lenguaje deben ser ignorados.
  - Se puede considerar que el archivo fuente entra todo en memoria, aunque recomendamos sólo almacenar lo
  necesario.
  - Se debe validar la cantidad de argumentos pasados al programa, en caso de haber una cantidad inválida, escribir
  por salida de error (`stderr`): `Error: Cantidad erronea de parametros` (sin tildes).
  - Se debe validar (en caso de indicarse) que se pueda leer el archivo pasado por parámetro. En caso de no ser posible
  escribir por salida de error (`stderr`): `Error: archivo fuente inaccesible`.
  - Las impresiones realizadas por el programa deben realizarse a salida estándar (`stdout`).

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- `strutil.c` con las implementaciones de las funciones `substr`, `split`, `join` y `free_strv`.
- El código de la solución de _bf_ en `bf.c` y _fixcol_ en `fixcol.c`.
- El código de los TDAs programados en la cursada que se requieran.
- Un archivo `deps.mk` con las dependencias del proyecto en formato make. Este
deberá contener sólamente una línea por programa que indique qué _objetos_ necesita para
compilar el ejecutable de cada uno de los archivos, por ejemplo:

``` makefile
bf: bf.o
fixcol: cola.o pila.o fixcol.o
```

El corrector automático va a interpretar ese archivo de dependencias y va a
compilar todos los `.o` especificados a partir de los `.h` y `.c` que deberán
enviar, con los siguientes flags de `GCC`:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. En forma digital a través del [sistema de entregas]({{site.entregas}}):
todos los archivos mencionados en un único archivo ZIP.
2. En papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, informe ni carátula**. No es necesario
reimprimir el código de los TDA.
