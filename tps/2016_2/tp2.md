---
title: TP 2
---


TP2: utilidades con hashes, ABBs y heaps
========================================
{:.no_toc}

Este trabajo práctico es **grupal** y consiste de seis ejercicios, para los cuales se pueden utilizar los TDAs programados durante la cursada. La fecha de entrega es el viernes 11 de noviembre.

## Contenido
{:.no_toc}

1. TOC
{:toc}


# Ejercicios

## Hashes

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

Si bien en su versión original, `uniq` requiere que las repeticiones sean consecutivas, nuestra versión no tendrá esta restricción. Se debe imprimir cada palabra en orden de acuerdo a su primera aparición en el archivo. El tiempo de ejecución debe ser *O(n)* siendo *n* el número de palabras del archivo a analizar.

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

  - se deben imprimir solamente las palabras en común a ambos archivos.

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

En este ejercicio se pide una primitiva que en *O(n)* devuelva un arreglo con todos los datos del árbol (claves y valores), ordenados por *clave*. Para esto se deberá definir una estructura pública de la siguiente manera:

    typedef struct abb_item
    {
        const char* clave;
        void* valor;
    } abb_item_t;

La firma de la primitiva será la siguiente:

    abb_item_t* abb_obtener_items(const abb_t*);

El puntero devuelto apunta al primer elemento de un arreglo de *n* elementos, donde *n* es el número de elementos del árbol. Es, por tanto, equivalente un arreglo `abb_item[n]`:

    abb_item_t* items = abb_obtener_items(arbol);
    printf("primera clave = %s\n", items[0].clave);

El arreglo devuelto es liberado con free(). Las claves son propiedad del árbol y no deben ser destruidas.


## Heaps

### top-k

Se pide programar la función `top_k()`, que dado un arreglo de elementos y una función de comparación, nos devuelve un nuevo arreglo con los `k` elementos más chicos, en orden de menor a mayor:

    void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp);

Indicaciones:

  - el arreglo devuelto tendrá exactamente tamaño `k`. Si `k > n`, las últimas `k - n` posiciones son NULL.

  - la complejidad de la función debe ser *O(n log k)*.


### heap_actualizar_prioridad

Actualmente nuestra implementación de la cola de prioridad soporta agregar elementos, ver el más prioritario y extraerlo. En caso de que el usuario cambie la prioridad de algunos de los elementos, la estructura perdería el invariante.

En este ejercicio se propone agregar una función que dado un heap y un elemento se verifique si su prioridad es la correcta dentro del TDA y lo reacomode. Se trata de agregar una primitiva que actualice la prioridad de un elemento indicado:

    void heap_actualizar_prioridad(heap_t* heap, void* dato);

Esta función debería ser llamada por el usuario cada vez que actualice un elemento que está dentro del heap y deberá funcionar en orden lineal.

Diseñar esta nueva primitiva de manera tal que se comporte en orden _O(log n)_ si tuviésemos un índice con el cual podamos encontrar la ubicación del elemento cuya prioridad debe ser actualizada en orden sublineal.


# Consideraciones adicionales

Ver los apartados de [lectura de archivos](https://algoritmos-rw.github.io/fiuba-algo2-2c2016-tp1/enunciado/#lectura-de-archivos) y [deps.mk](https://algoritmos-rw.github.io/fiuba-algo2-2c2016-tp1/enunciado/#depsmk) del Trabajo Práctico 1.


# Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores de memoria. La entrega incluye, obligatoriamente, un informe en formato PDF y los siguientes archivos de código:

  * `uniq-count.c`
  * `comm.c`
  * `heap-utils.c` con la implementación de la función `top_k`.
  * `hash.c`, `abb.c` y `heap.c` (las implementaciones del grupo de estos TDA; incorporando las funciones adicionales pedidas en el presente trabajo, incluyendo los archivos .h actualizados).
  * un archivo `deps.mk` con las dependencias del proyecto en formato make.

Para la confección del informe, pueden revisar el [informe de ejemplo](https://drive.google.com/open?id=11ufmyqYKWt18Ty3Wg0fxtjqU7slRU-MT) disponible en el sitio de la materia.

La entrega se realiza:

  1. por mail a la casilla de TPs (`tps.7541rw@gmail.com`): todos los archivos mencionados en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. En el asunto deben indicar: `TP2 - <Padrón 1> - <Apellido 1> - <Padrón 2> - <Apellido 2>`.
  2. en papel durante la clase (si su ayudante lo requiere), tanto el informe como el código. **No es necesario reimprimir el código de los TDA (excepto las primitivas modificadas)**.

El informe deberá consistir de las siguientes partes:

  * carátula con los datos personales del grupo y el ayudante asignado.
  * análisis y diseño de la solución, en particular: algoritmos y estructuras de datos utilizados; orden de ejecución de cada programa o función.
