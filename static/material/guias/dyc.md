---
title: División y Conquista
permalink: 'material/guias/dyc'
math: true
---

# División y Conquista
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Implementar un algoritmo en C que reciba un arreglo de $$n$$ enteros sin repetir y ordenado ascendentemente, y determine en $$\mathcal{O}(\log n)$$ si es mágico. Un arreglo es mágico si existe algún valor `i` (entre `0` y `n − 1`) tal que `arr[i] = i`. Justificar el orden del algoritmo.

Ejemplos:
* `A = [ -3, 0, 1, 3, 7, 9 ]` es mágico porque `A[3] = 3`.
* `B = [ 1, 2, 4, 6, 7, 9 ]` no es mágico porque `B[i] != i` para todo `i`.

### Solución

Como mencionamos en clase, al ver que se nos pide: 
- Un algoritmo de división y conquista,
- Un orden $$\mathcal{O}(\log n)$$

Si no nos pidiera que sea de división y conquista, y más aún que su orden sea logarítimico, podríamos simplemente ir elemento por elemento chequeando si se cumple la condición:

```cpp
bool arreglo_es_magico(int arr[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == i) return true;
    }
    return false;
}
```

Por supuesto, esta sería la solución _trivial_, casi con nulo esfuerzo de pensar y aprovechar la cualidad de que el
arreglo se encuentre ordenado y sin repetidos. Se podría hasta implementar con división y conquista, pero no dejará
de ser $$\mathcal{O}(n)$$. Como en otros problemas, vamos a buscar aprovechar las precondiciones que nos dan para el
arreglo. 

Lo primero que tenemos que pensar es en el algoritmo _estrella_ de división y conquista, que tiene ese orden: Búsqueda Binaria. Al ver que se nos pide eso, seguramente nuestro algoritmo no sea muy distinto al de búsqueda binaria (o bien, que la forma de la función va a ser similar). Pero para poder aplicar un algoritmo así, necesariamente tenemos que poder desechar toda una proporción del problema original. Ya vemos que tenemos la condición de que el arreglo se encuentra ordenado ascendentemente, y no cuenta con repetidos. Veremos si esa última restricción es realmente necesaria, pero al menos con la primera ya contamos con una restricción bastante fuerte. 

Lo primero a pensar es el caso base: si se nos da vuelta el inicio y fin, significa que nunca nos topamos con un índice que cumpla la condición (no siempre va a ser éste nuestro caso base, ojo). 

Ahora, lo crucial: pensar la condición de éxito. Acá es donde analizamos qué resuelve nuestro algoritmo. Vamos al medio, y lo que tenemos que verificar es si `arr[medio] == medio`. Si eso sucede, ¡éxito! Entonces, por ahora tenemos: 

```cpp
bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}

bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin) {
    if (inicio > fin) {
        return false;
    }

    size_t medio = (inicio + fin) / 2;
    if (arr[medio] == medio) {
        return true;
    }
    // nos falta el caso sin exito
}
```

Ahora, pensemos que eso no sucede. Necesitamos quedarnos con una sola de las mitades, lo cual implica descartar la otra. Pero, ¿cómo descartamos una mitad? Bueno, podemos ver qué pasó con `arr[medio]` que no cumple con la condición de éxito. ¿Qué sucede si `arr[medio] < medio`? ¿Puede suceder que algún elemento anterior sí cumpla la condición? **¡NO!** porque al no poder haber repetidos, si `arr[medio] < medio`, entonces `arr[medio - 1] < medio - 1`, y tambien para todos los anteriores. Por eso, podemos simplemente ver de la mitad en adelante, descartando la primera mitad. Ahí vemos que la condición extra era necesaria, sino no podríamos descartar la primera mitad. Podemos hacer el mismo análisis al revés, vamos a ver que si `arr[medio] >  medio`, no puede ser que se cumpla la condición para los elementos siguientes. 

Luego de este análisis, podemos escribir el código: 

```cpp
bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}

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
```

_Nota_: El algoritmo puede, en vez de resolverse con una función auxiliar que haga la recursión, usando directamente `arreglo_es_magico`, usando álgebra de punteros. Quien quiera hacerlo así, es bienvenido, aunque nos parece más clara para la explicación (y más directa) la propuesta. 

#### Demostración del orden 

Vemos la ecuación de recurrencia: 

$$
\mathcal{T}(n) = \mathcal{T}\left(\frac{n}{2}\right) + \mathcal{O}(1)
$$

