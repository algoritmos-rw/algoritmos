---
title: TP 2
layout: default
permalink: /:path/:basename/
---

TP2: utilidades con hashes, ABBs y heaps
==================================

# Ejercicios

## Hashes

### uniq-count

Se pide programar un programa con una funcionalidad similar a la de la utilidad [uniq](http://ss64.com/bash/uniq.html) al ser invocada con la opción `-c`. Esta variante imprime un listado de todas las palabras de un archivo de texto, junto con su frecuencia.

Por ejemplo, ante la entrada:

    $ cat nombres.txt
    Carolina
    Daniel
    Bruno
    Alicia
    Alicia
    Carolina

La salida deberá ser la siguiente:

    $ ./uniq nombres.txt
    2 Carolina
    2 Daniel
    1 Bruno
    2 Alicia

En la versión original, `uniq` requiere que las líneas repetidas sean consecutivas. Nuestra versión no debe tener esta restricción. Debe imprimir cada palabra en orden de acuerdo a la primera aparición y debe funcionar en $O(n)$ siendo $n$ el número de palabras del archivo a filtrar.

### comm

Estoy pensando en hacer algo similar a [comm](http://ss64.com/bash/comm.html).


## Árboles binarios de búsqueda

### abb_iter_post_order

Un iterador nuevo, post order.

### abb_obtener_lista

Que en $O(n)$ devuelvan una lista de nodos del abb. La única manera que se puede hacer en O(n) con nuestra implementación es con el iterador interno.

También podría hacerse que devuelva un arreglo, para que vean la muy elegante forma de resolverlo usando doble punteros.

## Heaps

### TDA cuantil

Similar al de la mediana del año pasado, pero este si le especificás el 20% te tiene que dar el elemento que está en el 20%. Es como una mediana que se va adaptando de acuerdo a la cantidad de elementos que tenga.

### top-k

Este fue descartado el cuatri pasado, quiero los k elementos más prioritarios.

### heap_actualizar_prioridad

Se trata de agregar una primitiva `void heap_actualizar_prioridad(const void* clave, void* valor)` que actualice la prioridad del elemento.
