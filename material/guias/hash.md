---
math: true
---

# Diccionarios, Hashing y Hash
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

1. Para un hash cerrado, implementar una primitiva `lista_t* hash_claves(const hash_t*)` que reciba
un hash y devuelva una lista con sus claves.

1. Repetir lo mismo para un hash abierto.

1. Implementar de nuevo la operación, en este caso como una función.
{:.lower_alpha}

### Solución

Partiendo del punto _a)_, es importante notar que no podemos utilizar el iterador externo, ya que se trata de una primitiva para
el hash (y es una mala práctica que, dado que el iterador dependa del hash, ahora hagamos que el hash dependa del iterador).

#### Hash Cerrado

Para este punto, sólo es necesario iterar campo por campo, considerando únicamente aquellos que están ocupados.

```cpp
lista_t* hash_claves(const hash_t* hash) {
    lista_t* claves = lista_crear();
    if (!claves) {
        return NULL;
    }
    for (size_t i = 0; i < hash->tam; i++) {
        // valor de un enum definido para el hash
        if (hash->tabla[i].estado == OCUPADO) {
            lista_insertar_ultimo(claves, hash->tabla[i].clave);
        }
    }
    return claves;
}
```

Es importante notar que en este ejercicio se está evaluando que sabemos trabajar internamente con el hash cerrado. Los puntos importantes:

* Sabemos cuáles son los campos de la estructura.

* Sabemos que la tabla es de tipo `campo_t*`, y no `campo_t**`, puesto que es completamente innecesario un segundo grado de indirección (como se analiza en la respectiva clase práctica).

* Entendemos que el estado correcto a considerar es el de `OCUPADO`, que es un enumerativo. Cuanto mucho, una constante. Definitivamente no un `"ocupado"`.


#### Hash Abierto

Para este caso, consideramos todas las listas, las cuales podemos ir iterando utilizando el iterador externo o interno. Aquí mostramos una implementación utilizando el iterador interno, no porque sea mejor implementación, sino para que tengan un ejemplo de uso.

```cpp
lista_t* hash_claves(const hash_t* hash) {
   lista_t* claves = lista_crear();
    if (!claves) {
        return NULL;
    }
    for (size_t i = 0; i < hash->tam; i++) {
        lista_iterar(hash->tabla[i], insertar_clave, claves);
    }
    return claves;
}

bool insertar_clave(void* dato, void* extra) {
    lista_t* claves = extra;
    par_clave_valor_t* par = dato;
    lista_insertar_ultimo(claves, par->clave);
    return true;
}
```

_Aclaración_: Hay quienes deciden implementar el Hash Abierto de tal forma que
no tenga listas vacías (esto es, si una posición aún
no ha sido utilizada, entonces se guarda `NULL` y se crea la lista cuando sea necesaria). Esto es totalmente válido, y en todo
caso con aclararlo en algún lado es suficiente (pero debe hacerse la validación contra `NULL` en ese caso).

#### Función

En este caso, no sólo sí está permitido utilizar el iterador externo del hash,
sino que **no nos queda otra opción**, dado que no es posible acceder a los
campos internos de la estructura. Además, en particular no se nos dice cuál es la implementación, cosa que no es necesario conocer.

Entonces, simplemente iteramos utilizando el iterador externo y guardamos en una lista.

```cpp
lista_t* hash_claves(const hash_t* hash) {
   lista_t* claves = lista_crear();
    if (!claves) {
        return NULL;
    }
    hash_iter_t* iter = hash_iter_crear(iter);
    if (!iter) {
        lista_destruir(claves);
        return NULL;
    }
    while (!hash_iter_al_final(iter)) {
        char *clave = hash_iter_ver_actual(iter);
        lista_insertar_ultimo(claves, clave);
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return claves;
}
```

## Ejercicios propuestos

1.  (★) Suponer que se tiene un hash cerrado que se redimensiona cuando el factor de carga llega a 0.75, y que
    no se tienen en cuenta los elementos borrados a la hora de calcular el factor de carga.

    {:.lower_alpha}
    1. Describir, en términos generales, el peor escenario posible para esta implementación.

    1. Dado un hash de estas características, con capacidad inicial 100, calcular el número máximo de casillas que podría llegar a visitar `hash_obtener()` si la cantidad actual de elementos en el hash es 1, y no se realizó ningúna redimensión, pero sí se insertaron y borraron elementos. (En otras palabras, poner una cota superior al caso peor de este hash.)

