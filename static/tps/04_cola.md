---
layout: page
title: Cola
permalink: /tps/cola
---

Cola Enlazada
=============

Se include en [cola.zip](https://sites.google.com/site/fiuba7541rw/tps/cola/cola.zip?attredirects=0&d=1) el archivo `cola.h` correspondiente al ejercicio de la cola enlazada para el viernes 15 de septiembre.

El ejercicio es muy similar al realizado para la pila.  Excepto que la función para destruir la cola recibe por parámetro una función para destruir uno a uno los elementos, que puede ser NULL en el caso de que no haya que destruirlos.

La cola debe ser enlazada, es decir que en lugar de estar implementada con un arreglo, está implementada mediante nodos enlazados, de los cuales se desencola el primero y se encola a continuación del último. Por tanto, se debe implementar solamente con punteros, y no se debe guardar en un campo el tamaño de la cola. 

Deben entregar un archivo `pruebas_alumno.c` que haga las correspondientes pruebas unitarias. Además de las pruebas obligatorias análogas a las pedidas para la [pila](pila), también tienen que incluir unas pruebas para probar la destrucción con y sin funciones de destrucción de los elementos.

Deberán entregar el código en papel, con el nombre y padrón, imprimiendo el archivo `cola.c` y el archivo `pruebas_alumno.c`.  

Además, deben subir el código a la [página de entregas de la materia](https://algoritmos7541-rw.tk/entregas/), con el código completo.
