---
title: Diccionarios, Hashing y Hash
layout: default
permalink: 'material/guias/hash'
math: true
---

# Diccionarios, Hashing y Hash
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto


a) Para un hash cerrado, implementar una primitiva `lista_t* hash_claves(const hash_t*)`, que reciba
un hash y devuelva una lista con sus claves.

b) Repetir lo mismo para un hash abierto.

c) Repetir, en este caso como una función.

### Solución

Partiendo del punto a, es importante notar que no podemos utilizar el iterador externo, ya que se trata de una primitiva para
el hash (y es una mala práctica que, dado que el iterador dependa del hash, ahora hagamos que el hash dependa del iterador). 

#### Hash Cerrado

Para este punto, sólo es necesario iterar campo por campo, considerando únicamente aquellos que están ocupados.

```cpp
lista_t* hash_claves(const hash_t* hash) {
    lista_t* claves = lista_crear();
    if (claves) {
        return NULL;
    }
    for (size_t i = 0; i < hash->tam; i++) {
        if (hash->tabla[i].estado == OCUPADO) { // valor de un enum definido para el hash
            lista_insertar_ultimo(claves, hash->tabla[i].clave);
        }
    }
    return claves;
}
```

Es importante notar que en este ejercicio se está evaluando que sabemos trabajar internamente con el hash cerrado. Los puntos importantes: 
- Sabemos cuáles son los campos de la estructura. 
- Sabemos que la tabla es de tipo `campo_t*`, y no `campo_t**`, puesto que es completamente innecesario un segundo grado de indirección (como se analiza en la respectiva clase práctica). 
- Entendemos que el estado correcto a considerar es el de OCUPADO, que es un enumerativo. Cuanto mucho, una constante. Definitivamente no un `"ocupado"`.


#### Hash Abierto

Para este caso, consideramos todas las listas, las cuales podemos ir iterando. Podemos iterar cada lista utilizando el iterador externo o interno. Aquí mostramos una implementación utilizando el iterador interno, no porque sea mejor implementación, sino para que tengan un ejemplo de uso. 

```cpp
lista_t* hash_claves(const hash_t* hash) {
   lista_t* claves = lista_crear();
    if (claves) {
        return NULL;
    }
    for (size_t i = 0; i < hash->tam; i++) {
        lista_iterar(hash->tabla[i], agregar_clave_lista, claves);
    }
    return claves;
}

bool agregar_clave_lista(void* dato, void* extra) {
    lista_t* claves = extra;
    par_clave_valor_t* par = dato;
    lista_insertar_ultimo(claves, par->clave);
    return true;
}
```

#### Función

En este caso, no sólo podemos utilizar el iterador externo del hash, sino que **no nos queda otra opción**, dado que no es posible acceder a los campos internos de las estructuras. Además, en particular no nos dicen cuál es la implementación, cosa que no debe ser necesario conocer.

Entonces, simplemente iteramos utilizando el iterador externo y guardamos en una lista. 

```cpp
lista_t* hash_claves(const hash_t* hash) {
   lista_t* claves = lista_crear();
    if (claves) {
        return NULL;
    }
    hash_iter_t* iter = hash_iter_crear(iter);
    if (!iter) {
        lista_destruir(claves);
        return NULL;
    }
    for (; ! hash_iter_al_final(iter); hash_iter_avanzar(iter)) {
        lista_insertar_ultimo(claves, hash_iter_ver_actual(iter));
    }
    hash_iter_destruir(iter);
    return claves;
}
```

## Ejercicios propuestos

1.  a. Mostrar el resultado de las siguientes operaciones tanto para un hash cerrado como para un hash abierto, 
    ambos de largo 9 (los números son también el resultado de la función de hashing): insertar 17, insertar 22, 
    insertar 35, borrar 17, insertar 52, insertar 54. 

    b. ¿Qué pasos hay que seguir para verificar si el 70 pertenece al hash? 

    c. Posteriormente se realizan más inserciones. ¿Cuándo redimensionaría cada hash? 
    ¿Qué pasos hay que seguir para hacerlo?

1.  Implementar una función de orden $$\mathcal{O}(n)$$ que dado un arreglo de n números enteros devuelva `true` 
    o `false` según si existe algún elemento que aparezca más de la mitad de las veces. Justificar el orden de 
    la solución. Ejemplos: 

        [1, 2, 1, 2, 3] -> false
        [1, 1, 2, 3] -> false 
        [1, 2, 3, 1, 1, 1] -> true
        [1] -> true

1.  Implementar el TDA MultiConjunto. Este es un Conjunto que permite más de una aparición de un elemento, 
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

1.  Una panadería de Avellaneda le pide a alumnos de Algoritmos y Programación II que le solucionen un problema: 
    sus dos distribuidoras de pan le enviaron un hash cada una, dónde sus claves son los nombres de los productos, 
    y sus valores asociados, sus precios. La panadería le pide a los alumnos que le implementen una función que 
    le devuelva un nuevo hash con la unión de todos esos productos, y en caso de que un mismo pan se encuentre en 
    ambos hashes, elegir el que tenga el precio más barato. Indicar y justificar el orden del algoritmo.

1.  Se tiene un hash que cuenta con una función de hashing, que recibida una clave 
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

1.  El Ing. Musumeci quiere implementar un hash abierto, pero en el que cuyas listas 
    se encuentren ordenadas por clave (usando `strcmp`). Explicar cómo mejora o empeora respecto 
    a la versión que vemos en clase para el caso de inserciones, borrados, búsquedas con éxito 
    (el elemento se encuentra en el hash) y sin éxito (no se encuentra).


1.  **Ejercicio difícil**: Se quiere implementar un TDA Diccionario con las siguientes primitivas: 
    `obtener(x)` devuelve el valor de `x` en el diccionario; `insertar(x, y)` inserta en el diccionario 
    la clave `x` con el valor `y` (entero); `borrar(x)` borra la entrada de `x`; `add(x, y)` le 
    suma `y` al contenido de `x`; `add_all(y)` le suma `y` a **todos** los valores. 

    Proponer una implementación donde **todas** las operaciones sean $$\mathcal{O}(1)$$. Justificar el 
    orden de las operaciones.



