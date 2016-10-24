---
title: TP 2
layout: default
permalink: /:path/:basename/
---

TP2: utilidades con hashes, ABBs y heaps
==================================

Este trabajo práctico es **grupal** y consiste de seis ejercicios, para los cuales se deberán utilizar los TDAs programados durante la cursada. La fecha de entrega es el lunes 7 de noviembre.

# Ejercicios

### uniq-count

Se pide programar una herramienta con una funcionalidad similar a la de la utilidad [uniq](http://ss64.com/bash/uniq.html) al ser invocada con la opción `-c`. Esta variante imprime un listado de todas las palabras de un archivo de texto, junto con su frecuencia.

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

Si bien en su versión original, `uniq` requiere que las líneas repetidas sean consecutivas, nuestra versión no tendrá esta restricción. Deberá imprimir cada palabra en orden de acuerdo a la primera aparición en *O(n)* siendo *n* el número de palabras del archivo a filtrar.

Se deberá validar que el programa reciba un único parámetro en su invocación, el nombre del archivo de texto.


### comm

Para este ejercicio se deberá implementar una simplificación de la funcionalidad [comm](http://ss64.com/bash/comm.html), que dado dos archivos ordenados clasifica en columnas las líneas que pertenecen sólo al primero, a ambos, o solo al segundo.

Nuestra variación recibirá dos parámetros (los archivos de texto) que, a diferencia de la versión original, no necesariamente deberán estar ordenados.
La implementación a realizar podrá recibir un parámetro extra (por lo que se debe validar que el número de parámetros recibidos sea de dos o tres).

Los parámetros extra son:

  - (ninguno): indica que en la salida se deben imprimir las palabras en común a ambos archivos.
  - `-1` indica que solamente se deben imprimir las palabras que son únicas para el primer archivo.
  - `-2` indica que solamente se deben imprimir las palabras que son únicas para el segundo archivo.

Se debe imprimir una palabra por línea y cada una de ellas debe aparecer una única vez en la salida (no es necesario que se impriman según el orden de aparición).

Por ejemplo, dado los siguientes dos archivos:

    $ cat nombres1.txt
    Carolina
    Daniel
    Bruno
    Alicia
    Alicia
    Lucía

    $ cat nombres2.txt
    Germán
    Alicia
    Federico
    Diego
    Bruno
    Lucila

Para cada invocación las salidas serán las siguientes:

    $ ./comm nombres1.txt nombres2.txt
    Bruno
    Alicia

    $ ./comm nombres1.txt nombres2.txt -1
    Carolina
    Daniel
    Lucía

    $ ./comm nombres1.txt nombres2.txt -2
    Germán
    Federico
    Diego
    Lucila



## Árboles binarios de búsqueda

### abb_iter_post_order

En este punto se pide agregar un nuevo par de iteradores al árbol que implementen un recorrido post-order. Se agregarán las siguientes primitivas:

Para el iterador interno:

    void abb_post_order(abb_t* arbol, bool (\*visitar)(const char*, void*, void*), void* extra);

Para el iterador externo se creará la estructura abb_iter_post_t:

    abb_iter_post_t* abb_iter_post_crear(const abb_t* arbol);
    bool abb_iter_post_avanzar(abb_iter_post_t* iter);
    const char* abb_iter_post_ver_actual(const abb_iter_post_t* iter);
    bool abb_iter_post_al_final(const abb_iter_post_t* iter);
    void abb_iter_post_destruir(abb_iter_post_t* iter);


### abb_obtener_lista

En este ejercicio se pide una primitiva que en *O(n)* devuelva un arreglo con todos los datos del árbol. Para esto se definirá una estructura de la siguiente manera:

    typedef struct abb_dato
    {
        const char* clave;
        void* valor;
    } abb_dato_t;

Por lo tanto, la firma de la primitiva será la siguiente:

    abb_dato_t** abb_obtener_lista(const abb_t*);

## Heaps

### top-k

Se pide programar la función `top-k`, que dado un arreglo de elementos y una función de comparación, nos devuelve un nuevo arreglo con los `k` elementos más grandes:

    void** top-k(void** datos, size_t n, cmp_func_t cmp);

  



### heap_actualizar_prioridad

Se trata de agregar una primitiva `void heap_actualizar_prioridad(const void* clave, void* valor)` que actualice la prioridad del elemento.