1.  (★) ¿Para qué casos la función `hash_obtener()` tiene una complejidad peor que $$\mathcal{O}(1)$$? Explicar tanto para el hash abierto, como el cerrado.

1.  (★) Justificar si la siguiente función de hashing es correcta o no:
    ```cpp
    size_t calcular_hash(char *clave, size_t largo) {
        // rand() devuelve un numero entero positivo aleatorio
        return rand() % largo;
    }
    ```

1.  (★★) a. Mostrar el resultado de las siguientes operaciones tanto para un hash cerrado como para un hash abierto,
    ambos de capacidad 9 e inicialmente vacíos (los números son también el resultado de la función de hashing): insertar 17, insertar 22,
    insertar 35, borrar 17, insertar 52, insertar 54.

    b. Tras estas inserciones ¿qué pasos hay que seguir para verificar si el 70 pertenece al hash?

    c. Posteriormente se realizan más inserciones. ¿Cuándo redimensionaría cada hash?
    ¿Qué pasos hay que seguir para hacerlo?

1.  (★★) Implementar una función de orden $$\mathcal{O}(n)$$ que dado un arreglo de _n_ números enteros devuelva `true`
    o `false` según si existe algún elemento que aparezca más de la mitad de las veces. Justificar el orden de
    la solución. Ejemplos:

        [1, 2, 1, 2, 3] -> false
        [1, 1, 2, 3] -> false
        [1, 2, 3, 1, 1, 1] -> true
        [1] -> true

1.  (★★) Asumiendo que se tiene disponible una implementación completa del TDA Hash, se desea implementar una función
    que decida si dos Hash dados representan o no el mismo Diccionario. Considere para la solución que
    es de interés la mejor eficiencia temporal posible. Indique, para su solución, eficiencia en tiempo y espacio.
    Nota: Dos tablas de hash representan el mismo diccionario si tienen la misma cantidad de elementos; todas las claves
    del primero están en el segundo; todas las del segundo, en el primero; y los datos asociados a cada una de esas claves son iguales (se pueden comparar los
    valores con "==").

1.  (★★) Implementar el TDA MultiConjunto. Este es un Conjunto que permite más de una aparición de un elemento,
    por lo que eliminando una aparición, el elemento puede seguir perteneciendo. Dicho TDA debe tener como
    primitivas:
    * `multiconj_t* multiconj_crear()`: crea un multiconjunto. A fines del parcialito, no es necesario
    implementar la primitiva de destruir.
    * `bool multiconj_guardar(multiconj_t* multiconj, char* elem)`: guarda un elemento
    en el multiconjunto. Devuelve `true` si se pudo guardar el elemento correctamente, `false` en caso
    contrario.
    * `bool multiconj_pertenece(multiconj_t* multiconj, char* elem)`: devuelve `true` si el elemento aparece
    al menos una vez en el conjunto.
    * `bool multiconj_borrar(multiconj_t* multiconj, char* elem)`: elimina *una aparición* del elemento
    dentro del conjunto. Devuelve `true` si se eliminó una aparición del elemento.

    Dar la estructura del TDA y la implementación de las 4 primitivas marcadas, de forma tal que todas sean
    $$\mathcal{O}(1)$$.

1.  (★★★) Se tiene un hash que cuenta con una función de hashing que, recibida una clave,
    devuelve la posición de su inicial en el abecedario. La capacidad inicial del hash
    es 26. Para los puntos B, C y D indicar y justificar si las afirmaciones son
    verdaderas o falsas. Se puede considerar que todas las claves serán palabras
    (sólo se usan letras para las claves).

    a. Mostrar cómo quedan un hash abierto y un hash cerrado (sólo el resultado final)
    tras guardar las siguientes claves: Ambulancia (0), Gato (6), Manzana (12), Ananá (0),
    Girasol (6), Zapato (25), Zapallo (25), Manzana (12), Bolso (1).
    _Aclaración_: No es necesario hacer una tabla de 26 posiciones, lo importante es que
    quede claro en cuál posición está cada elemento.

    b. En un hash **abierto** con dicha función de hashing, se decide redimensionar cuando la
    cantidad alcanza la capacidad (factor de carga = 1). El rendimiento de
    `hash_obtener()` es mejor en este caso respecto a si se redimensionara al alcanzar
    un factor de carga 2.

    c. En un hash **cerrado** con dicha función de hashing, si se insertan `n + 1` claves diferentes
    (considerar que se haya redimensionado acordemente), `n` con la misma letra
    inicial, y 1 con otra distinta, en el primer caso `obtener()` es $$\mathcal{O}(n)$$ y en el
    segundo siempre $$\mathcal{O}(1)$$.

    d. En un hash **abierto** con dicha función de hashing, si se insertan `n + 1` claves diferentes
    (considerar que se haya redimensionado acordemente), `n` con la misma letra
    inicial, y 1 con otra distinta, en el primer caso `obtener()` es $$\mathcal{O}(n)$$ y en el
    segundo siempre $$\mathcal{O}(1)$$.

