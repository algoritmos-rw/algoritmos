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

El Trabajo Práctico número 1 tiene fecha de entrega para el **viernes 19/10**, y
está divido en tres partes:
* implementación de funciones auxiliares para cadenas ([`strutil`](#manejo-de-cadenas))
* implementación de aplicaciones similares a comandos Unix: [`grep`](#grep) y [`dc`](#dc)


## Manejo de cadenas

Se pide implementar las funciones del archivo adjunto en [el sitio de descargas]({{site.skel}}) que se describen a continuación. Se permite utilizar cualquier función de [string.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html), aunque se desaconseja el uso de strtok. Para la implementación de estas funciones no se puede hacer uso de TDAs.

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

Complejidad algorítmica: se espera que la función tenga complejidad $$\mathcal{O}(n)$$ (Siendo $$n$$ la longitud de la cadena resultante).

### join

La función `join()` es la inversa de `split()`. Concatena un arreglo de cadenas terminado en NULL mediante un caracter de separación:

``` cpp
// Ejemplo de uso de join
char **strv = split("abc,def,ghi", ',');
char *resultado = join(strv, ';');  // "abc;def;ghi"

char **palabras = split("Hola mundo", ' ');
char *otro_resultado = join(palabras, ',');  // "Hola,mundo"
```

Casos borde:
``` cpp
join([""], ",")      →  ""
join(["abc"], ",")   →  "abc"
join(["", ""], ",")  →  ","
join([NULL], ",")    →  ""
```

Complejidad algorítmica: se espera que la función tenga complejidad $$\mathcal{O}(n)$$ (Siendo $$n$$ la longitud de la cadena resultante).

Las pruebas del corrector automático proveen una indicación del comportamiento de `join()` (si bien **ambas funciones deben correr en tiempo lineal**, `join()` provee una dificultad de implementación mayor a `split()`).

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

Si bien no es obligatorio probar la biblioteca, es muy recomendable hacer pruebas unitarias para comprobar el correcto funcionamiento, en particular para los casos borde.

## Aplicaciones

### Grep

Se pide implementar una versión simplificada de la utilidad [grep](http://man7.org/linux/man-pages/man1/egrep.1.html) de Unix.
`grep` imprime las líneas de un archivo, o de entrada estándar que cumpla con la expresión regular pasada por parámetro.

En nuestro caso, el programa va a recibir una cadena simple y va a chequear si esa cadena está contenida en cada línea del archivo o de la entrada estándar.
Nuestra implementación recibirá:
 - Una cadena, que va a ser la que se usará para  ver si esa cadena está contenida en cada línea del archivo o entrada estándar,
 - Un numero entero `N` que será la cantidad de líneas a mostrar por consola antes del "match" de la cadena y la línea leída
 - Opcionalmente un nombre de archivo que va a ser el archivo que grep va a tener que leer, si no recibe este parámetro, tiene que leer de entrada estándar.
Por ejemplo, usando el archivo `charla.txt`:

```
$ cat charla.txt
Hola!
Hola, como te va?
Bien, y a vos?
Espléndido, acá haciendo el tp1 de algo2
Uuuu q diverr
Se ...


$ ./grep vos 0 charla.txt
Bien, y a vos?

$ cat charla.txt | ./grep vos 0
Bien, y a vos?

$ ./grep vos 0 < charla.txt
Bien, y a vos?

$ cat charla.txt | ./grep vos 1
Hola, como te va?
Bien, y a vos?

$ cat charla.txt | ./grep vos 5
Hola!
Hola, como te va?
Bien, y a vos?

$ cat charla.txt | ./grep Hola 1
Hola!
Hola, como te va?

$ cat charla.txt | ./grep ien 0
Bien, y a vos?
Espléndido, acá haciendo el tp1 de algo2

$ cat charla.txt | ./grep ien 1
Hola, como te va?
Bien, y a vos?
Espléndido, acá haciendo el tp1 de algo2

$ cat charla.txt | ./grep umpalumpa! 1

$ ./grep "Hola, como te" 1 < charla.txt
Hola!
Hola, como te va?
```

#### Observaciones

- No se permite almacenar todo el archivo en memoria. Se puede almacenar, como máximo, `N + 1` líneas. Tampoco se permite el uso de archivos temporales.

- Se debe validar tanto que la cantidad de parámetros sea la correcta, como que el parámetro sea efectivamente un número. En caso de no contar con la cantidad de parámetros correctos se debe imprimir por salida de error (`stderr`) `"Cantidad de parametros erronea"`, y finalizar la ejecución. En caso que el parámetro no sea un número, se debe imprimir por salida de error (`stderr`) "Tipo de parametro incorrecto". En caso de estar presente el parámetro de la ruta del archivo, el mismo debe validarse que pueda abrirse para lectura. En caso contrario, debe imprimirse por salida de error `"No se pudo leer el archivo indicado"`, y finalizar la ejecución.

- Cabe notar que, al tratarse de entrada estándar, en ningún caso puede ser leída dos veces para averiguar el número de líneas primero.

- Todas las salidas deben hacerse por salida estándar (`stdout`) y en caso de que no haya ningún "match", no se debe imprimir nada.

- Se puede implementar una solución por _fuerza bruta_, que lugar a lugar vaya realizando las comparaciones de la subcadena sobre cada línea. Igualmente, recomendamos implementar una mejor solución, como puede ser el [algoritmo de Karp-Rabin](https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm), que utiliza funciones de hashing para mejorar la eficiencia temporal.


### dc

Se pide implementar un programa que permita realizar operaciones matemáticas. Este programa procesará la entrada estándar y la interpretará como un cálculo en [notación polaca inversa](https://en.wikipedia.org/wiki/Reverse_Polish_notation), imprimiendo por salida estándar el resultado.

```
$ cat scripts1.txt
10 5 + +
10 5 3 + *
10 sqrt 2 10 / 1 ?
2 2 2 2 * ^ log
?

$ ./dc < scripts1.txt
ERROR
80
5
4
ERROR
```

#### Operaciones
- Todas las operaciones trabajarán con números enteros, y devolverán números enteros.
- Las operaciones pueden ser: suma (`+`), resta (`-`), multiplicación (`*`), división (`/`), obtener la raíz (`sqrt`), obtener la potencia (`^`), obtener el logaritmo (`log`) y operador ternario (`?`).
- La operación de suma debe agarrar los dos últimos elementos y sumar el último con el anterior: `5 10 + → 10 + 5 = 15`
- La operación de resta debe agarrar los dos últimos elementos y restar el último con el anterior: `5 10 - → 10 - 5 = 5`
- La operación de multiplicación debe agarrar los dos últimos elementos y multiplicar el último con el anterior: `5 10 * → 10 * 5 = 50`.
- La operación de división debe agarrar los dos últimos elementos y dividir (de forma entera) el último por el anterior: `5 10 / → 10 / 5 = 2`, `3 10 / → 10 / 3 = 3`. En caso de encontrarse con que el divisor es 0, se considerará como un error.
- La operación de obtener la raíz agarra el último operando y obtiene la parte entera de la raíz de dicho operando: `5 10 sqrt → sqrt(10) = 3` dejando en la pila de ejecución `5 3`. En caso que el argumento sea negativo, se considerará como un error.
- La operación para obtener la potencia debe agarrar los últimos dos elementos y elevar el último por el anterior: `5 10 ^ → 10^5 = 100000`. En caso que el argumento del exponente sea negativo, se considerará como un error.
- La operación de obtener el logaritmo agarra los últimos dos operandos, y calcular la parte entera del logaritmo del último operando, en base del penúltimo: `5 10 log → log_5 (10) = 1`. En caso que la base sea un número menor o igual a 1, se considerará como un error.
- La operación del operador ternario debe agarrar los últimos 3 elementos. En caso que el último operando sea distinto de 0, debe devolver el penúltimo, en caso de ser 0 debe devolver el antepenúltimo: `5 10 0 ? → (0? 10 : 5) = 5`.
- En cualquiera de las operaciones, el resultado pasa a estar al tope de la pila, para ser usado por otros operadores (siempre y cuando no haya habido algún error).


#### Observaciones
- Cada línea de la entrada estándar debe tratase por separado.
- Los símbolos en la entrada pueden ser o bien números u operaciones. Todos ellos deben estar separados por espacios.
- Todas las salidas deben hacerse por salida estándar (`stdout`). En caso de error debe imprimirse `"ERROR"`, sin ningún tipo de resultado parcial. El programa debe continuar procesando la siguiente línea de entrada estándar.
- Los casos posibles de error pueden ser:
    * Cantidad de operandos inválidos para un operador
    * Al finalizar la ejecución queda más de un operando en la pila de ejecución.
    * Errores propios de cada operación.
- La operación para obtener la raíz debe ejecutar en $$\mathcal{O}(\log n)$$, siendo $$n$$ el valor del número al que se le calcula la raíz.
- La operación para obtener la potencia debe ejecutar en $$\mathcal{O}(\log e)$$, siendo $$e$$ el valor del exponente.
- La operación para obtener el logaritmo debe ejecutar en $$\mathcal{O}(\log n)$$, siendo $$n$$ el argumento del logaritmo.


## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- `strutil.c` con las implementaciones de las funciones `split`, `join` y `free_strv`.
- El código de la solución de `grep` y `dc`.
- El código de los TDAs programados en la cursada que se requieran.
- Un archivo `deps.mk` con las dependencias del proyecto en formato make. Este
deberá contener sólamente una línea por programa que indique qué _objetos_ necesita para
compilar el ejecutable de cada uno de los archivos, por ejemplo:

``` makefile
grep: grep.c
dc: dc.c tda.c
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
