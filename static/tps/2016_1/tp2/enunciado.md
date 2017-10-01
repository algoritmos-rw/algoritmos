---
title: TP 2
layout: default
permalink: /:path/:basename/
---

TP2: utilidades con hashes, ABBs y heaps
========================================

## Contenido
  1. [Ejercicios](#ejercicios)
      1. [uniq](#uniq)
      2. [join](#join)
      3. [abb_iter_crear_desde](#abbitercreardesde)
      4. [abb_rebalanceado](#abbrebalanceado)
      5. [multi-merge](#multi-merge)
      6. [TDA mediana](#tda-mediana)
  2. [Condiciones de entrega](#condiciones-de-entrega)  
  3. [Criterios de aprobación](#criterios-de-aprobacin)

## Ejercicios

### uniq

Se pide programar una utilidad similar al programa [uniq](http://ss64.com/bash/uniq.html), que dada una entrada de texto la imprime ignorando las líneas repetidas.

En la versión original, uniq sólo filtra las líneas repetidas que son consecutivas. Nuestra versión no debe tener esta restricción. Debe imprimir las líneas en orden de acuerdo a la primera aparición y debe funcionar en O(n) siendo n el número de líneas del archivo a filtrar.

Entonces, ante la siguiente entrada:

    $ cat nombres.txt
    Carolina
    Daniel
    Bruno
    Daniel
    Alicia
    Carolina


La salida deberá ser la siguiente:

    $ ./uniq nombres.txt
    Carolina
    Daniel
    Bruno
    Alicia

El programa podrá almacenar todo el contenido del archivo en memoria.


### join

Se pide implementar un programa similar a [join](http://ss64.com/bash/join.html), que dados dos archivos de registros imprime una junta interna entre los dos.

Por simplicidad consideraremos que los registros en los archivos están separados por saltos de líneas, y los campos en los registros están separados por espacios.

De esta manera ante los siguientes archivos:

    $ cat fechas.txt
    Nombre Dia Mes Año
    Carolina 2 12 2007
    Bruno 4 12 1996
    Alicia 11 12 2013

    $ cat ciudades.txt
    Nombre Ciudad
    Bruno Rosario
    Daniel Córdoba
    Carolina Lanús

La salida deberá ser:

    $ ./join fechas.txt ciudades.txt
    Nombre Dia Mes Año Ciudad
    Carolina 2 12 2007 Lanús
    Bruno 4 12 1996 Rosario

Tener en cuenta las siguientes consideraciones:
- El campo por el que se hace la junta es el primero de cada archivo.
- Se imprimen las columnas de los dos archivos.
- Los registros que forman parte del resultado son los que aparecen en los dos archivos.
- El orden de los registros de salida es aquél del primer archivo de entrada.

El programa debe funcionar en orden O(n + m), siendo n y m la longitud de cada archivo.


### abb_iter_crear_desde

Se pide programar una nueva primitiva para el árbol binario de búsqueda con la siguiente firma:

    abb_iter_t* abb_iter_crear_desde(abb_t* arbol, const char* clave_desde, const char* clave_hasta);

La función debe crear un iterador in order que al crearse estará posicionado en el nodo con `clave_desde` (o en caso de que el árbol no tenga esa clave, en la primera superior a esa), y debe iterar hasta encontrar la `clave_hasta` (o en caso de no existir, a la última menor a esa), inclusive. Una vez superado ese valor el iterador estará siempre al final.

El parámetro `clave_hasta` puede ser `NULL`. En ese caso el iterador iterará hasta el último nodo inorder.

Para implementar esta primitiva será necesario modificar la estructura interna del iterador del árbol.


Por ejemplo, dado el siguiente árbol:

![ABB ejemplo](http://cramster-image.s3.amazonaws.com/definitions/computerscience-5-img-1.png)

Los valores de la iteración en cada una de las siguientes invocaciones deberán ser:

- `abb_iter_crear_desde(4, 9)`: 4, 5, 6, 7, 9
- `abb_iter_crear_desde(7, NULL)`: 7, 9, 17, 20, 22
- `abb_iter_crear_desde(4, 8)`: 4, 5, 6, 7
- `abb_iter_crear_desde(13, 22)`: 17, 22
- `abb_iter_crear_desde(9, 4)`: -


### abb_rebalanceado

Se pide programar una función externa (no primitiva) con la siguiente firma:

    void abb_rebalanceado(abb_t* orig, abb_t* dest);

que dado un árbol binario de búsqueda añada a otro árbol inicialmente vacío todos sus elementos en un orden de inserción tal, que el árbol destino quede balanceado.

En un árbol balanceado se cumple _para todos los nodos_ (no solo la raíz) que la diferencia de altura entre su subárbol izquierdo y su subárbol derecho es 0 o 1.

La función debe ser O(n log n), siendo n la cantidad de nodos del árbol.


### multi-merge

Se tienen k archivos cuyas líneas aparecen en orden. Se desea unirlos por salida estándar de manera que la secuencia siga ordenada (parecido a como hace merge-sort).

Los archivos pueden ser arbitrariamente grandes (no entran en memoria), y k puede también serlo. Si en total hay n líneas, se pide implementar un algoritmo que permita realizar la unión en O(n log k) tiempo, sin mantener en memoria más de k líneas.

Además: el número de alloc/realloc debe ser proporcional a k, no a n. Si, por ejemplo, se usa la función getline(), los buffers deben ser reusados cuando corresponda.

Uso:

    ./multi-merge arch1 arch2 arch3 ... archN


### TDA mediana

Implementar un TDA que permita calcular la mediana para una secuencia de números diferentes que se le ingresarán. El TDA debe contar con las siguientes primitivas:

  - `mediana_t* calculador_mediana_crear();`, que deberá inicializar el TDA en O(1).

  - `bool calculador_mediana_agregar_valor(mediana_t* mediana, double valor);`, que agregará un valor a la estructura en O(log n). Esta primitiva devolverá `true` cuando se agrega el valor exitosamente y `false` en caso contrario.

  - `double calculador_mediana_obtener_mediana(mediana_t* mediana);`, que devolverá la mediana de acuerdo a los elementos que le fueron ingresados en O(1).

  - `void calculador_mediana_destruir(mediana_t* mediana);`, que destruirá la estructura en O(n).


## Condiciones de entrega

Este trabajo práctico consiste de seis ejercicios con fecha de entrega **3 de junio de 2016**.
La entrega incluye, obligatoriamente, un informe en formato PDF y los siguientes archivos de código:

  - `uniq.c`
  - `join.c`
  - `abb.c` y `abb.h` con el nuevo iterador implementado.
  - `abb_utils.c` con la función `abb_rebalancear`.
  - `multi-merge.c`
  - `mediana.c` y `mediana.h`
  - `deps.mk`, el archivo de dependencias con las mismas consideraciones que se tuvieron en el [TP1](https://algoritmos-rw.github.io/prog2/tp1/#deps.mk).

La entrega se realiza:

  1. por mail a la casilla de TPs: todos los archivos mencionados en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. El asunto debe incluir el padrón del alumno (sin punto decimal) y nombre del TP (TP1 en este caso).

  2. en papel durante la clase, tanto el informe como el código. El código se debe imprimir en fuente `monoespacio`; no se debe imprimir el código de los TDA.

Se puede incluir otros archivos fuente con funciones comunes, siempre que el orden de dependencias quede especificado en `deps.mk`.


## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores de memoria (ver el uso de Valgrind a continuación).

El informe deberá consistir de las siguientes partes:

  - carátula con los datos personales del alumno y el ayudante asignado.
  - análisis y diseño de la solución, en particular: algoritmos y estructuras de datos utilizados; orden de ejecución de cada programa o función.
