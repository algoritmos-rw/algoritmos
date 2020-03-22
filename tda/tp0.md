---
title: TP0
permalink: /tps/tp0/
trabajo: TP0
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Trabajo Práctico 0
==================

El adjunto en [el sitio de descargas]({{site.skel}}) contiene varios archivos.
Deben editar el archivo `tp0.c`, completando las cuatro funciones que
aparecen en el código fuente: `swap()`,  `maximo()`, `comparar()` y `seleccion()`.
(Los comentarios en el archivo indican qué debe hacer cada función).

El resto de archivos del zip no los deben modificar. Sí pueden, no obstante, leer el archivo `tp0_pruebas.c` para entender qué verificaciones realizaremos sobre su código.

La compilación se realiza en el estándar C99, con los siguientes flags:

    gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c

Las pruebas deben dar todas OK, y las pueden ejecutar con:

    ./pruebas

En la entrega de ser impresa en una hoja de papel, con su nombre y padrón, imprimiendo únicamente el archivo `tp0.c`.

Además, deben subir el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

**No olviden revisar los [primeros pasos en Linux](/algo2/faq/primeros-pasos) y las [preguntas frecuentes](/algo2/faq/).**
