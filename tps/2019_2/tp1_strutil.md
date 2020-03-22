---
title: TP1 - Parte 1 – Manejo cadenas
math: true
trabajo: TP1 (Parte 1) - Strutil
---
{% assign TP = site.data.trabajos[page.trabajo] %}

# Trabajo Práctico 1 (Primera parte)
{:.no_toc}

## Contenido
{:.no_toc}

* Contenido
{:toc}

El Trabajo Práctico número 1 parte 1 tiene fecha de entrega para el **21 de octubre** y
contempla la implementación de funciones auxiliares para cadenas ([`strutil`](#manejo-de-cadenas))

## Manejo de cadenas

Se pide implementar las funciones del archivo adjunto en [el sitio de descargas]({{site.skel}}) que se describen a
continuación. Se permite utilizar cualquier función de [string.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html), aunque se desaconseja el uso de `strtok`. Para la implementación de estas funciones no se puede hacer uso de TDAs.

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

La función `split()` divide una cadena en subcadenas por cada ocurrencia de un
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

Las pruebas del corrector automático proveen una indicación del comportamiento de `join()` (si bien **todas las
funciones deben correr en tiempo lineal**, `join()` provee una dificultad de implementación mayor a `split()` o
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


## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- `strutil.c` con las implementaciones de las funciones `substr`, `split`, `join` y `free_strv`.


El corrector va a compilar con los siguientes flags de `GCC`:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. En forma digital a través del [sistema de entregas]({{site.entregas}}):
todos los archivos mencionados en un único archivo ZIP.
2. En papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, sin informe ni carátula**.
