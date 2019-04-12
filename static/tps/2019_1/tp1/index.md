---
layout: page
title: TP1 – Manejo de archivos, cadenas y TDAs básicos
permalink: '/tps/2019_1/tp1'
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
* implementación de verificador e interprete del lenguaje [Brainfuck](https://es.wikipedia.org/wiki/Brainfuck)
* TODO: 3er parte

## Manejo de cadenas

Se pide implementar las funciones del archivo adjunto en [el sitio de descargas]({{site.skel}}) que se describen a 
continuación. Se permite utilizar cualquier función de [string.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/string.h.html), aunque se desaconseja el uso de strtok. Para la implementación de estas funciones no se puede hacer uso de TDAs.

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

### join

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
join([""], ",")      →  ""
join(["abc"], ",")   →  "abc"
join(["", ""], ",")  →  ","
join([NULL], ",")    →  ""
```

Complejidad algorítmica: se espera que la función tenga complejidad $$\mathcal{O}(n)$$ (Siendo $$n$$ la longitud de la 
cadena resultante).

Las pruebas del corrector automático proveen una indicación del comportamiento de `join()` (si bien **ambas funciones 
deben correr en tiempo lineal**, `join()` provee una dificultad de implementación mayor a `split()`). 

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

## Aplicaciones

### Brainfuck
Los amigos del instituto del cerebro nos pidieron que implementemos un interprete del famoso lenguaje llamado 
[Brainfuck](https://es.wikipedia.org/wiki/Brainfuck), este lenguaje cuenta con las caracteristicas que tiene muy pocas 
instrucciones posibles (solo 7) y tambien por tener un compilador/interprete muy pequeño y facil de implementar.

Un link util para probar este lenguaje es este [interprete online](https://copy.sh/brainfuck/).

Su mision es implementar un interprete de Brainfuck en el lenguaje C.  
Para ello se van a exponer dos posibles formas: `validate` y `run`, con el formato:
```
./bf < modo > <nombre de archivo> 
```
Donde `< modo >` puede ser `-v` o `-r` y `< nombre de archivo >` es el nombre del archivo (este parametro puede no 
estar y entonces se leerá de entrada estandar). En el caso que se pase una cantidad de parametros incorrecta se 
devolverá por salida estandar `ERROR`

### Modo validate (-v)
Cuando se llama al programa con validate (-v), este recibe el codigo a validar, puede ser pasandole un nombre de archivo 
o por entrada estandar. 
El programa entonces realizará una validación del codigo para verificar que este este correctamente escrito. En caso que
el codigo este bien, devuelve `OK`, sino `ERROR`.
Se considera que un codigo está correcto cuando todas los corchetes que se abren (`[`) tiene su respectivo corchete que 
cierra (`]`).

Ej de llamada con un archivo:  
```
./bf -v hellow_world.txt 
OK
```  
Ej de llamada con un archivo invalido:  
```
./bf -v archivo_invalido.txt 
ERROR
```  
Ej de llamada pasandole el codigo por entrada estandar:
```
cat hellow_world.txt | ./bf -v
OK
```

### Modo run (-r)
Cuando se llama al programa con run (-r), este recibe el codigo a correr, puede ser pasandole un nombre de archivo 
o por entrada estandar. El programa primero valida si el codigo está correctamente escrito en el caso de que este 
correctamente escrito, procederá a ejecutarlo y mostrará por salida estandar el resultado de el programa ejecutandose. 
En el caso de que el codigo no esté correctamente escrito, o que no exista, se tiene que devolver `ERROR`


Ej 1 - Ejecucion de un archivo correctamente, que escribe Hello World! por salida estandar:  
```
./bf -r hellow_world.txt
Hello World!
```

Ej 2 - Ejecucion del mismo archivo del Ej 1, pero ahora pasado por entrada estandar :
```
cat hellow_world.txt | ./bf -r
Hello World!
``` 
 
Ej 3 - Ejecucion fallida de un archivo incorrectamente:
```
cat <nombre de archivo> | ./bf -r
ERROR
```
Ej 4 - Ejecucion fallida con cantidad de argumentos incorrecto:
```
./bf hellow_world.txt
ERROR
```

#### Observaciones

TODO

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- `strutil.c` con las implementaciones de las funciones `split`, `join` y `free_strv`.
- El código de la solución de `bf` y `dc`.
- El código de los TDAs programados en la cursada que se requieran.
- Un archivo `deps.mk` con las dependencias del proyecto en formato make. Este
deberá contener sólamente una línea por programa que indique qué _objetos_ necesita para
compilar el ejecutable de cada uno de los archivos, por ejemplo:

``` makefile
bf: bf.c 
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
