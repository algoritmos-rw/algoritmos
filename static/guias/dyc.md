---
title: División y Conquista
layout: default
permalink: '/guias/dyc'
math: true
---

# División y Conquista
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Implementar un algoritmo en C que reciba un arreglo de `n` enteros sin repetir y ordenado ascendentemente, y determine en _O(log n)_ si es mágico. Un arreglo es mágico si existe algún valor `i` (entre `0` y `n − 1`) tal que `arr[i] = i`.
Ejemplos:
* `A = [ -3, 0, 1, 3, 7, 9 ]` es mágico porque `A[3] = 3`.
* `B = [ 1, 2, 4, 6, 7, 9 ]` no es mágico porque `B[i] != i` para todo `i`.
Justificar el orden del algoritmo.

### Solución

Como mencionamos en clase, al ver que se nos pide: 
- Un algoritmo de división y conquista,
- Un orden _O(log n)_

Lo primero que tenemos que pensar es en el algoritmo _estrella_ de división y conquista, que tiene ese orden: Búsqueda Binaria. Al ver que se nos pide eso, seguramente nuestro algoritmo no sea muy distinto al de búsqueda binaria (o bien, que la forma de la función va a ser similar). Pero para poder aplicar un algoritmo así, necesariamente tenemos que poder desechar toda una proporción del problema original. Ya vemos que tenemos la condición de que el arreglo se encuentra ordenado ascendentemente, y no cuenta con repetidos. Veremos si esa última restricción es realmente necesaria, pero al menos con la primera ya contamos con una restricción bastante fuerte. 

Lo primero a pensar es el caso base: si se nos da vuelta el inicio y fin, significa que nunca nos topamos con un índice que cumpla la condición (no siempre va a ser éste nuestro caso base, ojo). 

Ahora, lo crucial: pensar la condición de éxito. Acá es donde analizamos qué resuelve nuestro algoritmo. Vamos al medio, y lo que tenemos que verificar es si `arr[medio] = medio`. Si eso sucede, ¡éxito!

Ahora, pensemos que eso no sucede. Necesitamos quedarnos con una sola de las mitades, lo cual implica descartar la otra. Pero, ¿cómo descartamos una mitad? Bueno, podemos ver qué pasó con `arr[medio]` que no cumple con la condición de éxito. ¿Qué sucede si `arr[medio] < medio`? ¿Puede suceder que algún elemento anterior sí cumpla la condición? **¡NO!** porque al no poder haber repetidos, si `arr[medio] < medio`, entonces `arr[medio - 1] < medio - 1`, y tambien para todos los anteriores. Por eso, podemos simplemente ver de la mitad en adelante, descartando la primera mitad. Ahí vemos que la condición extra era necesaria, sino no podríamos descartar la primera mitad. Podemos hacer el mismo análisis al revés, vamos a ver que si `arr[medio] >  medio`, no puede ser que se cumpla la condición para los elementos siguientes. 

Luego de este análisis, podemos escribir el código: 
```c
bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin) {
    if (inicio > fin) {
        return false;
    }

    size_t medio = (inicio + fin) / 2;
    if (arr[medio] == medio) {
        return true;
    }
    if (arr[medio] < medio) {
        return _arreglo_es_magico(arr, medio + 1, fin);
    } else {
        return _arreglo_es_magico(arr, inicio, medio - 1);
    }
}

bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}
```

_Nota_: El algoritmo puede, en vez de resolverse con una función auxiliar que haga la recursión, usando directamente `arreglo_es_magico`, usando álgebra de punteros. Quien quiera hacerlo así, es bienvenido, aunque nos parece más clara para la explicación (y más directa) la propuesta. 

#### Demostración del orden 

Vemos la ecuación de recurrencia: 

    T(n) = T(n / 2) + O(1)

Es, evidentemente, igual a la de Búsqueda Binaria, por lo que tendrá el mismo orden, pero aplicamos el Teorema Maestro para corroborar: 

    A = 1
    B = 2
    C = 0

    log_B (A) = log_2 (1) = 0 = C

Por ende, el orden del algoritmo debe ser _O(n^C log n)_ = _O(log n)_

## Ejercicios propuestos

1. Implementar, por división y conquista, una función que determine si un elemento se encuentra en un _arreglo desordenado_. Indicar el orden del algoritmo, justificando con el Teorema Maestro.

1. Se tiene un arreglo tal que `[1, 1, 1, ..., 0, 0, ...]` (es decir, _unos seguidos de ceros_). Se pide:

    a. una función de orden _O(log n)_ que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.

    b. demostrar con el Teorema del Maestro que la función es, en efecto, _O(log n)_.

    Ejemplos:

        [1, 1, 0, 0, 0] →  2
        [0, 0, 0, 0, 0] →  0
        [1, 1, 1, 1, 1] → -1

1. Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de la raíz cuadrada de un número _n_, en tiempo _O(log n)_.

## Bibliografía y referencias

- Weiss, Mark Allen: "Data Structures and Algorithms" (tercera edición), Pearson, 1999. Cap. 10.2: _Divide and Conquer_.
- Cormen, Thomas; Leiserson, Charles; Rivest, Ronald; Stein, Clifford: "Introduction to Algorithms" (tercera edición), MIT Press, 2009. Cap. 4: _Divide-and-Conquer_.

