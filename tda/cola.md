---
title: Cola
permalink: /tps/cola/
trabajo: Cola
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Cola enlazada
=============

Se incluye en [el sitio de descargas]({{site.skel}}) el archivo `cola.h` correspondiente al ejercicio de la cola enlazada.

La entrega es muy similar a la realizada para el TDA Pila.  Excepto que la función para destruir la cola recibe por parámetro una función para destruir uno a uno los elementos, que puede ser `NULL` en el caso de que no haya que destruirlos.

La cola debe ser enlazada, es decir que en lugar de usar un arreglo, usa nodos enlazados, de los cuales se desencola el primero y se encola a continuación del último. Por tanto, se debe implementar solamente con punteros, y no se debe guardar en un campo el tamaño de la cola.

Deben entregar un archivo `pruebas_alumno.c` que haga las correspondientes pruebas unitarias. Además de las pruebas obligatorias análogas a las pedidas para la [pila](pila.md), también tienen que incluir unas pruebas para probar la destrucción con y sin funciones de destrucción de los elementos.

Deberán entregar el código en papel, con el nombre y padrón, imprimiendo el archivo `cola.c` y el archivo `pruebas_alumno.c`.

Además, deben subir el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

**No olviden revisar las [preguntas frecuentes de la cola](/algo2/faq/cola)**

---
### Bibliografia recomendada
* Weiss, Mark Allen, "Data Structures and Algorithm Analysis": *3.4. The Queue ADT*.
* Cormen, Thomas H. "Introduction to Algorithms": *10.1. Stacks and queues*.
