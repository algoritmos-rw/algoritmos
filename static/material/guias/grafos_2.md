---
title: "Grafos: Aplicaciones y Algoritmos"
layout: default
permalink: 'material/guias/grafos_2'
math: true
---

# Grafos: Aplicaciones y Algoritmos
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

El diámetro de una red es el máximo de las distancias mínimas entre todos los vértices 
de la misma. Implementar un algoritmo que permita obtener el diámetro de una red, para 
el caso de un grafo no dirigido y no pesado. Indicar el orden del algoritmo propuesto.



### Solución


## Ejercicios propuestos


1.  (★★) a.  Obtener una representación del camino mínimo desde el vértice A en el siguiente grafo 
        (representado con una matriz de adyacencias), hacia todos los demás vértices, 
        utilizando el algoritmo de Dijkstra:
        
        |   | A | B | C | D | E | F |
        |---|---|---|---|---|---|---|
        | A | 0 | 7 | 5 | 0 | 3 | 8 |
        | B | 7 | 0 | 0 | 0 | 1 | 3 |
        | C | 5 | 0 | 0 | 5 | 3 | 2 |
        | D | 0 | 0 | 5 | 0 | 2 | 0 |
        | E | 3 | 1 | 3 | 2 | 0 | 0 |
        | F | 8 | 3 | 2 | 0 | 0 | 0 |

    b. ¿Qué condiciones debe cumplir el grafo para poder aplicar el algoritmo de Dijkstra? 
       ¿Qué característica tiene el grafo si al finalizar la ejecución del algoritmo, uno o 
       más vértices quedan a *distancia infinita*?

1.  (★★★) Ejercicio seguimiento de Bellman-Ford

1.  (★★) Obtener el Árbol de Tendido Mínimo del siguiente grafo:
    
    a. Utilizando el Algoritmo de Kruskal. 

    b. Utilizando el Algoritmo de Prim. 

    <img src="../../assets/img/material/mst.png" alt="grafo mst" width="75%"/>


1.  (★★★) Dadas las matrices de adyacencia `M1`, `M2` y `M3`, responder las siguientes preguntas 
    (recomendamos pasar los grafos a una representación visual para mayor facilidad):
    a. ¿Puede ser el grafo definido por `M2` un árbol de tendido mínimo de `M1`? Justificar.
    b. Realizar un seguimiento de aplicar el algoritmo de Kruskal para obtener un árbol de tendido 
    mínimo del grafo definido por `M3`.

    ```
    | M1 | A | B | C | D | E | F | G | 
    |----|---|---|---|---|---|---|---| 
    | A  | 0 | 3 | 4 | 0 | 0 | 0 | 0 | 
    | B  | 3 | 0 | 5 | 3 | 3 | 0 | 0 | 
    | C  | 4 | 5 | 0 | 2 | 0 | 0 | 6 | 
    | D  | 0 | 3 | 2 | 0 | 4 | 2 | 1 | 
    | E  | 0 | 3 | 0 | 4 | 0 | 6 | 0 | 
    | F  | 0 | 0 | 0 | 2 | 6 | 0 | 0 | 
    | G  | 0 | 0 | 6 | 1 | 0 | 0 | 0 | 

    | M2 | A | B | C | D | E | F | G | 
    |----|---|---|---|---|---|---|---| 
    | A  | 0 | 3 | 4 | 0 | 0 | 0 | 0 | 
    | B  | 3 | 0 | 0 | 0 | 3 | 0 | 0 | 
    | C  | 4 | 0 | 0 | 2 | 0 | 0 | 6 | 
    | D  | 0 | 0 | 2 | 0 | 0 | 2 | 0 | 
    | E  | 0 | 3 | 0 | 0 | 0 | 0 | 0 | 
    | F  | 0 | 0 | 0 | 2 | 0 | 0 | 0 | 
    | G  | 0 | 0 | 6 | 0 | 0 | 0 | 0 | 

    | M3 | A | B | C | D  | E  | F  | G  |
    |----|---|---|---|----|----|----|----|
    | A  | 0 | 6 | 0 | 4  | 0  | 0  | 0  |
    | B  | 6 | 0 | 7 | 8  | 6  | 0  | 0  |
    | C  | 0 | 7 | 0 | 0  | 4  | 0  | 0  |
    | D  | 4 | 8 | 0 | 0  | 14 | 5  | 0  |
    | E  | 0 | 6 | 4 | 14 | 0  | 7  | 8  |
    | F  | 0 | 0 | 0 | 5  | 7  | 0  | 10 |
    | G  | 0 | 0 | 0 | 0  | 8  | 10 | 0  |
    ```

1.  (★★) Analizar la complejidad del algoritmo de Prim según si el grafo está implementado con
    listas de adyacencia o matriz de adyacencia. 

1.  (★★) Responder las siguientes preguntas, **justificando** la respuesta: 

    a. Al aplicar sobre un grafo el algoritmo de Dijkstra para encontrar caminos mínimos desde un vértice $$v$$
    cualquiera, se obtiene un árbol definido por el diccionario de padres (que permite reconstruir dichos 
    caminos mínimos). Dicho árbol, ¿es siempre de tendido mínimo?
    
    b. Al obtener un árbol de tendido mínimo de un grafo, se asegura que la suma de los pesos de las aristas
    sean mínimos. 
    ¿Es posible utilizar el árbol de tendido mínimo para encontrar el camíno mínimo entre dos pares de 
    vértices cualesquiera?

    c. Si un grafo es no pesado, ¿Se puede utilizar el Algoritmo de Dijkstra para obtener los caminos mínimos
    en dicho grafo?

1.  (★★★) Seguimiento Flujo

1.  (★★★) Implementar por **backtracking** un algoritmo que, dado un grafo no dirigido y un número 
    $$n \lt \left|V \right|$$, nos permita obtener un subconjunto de $$n$$ vértices tal que ningún par de dichos 
    vértices sean adyacentes entre sí. Se puede suponer que los vértices están identificados con números de 
    0 a $$\left| \mathcal{V} \right|-1$$.

1.  (★★★★) Ejercicio con BT: Coloreo

1.  (★★★★) Ejercicio con BT: Viajante

1.  (★★★) Implementar un algoritmo que reciba un grafo, un vértice $$v$$ y otro $$w$$ y, utilizando **backtracking**,
    obtenga **todos** los caminos simples de $$v$$ a $$w$$ en el grafo. 

1.  (★★★★) Se cuenta con un grafo en el que sus aristas tiene peso 1 o 2, únicamente. Implementar un algoritmo
    que permita obtener el camino mínimo de un vértice hacia todos los demás, en tiempo $$\mathcal{O}(V + E)$$.

1.  (★★★★★) Implementar un algoritmo que, dado un grafo dirigido, un vértice $$s$$ y otro $$t$$ determine la cantidad 
    mínima de aristas que deberían cambiar de sentido en el grafo para que exista un camino de $$s$$ a $$t$$. 

1.  (★★★★★) Supongamos que tenemos un sistema de una facultad en el que cada alumno puede pedir hasta 10 libros de 
    la biblioteca. 
    La biblioteca tiene 3 copias de cada libro. Cada alumno desea pedir libros diferentes. Implementar un algoritmo que 
    nos permita obtener la forma de asignar libros a alumnos de tal forma que la cantidad de préstamos sea máxima. 

