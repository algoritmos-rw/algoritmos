---
title: TP 1
layout: default
permalink: /:path/:basename/
---

TP 1: manejo de archivos y cadenas
==================================

Este trabajo práctico consiste en cuatro partes separadas, con fecha de entrega x de xx de 2016.

La entrega incluye, obligatoriamente, un informe en formato PDF y los siguientes archivos de código:

- `paste.c`
- `more.c`
- `bc.c`
- `strutil.c`
- `pila.c`, `cola.c` y `lista.c` (las implementaciones del alumno de estos TDA; se debe incluir los archivos .h también)
- un archivo `deps.mk` con las dependencias del proyecto en formato make

La entrega se realiza:

1. por mail a la casilla de TPs: todos los archivos mencionados en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. El asunto debe incluir el padrón del alumno (sin punto decimal) y nombre del TP (TP1 en este caso).
2. en papel durante la clase, tanto el informe como el código. El código se debe imprimir en fuente monoespacio; no se debe imprimir el código de los TDA.
Se puede incluir otros archivos fuente con funciones comunes, siempre que el orden de dependencias quede especificado en deps.mk.



# paste

Se pide implementar una utilidad similar al programa [paste](http://ss64.com/bash/paste.html), que dados dos archivos concatena su contenido de a líneas e imprime el resultado por salida estándar.

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


# more

En este ejercicio se pide implementar una simplificación de la utilidad de unix [more](http://ss64.com/bash/more.html) para mostrar por pantalla el contenido de un flujo.

El programa procesará lo enviado por entrada estándar, y deberá recibir por parámetro un número entero que indica la cantidad de líneas a ser mostradas por pantalla. Una vez mostradas las primeras N líneas, el programa imprimirá una nueva línea cada vez que el usuario envíe un salto de línea (con la tecla enter) por la entrada estándar.


# dc

Para este ejercicio se pide implementar una simplificación del programa [dc](http://ss64.com/bash/dc.html). Este programa procesará la entrada estándar y la interpretará como un cálculo en [notación polaca inversa](https://en.wikipedia.org/wiki/Reverse_Polish_notation), imprimiendo por salida estándar el resultado.

El siguiente será el comportamiento esperado:

    $ echo "4 2 +" | ./dc
    6
    $ echo "2 9 4 + \*" | ./dc
    26

Con las siguientes consideraciones:
- Los símbolos en la entrada pueden ser o bien números u operaciones. Todos ellos deben estar separados por espacios.
- Por simplicidad, sólo se esperan las siguientes operaciones: suma (+), resta (-), multiplicación (\*) y división.
- Si la entrada consta de varias líneas, se considerarán como cálculos independientes; y sus resultados se imprimirán de forma separada en líneas separadas.
- Si la expresión en la entrada no es válida, se interrumpirá inmediatamente el programa y se devolverá al sistema operativo un código de error.


# Manejo de cadenas
- split()
- join()
- free_strv()