Es, evidentemente, igual a la de Búsqueda Binaria, por lo que tendrá el mismo orden, pero aplicamos el Teorema Maestro para corroborar: 

$$
A = 1; B = 2; C = 0 \rightarrow \log_B (A) = \log_2 (1) = 0 = C
$$

Caemos en el caso de $$\log_B (A) = C$$, por lo que el orden del algoritmo será $$\mathcal{O}(n^C \log n) = \mathcal{O}(\log n)$$

## Ejercicios propuestos

1. Implementar, por división y conquista, una función que determine si un elemento se encuentra en un _arreglo desordenado_. Indicar el orden del algoritmo, justificando con el Teorema Maestro.

1. Implementar, por división y conquista, una función que dado un arreglo y su largo, determine si el mismo se encuentra ordenado. 

1. Se tiene un arreglo tal que `[1, 1, 1, ..., 0, 0, ...]` (es decir, _unos seguidos de ceros_). Se pide:

    a. una función de orden $$\mathcal{O}(\log n)$$ que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.

    b. demostrar con el Teorema del Maestro que la función es, en efecto, $$\mathcal{O}(\log n)$$.

    Ejemplos:

        [1, 1, 0, 0, 0] →  2
        [0, 0, 0, 0, 0] →  0
        [1, 1, 1, 1, 1] → -1

1. Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de la raíz cuadrada de un número $$n$$, en tiempo $$\mathcal{O}(\log n)$$. Por ejemplo, para $$n = 10$$ debe devolver 3, y para $$n = 25$$ debe devolver 5. 

1. Se tiene un arreglo de $$N >= 3$$ elementos en forma de pico, esto es: estrictamente creciente hasta una determinada posición $$p$$, y estrictamente decreciente a partir de ella (con $$0 \gt p \lt N-1$$). Por ejemplo, en el arreglo 
`[1, 2, 3, 1, 0, -2]` la posición del pico es $$p = 2$$. Se pide:

    a. Implementar un algoritmo de división y conquista de orden $$\mathcal{O}(\log n)$$ que encuentre la posición 
    $$p$$ del pico: `size_t posicion_pico(int v[], size_t ini, size_t fin);`. La función será invocará inicialmente como: 
    `posicion_pico(v, 0, n-1)`, y tiene como pre-condición que el arreglo tenga forma de pico.
    
    b. Justificar el orden del algoritmo mediante el teorema del maestro.

1.  Se quiere implementar MergeSort pero, en vez de dividir en dos partes el arreglo, dividirlo en tres, llamando 
    recursivamente al algoritmo para cada una de las partes y luego uniéndolas. 

    a. Suponiendo que el merge de las tres partes se realiza en tiempo lineal, calcular el orden del algoritmo. 

    b. Si en vez de dividir en tres partes, se dividiera el arreglo en $$n$$, siendo $$n$$ la cantidad de elementos del arreglo, ¿a qué otro algoritmo de ordenamiento se asemeja esta implementación? ¿Cuál es el orden de dicho algoritmo? 

    c. Dado lo obtenido en los puntos anteriores, ¿tiene sentido implementar MergeSort con $$k$$ separaciones, para $$k > 2$$?

1.  Un algoritmo sencillo para multiplicar matrices de $$n \times n$$ demora $$\mathcal{O}(n^3)$$. 
    El algoritmo de Strassen (que utiliza División y Conquista) lo hace en $$\mathcal{O}(n^{\log_2 7})$$. 
    La profesora Manterola quiere implementar un algoritmo de División y Conquista que sea aún más veloz, 
    donde divida al problema en `A` subproblemas de tamaño de $$\frac{n}{4}$$, y que juntar las soluciones 
    parciales sea $$\mathcal{O}(n^2)$$. 
    ¿Cuál es el máximo `A` para que el orden del algoritmo sea menor que el del algoritmo de Strassen? 
    Justificar.

1.  **Ejercicio difícil**: Implementar una función (que utilice división y conquista) de orden $$\mathcal{O}(n \log n)$$ 
    que dado un arreglo de $$n$$ números enteros devuelva `true` o `false` según si existe algún elemento que aparezca 
    más de la mitad de las veces. Justificar el orden de la solución. Ejemplos: 

        [1, 2, 1, 2, 3] -> false
        [1, 1, 2, 3] -> false 
        [1, 2, 3, 1, 1, 1] -> true
        [1] -> true

    _Aclaración_: Para hacer interesante el ejercicio, resolver sin ordenar el arreglo, sino puramente división y 
    conquista. 



