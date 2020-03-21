---
title: Centralidad en un Grafo
math: true
---

# Centrality

[Centrality](https://en.wikipedia.org/wiki/Betweenness_centrality) (o Centralidad, en español),
es una medida dentro te Teoría de Grafos que determina cuán importante es un vértice dentro de una red
en particular. Esto puede ayudar a entender desde cuan importante es una persona dentro de una red social,
importancia de una avenida dentro de una ciudad, etc...

Hay distintos tipos de centralidades:
1. Centralidad de grado: simplemente, el grado del vértice en cuestión (en caso de grafos dirigidos,
serían ambas medidas).
2. Cercanía (_closeness_): el promedio de las distancias del vértice a todos los demás.
3. Intermediación (_Betweeness_): es la frecuencia con la que aparece el vértice en todos los caminos
mínimos del grafo (en los que no es extremo).
4. Centralidad del autovector: analiza el vértice en función de los autovalores y autovectores de la
matriz de adyacencia.

En el curso, nos centraremos especialmente en la tercera.

## Betweeness Centrality

Para obtener la centralidad de los vértices de un grafo, será necesario saber cuántas veces aparece un
vértice en cada camino mínimo posible dentro del grafo. Para ésto, será necesario calcular los caminos
mínimos entre todos los pares de vértices (sin ser uno de los extremos). Esto nos dirá cuan seguido
se pasa por el vértice en cuestión para llegar a los demás. Para explicar la lógica de ésto: si
en una red de citaciones de Papers, para llegar de un paper a otro es necesario pasar usualmente
por uno en particular, entonces es seguro que ese paper debe ser importante.

### Implementación Sencilla

Un algoritmo trivial para tratar de calcular la centralidad podría ser:

1. Para cada vértice origen, para cada vértice destino, calculamos el camino mínimo entre estos dos,
vemos quienes aparecen en el medio del camino. El cálculo del camino mínimo se podrá hacer usando el
Algoritmo de Dijkstra, BFS (si el grafo es no pesado), según corresponda.

Este algoritmo es bastante sencillo de implementar:
```python
def centralidad(grafo):
    cent = {}
    for v in grafo: cent[v] = 0
    for v in grafo:
        for w in grafo:
            if v == w: continue
            # con el algoritmo que corresponda al grafo
            distancia, padre = camino_minimo(grafo, v, w)
            # salteamos si no hay camino de v a w
            if padre[w] is NULL: continue
            actual = padre[w]
            # le sumamos 1 a la centralidad de todos los vertices que se encuentren en
            # el medio del camino
            while actual != v:
                cent[actual] += 1
                actual = padre[actual]
    return cent
```

#### Complejidad

El algoritmo es muy sencillo de entender, y de implementar. Ahora bien, ¿cuál es el orden? Para todos los
vértices origen posibles, para todos los vertices destinos posible, obtenemos el camino mínimo. Si usamos
Dijkstra, el algoritmo tendrá un orden de $$\mathcal{O}(V^2 E \log V)$$, con BFS es
$$\mathcal{O}(V^2(V+E))$$. Ésto es claramente un orden muy grande.

### Una mejor implementación

Otra opción puede ser aprovechar que tanto el recorrido BFS como el Algoritmo de Dijkstra permite calcular
**todos** los caminos mínimos desde un determinado origen, con la misma complejidad. Esto nos permitirá
reducir en un grado el orden del punto anterior. Lo que sucederá es que el algoritmo será levemente más
complejo que el anterior, dado que será más complejo _reconstruir los caminos_: el truco estará en que
no buscamos reconstruir los caminos, sino simplemente saber cuántas veces aparece un vértice en un camino
mínimo:
1. Aplicar Dijsktra/BFS, sin un destino fijo (el algoritmo que corresponda para el grafo en cuestión).
1. Tener un arreglo/diccionario con contadores, para cada vértice, inicializados en 0. Estos contadores
nos permitirán saber cuántas veces aparece cada vértice, para este origen.
1. Ordenar los vértices de mayor a menor distancia (sacando de lado los que queden en infinito).
1. En el orden obtenido en el punto anterior, iterar los vértices: por cada uno, le sumamos a su
padre (solo a su padre directo) 1, más el contador del vértice actual. Eso hace que le estemos sumando 1
por su propio camino (cuando calculamos para desde el origen a dicho vértice), y todos los caminos que
pasan por este vértice en cuestión, que necesariamente también van a tener que pasar por el padre.
Estamos seguros de siempre pasar primero por un hijo antes del padre, por haber realizado el
ordenamiento de mayor a menor distancia.

```python
def centralidad(grafo):
    cent = {}
    for v in grafo: cent[v] = 0
    for v in grafo:
        # hacia todos los demas vertices
        distancia, padre = camino_minimo(grafo, v)
        cent_aux = {}
        for w in grafo: cent_aux[w] = 0
        # Aca filtramos (de ser necesario) los vertices a distancia infinita,
        # y ordenamos de mayor a menor
        vertices_ordenados = ordenar_vertices(grafo, distancias)
        for w in vertices_ordenados:
            cent_aux[padre[w]] += 1 + cent_aux[w]
        # le sumamos 1 a la centralidad de todos los vertices que se encuentren en
        # el medio del camino
        for w in grafo:
            if w == v: continue
            cent[w] += cent_aux[w]
    return cent
```
#### Complejidad

De los puntos anteriores podemos ver que el orden de nuestra nueva implementación será:

$$
\begin{aligned}
\mathcal{O}(\text{centralidad}) &= V \times \left(\mathcal{O}(\text{camino-minimo}) + \mathcal{O}(V)
+ \mathcal{O}(\text{ordenamiento}) + \mathcal{O}(V) + \mathcal{O}(V)\right) \\

\mathcal{O}(\text{centralidad}) &= V \times \left(\mathcal{O}(\text{camino-minimo}) +
 \mathcal{O}(\text{ordenamiento})\right)
\end{aligned}
$$

* Si se trata de un grafo no pesado el camino mínimo nos costará $$\mathcal{O}(V+E)$$. En este caso,
sabemos cuál es el rango de distancias posibles: irán de 0, a como mucho $$V$$, por lo que podríamos
utilizar un ordenamiento no comparativo como Counting Sort. De esta forma, el costo del ordenamiento
será $$\mathcal{O}(V)$$, teniendo un orden final de $$\mathcal{O}(V(V+E))$$.

* Si se trata de un grafo pesado, obtener los caminos mínimos nos costará $$\mathcal{O(E\log V)}$$. En
este caso no tenemos forma de acotar las distancias (aún cuando las conociéramos todas, sumadas pueden
dar mucho mayor a la cantidad de vértices que hay, haciendo que aplicar counting sort sea
contraproducente). Por lo tanto, deberemos usar un ordenamiento comparativo, costando
$$\mathcal{O}(V \log V)$$, teniendo un orden final de $$\mathcal{O}(V (V+E) \log V)$$.


### Usando el algoritmo de Floyd-Warshall

Opcionalmente, también se puede implementar el algoritmo de
[Floyd-Warshall](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm) que, utilizando
programación dinámica, permite obtener todos los caminos mínimos de un grafo, en tiempo
$$\mathcal{O}(V^3)$$.

## Centralidad Aproximada

Dado que el orden de las implementaciones anteriores aún sigue siendo muy grande, otra opción puede ser
calcular la centralidad utilizando [Random Walks](random_walks.md). Realizando muchos caminos largos, de
forma aleatoria, comenzando desde cualquier vértice, suena razonable pensar que los vértices que más
veces aparezcan entre todos los recorridos, deberían ser los más importantes. Por supuesto, esto es una
aproximación. Para explicar la lógica de ésto podemos utilizar el mismo ejemplo al anterior: si en una
red de papers nos movemos de citación en citación de forma aleatoria, muy probablemente los papers con los
que más veces nos topemos sean los más importantes. Nuevamente, deberíamos tener en cuenta los pesos para
movernos de un vértice a otro (si es que los hay).

Si tenemos $$K$$ recorridos a realizar de longitud $$L$$, el costo será $$\mathcal{O}(K \times L)$$. En el
peor de los casos, veremos varias veces algunas aristas, pero no veremos todas todo el tiempo. Podríamos
acotar esto por $$\mathcal{O}(V + E)$$.

