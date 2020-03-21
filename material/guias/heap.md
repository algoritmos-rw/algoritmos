---
math: true
---

# Colas de Prioridad y Heaps
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto


Implementar en C una primitiva para el heap (siendo este un max-heap) que reciba un heap y una función de
comparación y lo reordene de manera tal que se se comporte como max-heap para la nueva función de comparación
(se cambia la función de prioridad). El orden de dicha primitiva debe ser $$\mathcal{O}(n)$$.


### Solución

La única dificultad de este ejercicio radica en entender verdaderamente qué es lo que se nos pide: darle a un arreglo
ya existente (el interno del heap) forma de heap, dada por una función de comparación (la nueva función de comparación
del heap). Entonces, esto no es más que invocar a `heapify`, y ya. Eso es todo. También, es la única forma de darle ese
orden a la primitiva.

```cpp
void heap_cambiar_prioridad(heap_t* heap, heap_cmp_t nueva_cmp) {
    heap->cmp = nueva_cmp;
    heapify(heap->datos, heap->cantidad, nueva_cmp);
}
```

Obviamente, la primitiva es $$\mathcal{O}(n)$$ dado que `heapify` (bien implementado) tiene dicha complejidad.
Por supuesto, este ejercicio involucra más pensar bien cuáles son las operaciones que se pueden hacer con el heap
(y, especialmente, cuál es la única con el orden pedido).


## Ejercicios propuestos


1.  (★) Implementar en lenguaje C una función _recursiva_ con la firma
    `bool es_heap(int arr[], size_t n)`. Esta función debe devolver true o false de acuerdo
    a si el arreglo que recibe como parámetro cumple la propiedad de heap (de mínimos).

    Hacer el seguimiento de la función para el arreglo `[ 1, 7, 2, 8, 7, 6, 3, 3, 9, 10 ]`.

1.	(★) Implementar una primitiva para el heap (de máximos) que obtenga los 3 elementos más grandes del heap en
    $$\mathcal{O}(1)$$.

1.  (★★) Si en el ejercicio anterior vez de quererse los 3 elementos más grandes se quisieran los _K_ elementos
    más grandes ¿cómo se debería proceder? ¿Cuál terminaría siendo la complejidad del algoritmo?

1.	(★★) En un heap de máximos ¿cuáles son las posibles posiciones del arreglo
    donde podría encontrarse el mínimo?

1.  (★★) Realizar el seguimiento del algoritmo _heapsort_ para ordenar el siguiente
    arreglo: `[ 4, 7, 8, 14, 10, 9, 16, 2, 3, 1 ]`.

1.  (★★★) ¿Puede utilizarse un Heap para implementar el TDA cola (en el que se extraen los elementos en el orden
    en que fueron insertados)? ¿Y para implementar el TDA pila?

1.	(★★) Hacer el seguimiento de las siguientes operaciones sobre un heap (de mínimos),
    mostrando el estado de la estructura después de cada modificación:

    {:.lower_alpha}
    1. Crear un heap de mínimos desde el arreglo `[8, 2, 1, 5, 10, 6, 14, 4]`.

    1. Sobre el heap resultante del punto anterior, realizar las siguientes
      operaciones: `encolar(6)`, `encolar(3)`, `encolar(17)`, `desencolar()`, `encolar(7)`,
      `desencolar()`.

1.  (★★★) Escribir una función en C que, dado un arreglo de $$n$$ cadenas y un entero
    positivo $$k$$, devuelva una lista con las $$k$$ cadenas más largas. Se espera que el
    orden del algoritmo sea $$\mathcal{O}(n \log k)$$. Justificar el orden.

1.  (★★★) Para implementar un TDA Cola de prioridad, nos proponen la siguiente solución: usar un arreglo
    desordenado (`arr`) para insertar los datos, y una variable (`maximo`) para poder obtener el
    máximo en $$\mathcal{O}(1)$$. Se mantiene actualizada la variable `maximo` cada vez que se encola o
    desencola. ¿Es una buena solución en el caso general? Justificar (recomendación: comparar
    contra la implementación de colas de prioridad vista en clase).

1.  (★★★★) Se tienen $$k$$ arreglos de enteros previamente ordenados y se quiere obtener
    un arreglo ordenado que contenga a todos los elementos de los $$k$$ arreglos. Sabiendo que cada arreglo
    tiene tamaño $$h$$, definimos como $$n$$ a la sumatoria de la cantidad de elementos de todos los arreglos,
    es decir, $$n = k \times h$$.

    Escribir en C una función `int* k_merge(int** arr, size_t k, size_t h)` que reciba los $$k$$ arreglos y
    devuelva uno nuevo con los $$n$$ elementos ordenados entre sí. La función debe ser de orden
    $$\mathcal{O}(n \log k)$$. Justificar el orden del algoritmo propuesto.

1.	(★★★★★) Diseñar el TDA Mediana. Dicho TDA debe poder recibir un flujo de números y, en cualquier momento,
    debe poder consultársele cuál es la mediana de **todos** los elementos vistos hasta ese momento. La primitiva para agregar un nuevo
    número debe poder hacerse en $$\mathcal{O}(\log n)$$ mientras que la operación de consultar la mediana debe
    ser $$\mathcal{O}(1)$$. Recordar que la mediana de una secuencia de números es el elemento que se encontraría
    a la mitad si la secuencia se encontrara ordenada (en caso de ser una cantidad par, se puede definir como
    el promedio entre ambos valores adyacentes del medio, o como uno de los dos de ellos de forma arbitraria).