1.  (★★★) El Ing. Musumeci quiere implementar un hash abierto, pero en el que las listas de cada posición
    se encuentren ordenadas por clave (usando `strcmp`). Explicar cómo mejora o empeora respecto
    a la versión que vemos en clase para el caso de inserciones, borrados, búsquedas con éxito
    (el elemento se encuentra en el hash) y sin éxito (no se encuentra).

1.  (★★★) Hacer un seguimiento e indicar cómo queda un hash que aplica hashing perfecto (con Hash & Displace)
    con las siguientes claves (los valores de las funciones de hashing se encuentran a continuación de las claves).

    ```
    "casa": 1; 3; 2
    "perro": 3; 3; 3
    "cobayo": 6; 2; 6
    "conejo": 3; 2; 1
    "hamster": 2; 0; 1
    "gato": 3; 0; 5
    "hurón": 2; 3; 5
    "pejelagarto": 6; 0; 7
    ```

1.  (★★) Del ejercicio anterior, explicar qué sucedería si los resultados de aplicar las funciones de hashing sobre
    _"pejelagarto"_ fueran (6, 0, 3), y cómo debería resolverse.

1.  (★★★) a. Realizar las siguientes operaciones sobre un hash con Hopscotch hashing, de largo 9 y $$K = 2$$
    (los números son también el resultado de la función de hashing):
    Guardar 1, Guardar 0, Guardar 9, Borrar 1, Buscar 9, Guardar 5, Guardar 7, Guardar 17, Borrar 7, Guardar 16, Guardar 82
    Guardar 81, Guardar 2.

    b. Indicar qué sucede si guardamos el valor 89, y cómo se debe resolver.

1.  (★★★) a. Realizar el seguimiento de guardar las siguientes claves dentro de un hash con Cuckoo Hashing, con 2
    funciones de hashing (los valores de aplicar las funciones de hashing se indican a continuación de las claves),
    y tamaño 10:

    ```
    gato: 2; 3
    perro: 6; 9
    ornitorrinco: 2, 5
    oso: 8; 3
    delfín: 8; 4
    canario: 6; 3
    ```

    b. Explicar qué sucede al buscar la clave _"perro"_.

    c. Explicar cómo hacer para eliminar la clave _"perro"_ del hash, y cómo se debe modificar el hash para que
    siga funcionando correctamente.

1.  (★★★) Supongamos que queremos crear una estructura _Diccionario inmutable_. Dicho TDA es un Diccionario que
    no será modificado. No tendrá altas, ni bajas. Los elementos se los pasan al crearlo (por ejemplo,
    a través de otra implementación de diccionario, o con un par de arreglos con las claves y valores).
    Explicar cómo harías para implementar esto de forma eficiente, considerando que su mayor utilidad
    es realizar búsquedas lo más rápido posible.

1.  (★★★★) Dar una implementación en C de cómo podría ser la primitiva `hash_guardar` para el caso de un hash
    cerrado con Cuckoo Hashing con dos funciones de hashing (suponer que se llaman `h1` y `h2`). Si la clave
    ya se encontraba en el hash simplemente devolver `false` (no es necesario hacer un reemplazo del dato).
    La estructura del Hash es:
    ```cpp
    typedef struct hash {                   typedef struct campo_hash {
        campo_hash_t* tabla;                   char* clave;
        size_t cantidad;                        void* dato;
        size_t tam_tabla;                       int num_fhash;
    } hash_t;                               } campo_hash_t;
    ```

1.  (★★★★★) Se quiere implementar un TDA Diccionario con las siguientes primitivas:
    `obtener(x)` devuelve el valor de `x` en el diccionario; `insertar(x, y)` inserta en el diccionario
    la clave `x` con el valor `y` (entero); `borrar(x)` borra la entrada de `x`; `add(x, n)` le
    suma `n` al contenido de `x`; `add_all(m)` le suma `m` a **todos** los valores.

    Proponer una implementación donde **todas** las operaciones sean $$\mathcal{O}(1)$$. Justificar el
    orden de las operaciones.
