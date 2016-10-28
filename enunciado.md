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

    $ cat palabras.txt
    hola adiós saludos beso ciao
    hola mundo
    adiós mundo cruel
    saludos terrícolas un beso

La salida deberá ser la siguiente:

    $ ./uniq-c nombres.txt
    2 hola
    2 adiós
    2 saludos
    2 beso
    1 ciao
    2 mundo
    1 cruel
    1 terrícolas
    1 un

Si bien en su versión original, `uniq` requiere que las repeticiones sean consecutivas, nuestra versión no tendrá esta restricción. Se debe imprimir cada palabra en orden de acuerdo a su primera aparición en el archivo. El tiempo de ejecución debe ser *O(n)* siendo *n* el número de palabras del archivo a filtrar.

Se deberá validar que el programa reciba un único parámetro en su invocación, el nombre del archivo de texto.

Indicaciones:

  - se puede asumir que las palabras están separadas por *un* solo espacio

  - no es necesario convertir mayúsculas a minúsculas; “hola” y “Hola” se cuentan por separado

  - no es necesario detectar signos de puntuación u otros caracteres no alfanuméricos; de estar presentes, simplemente formarán parte de la palabra (debiéndose contar “hola.” y “hola” por separado).

  - podría haber en el archivo líneas vacías (sin ningún otro caracter más que `\n`)


### comm

Para este ejercicio se deberá implementar una simplificación de la funcionalidad [comm](http://ss64.com/bash/comm.html), que dado dos archivos ordenados clasifica en columnas las líneas que pertenecen sólo al primero, a ambos, o solo al segundo.

Nuestra variante recibirá siempre dos parámetros (los archivos de texto) más un tercer parámetro opcional que indica qué conjunto de líneas imprimir. De estar presente, este tercer parametro puede tomar los siguientes valores:

  - `-1` indica que solamente se deben imprimir las palabras que son únicas para el primer archivo.
  - `-2` indica que solamente se deben imprimir las palabras que son únicas para el segundo archivo.

De no estar presente (es decir, solo se pasaron dos argumentos):

  - se deben imprimir las palabras en común a ambos archivos.

Por tanto, los casos válidos de invocación son:

  - dos parámetros
  - tres parámetros, siendo el tercero la cadena `-1` o bien la cadena `-2`

Se debe imprimir una palabra por línea y cada una de ellas debe aparecer una única vez en la salida (no es necesario que se impriman según el orden de aparición). A diferencia de la versión original de *comm*, los archivos no necesariamente estarán ordenados.


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

    void abb_post_order(abb_t* arbol, bool (*visitar)(const char*, void*, void*), void* extra);

Para el iterador externo se creará la estructura abb_iter_post_t:

    abb_iter_post_t* abb_iter_post_crear(const abb_t* arbol);
    bool abb_iter_post_avanzar(abb_iter_post_t* iter);
    const char* abb_iter_post_ver_actual(const abb_iter_post_t* iter);
    bool abb_iter_post_al_final(const abb_iter_post_t* iter);
    void abb_iter_post_destruir(abb_iter_post_t* iter);


### abb_obtener_items

En este ejercicio se pide una primitiva que en *O(n)* devuelva un arreglo con todos los datos del árbol (claves y valores), ordenados por clave. Para esto se definirá una estructura pública de la siguiente manera:

    typedef struct abb_item
    {
        const char* clave;
        void* valor;
    } abb_item_t;

La firma de la primitiva será la siguiente:

    abb_item_t* abb_obtener_items(const abb_t*);

El puntero devuelto apunta al primer elemento de un arreglo de *N* elementos, donde *N* es el número de elementos del árbol. Es, por tanto, equivalente un arreglo `abb_item[N]`:

    abb_dato_t *items = abb_obtener_items(arbol);
    printf("primera clave = %s\n", items[0].clave);

El arreglo devuelto debe ser liberado con free(). Las claves son propiedad del árbol y no deben ser destruidas.


## Heaps

### top-k

Se pide programar la función `top_k()`, que dado un arreglo de elementos y una función de comparación, nos devuelve un nuevo arreglo con los `k` elementos más grandes:

    void** top_k(void** datos, size_t tam_datos, cmp_func_t cmp);

Indicaciones:

  - el arreglo tiene exactamente `k` posiciones. Si `k > n`, las últimas `k - n` posiciones del arreglo son NULL.

  - la complejidad de la función debe ser *O(n log k)*.


### heap_actualizar_prioridad

Se trata de agregar una primitiva `void heap_actualizar_prioridad(const void* clave, void* valor)` que actualice la prioridad del elemento.
