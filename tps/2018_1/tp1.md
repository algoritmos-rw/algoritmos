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

El Trabajo Práctico número 1 tiene fecha de entrega para el **lunes 14/05**, y
está divido en tres partes:
* implementación de funciones auxiliares para cadenas ([`strutil`](#manejo-de-cadenas))
* implementación de aplicaciones similares a comandos Unix: [`tail`](#tail) y [`diff`](#diff).
* implementación de un programa [`syntax_val`](#syntax-validation).


## Manejo de cadenas

Se pide implementar las funciones del archivo [{{TP.zip}}]({{TP.zip_link}}) que se describen a continuación. Se permite utilizar cualquier funcion de [string.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html), aunque se desaconseja el uso de strtok. Para la implementación de estas funciones no se puede hacer uso de TDAs.

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


### free_strv()

`free_strv()` libera la memoria asociada con un arreglo dinámico de cadenas dinámicas:

## Aplicaciones

### Tail

Se pide implementar una versión simplificada de la utilidad [tail](http://man7.org/linux/man-pages/man1/tail.1.html) de Unix.
`tail` imprime las últimas `N` lineas de un archivo, o de entrada estándar.

En nuestro caso, el programa no acepta nombre de archivo y siempre trabaja con entrada estándar. Nuestra implementación acepta un número entero `N` como único argumento. Por ejemplo, usando el archivo `nombres.txt`:
```
$ cat nombres.txt
Alicia
Bruno
Carolina
Daniel
$ cat nombres.txt | ./tail 2
Carolina
Daniel
$ cat nombres.txt | ./tail 1
Daniel
$ cat nombres.txt | ./tail 4
Alicia
Bruno
Carolina
Daniel
$ cat nombres.txt | ./tail 100
Alicia
Bruno
Carolina
Daniel
```

#### Observaciones

- No se permite almacenar todo el archivo en memoria. Se puede almacenar, como máximo, `n + 1` líneas. Tampoco se permite el uso de archivos temporales.

- Se debe validar tanto que la cantidad de parámetros sea la correcta, como que el parámetro sea efectivamente un número. En caso de no contar con la cantidad de parámetros correctos se debe imprimir por salida de error "Cantidad de parametros erronea", y finalizar la ejecución. En caso que el parámetro no sea un número, se debe imprimir por salida de error "Tipo de parametro incorrecto".

- Cabe notar que, al tratarse de entrada estándar, en ningún caso puede ser leída dos veces para averiguar el número de líneas primero.

### Diff

Se pide implementar una versión muy simplificada de la utilidad [diff](http://man7.org/linux/man-pages/man1/diff.1.html) de Unix.
`diff` recibe dos archivos por comando, y muestra las líneas diferentes entre uno y otro archivo.

```
$ cat nombres1.txt
Alicia
Bruno
Carolina
Daniel
$ cat nombres2.txt
Alicia
Bruno
Roberto
Daniel
$ cat nombres3.txt
Alicia
Carolina
Alberto
$ ./diff nombres1.txt nombres1.txt
$ ./diff nombres1.txt nombres2.txt
Diferencia en linea 3
< Carolina
---
> Roberto
$ ./diff nombres2.txt nombres1.txt
Diferencia en linea 3
< Roberto
---
> Carolina
$ ./diff nombres1.txt nombres3.txt
Diferencia en linea 2
< Bruno
---
> Carolina
Diferencia en linea 3
< Carolina
---
> Alberto
Diferencia en linea 4
< Daniel
---
>
```

#### Observaciones

- Las lineas se comienzan a contar desde 1
- No se pueden almacenar los archivos en memoria. Se debe trabajar en memoria con una línea por archivo.
- Todas las diferencias deben escribirse en salida estándar (`stdout`).
- Se debe validar que se reciban dos parametros exactamente. En caso de recibirse más, o bien menos, debe indicarse por salida de error: `"Cantidad de parametros erronea"`.
- Se debe validar que ambos archivos existan. En caso que alguno no exista (o bien no se tengan permisos de lectura), imprimir por salida de error (`stderr`): `"Archivo erroneo"`.
- En caso que los archivos no tengan la misma cantidad de líneas (como en el último ejemplo), se debe imprimir las diferencias, como si se estuviera comparando contra una cadena vacía.

## Syntax Validation

Se pide implementar un programa que permita realizar validaciones a scripts que contengan secuencias de paréntesis, llaves o corchetes. El programa debe leer las líneas de entrada estándar, donde cada una de dichas líneas sean secuencias a validar, e indicar si las secuencias se encuentran correctamente balanceadas. Adicionalmente, en caso de encontrarse encerradas dentro de comillas simples las cadenas, no deben considerarse para determinar si la secuencia se encuentra balanceada.

```
$ cat scripts1.txt
[]
[()]
[(){}]
[[[[[]]]]]
[[(({}))]]
[hola mundo]
$ cat scripts1.txt | ./syntax_val
OK
OK
OK
OK
OK
OK
$ cat script2.txt
[]()
[(])
()(
[(}]
$ cat scripts2.txt | ./syntax_val
OK
ERROR
ERROR
ERROR
$ cat script3.txt
['hola']
('mundo')
[']']
[]'hola'
[']
[]'
$ cat scripts3.txt | ./syntax_val
OK
OK
OK
OK
ERROR
ERROR
```

#### Observaciones

- Todas las salidas deben hacerse por salida estándar (`stdout`).

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- `strutil.c` con las implementaciones de las funciones `split`, `join` y `free_strv`.
- el código de la solución de `tail`, `diff` y `syntax_val`.
- el código de los TDAs programados en la cursada que se requieran, con las
modificaciones que sean necesarias.
- un archivo `deps.mk` con las dependencias del proyecto en formato make. Este
deberá contener sólamente una línea por programa que indique qué _objetos_ necesita para
compilar el ejecutable de cada uno de los archivos, por ejemplo:

``` makefile
tail: tail.c
syntax_val: syntax_val.c
diff: diff.c tda.o
```

El corrector automático va a interpretar ese archivos de dependencias y va a
compilar todos los `.o` especificados a partir de los `.h` y `.c` que deberán
enviar, con los siguientes flags de `GCC`:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. en forma digital a través del [sistema de entregas]({{site.entregas}}):
todos los archivos mencionados en un único archivo ZIP.
2. en papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, informe ni carátula**. No es necesario
reimprimir el código de los TDA.
