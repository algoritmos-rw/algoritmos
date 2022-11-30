---
title: Camino de Euler
math: true
---

# Camino y Ciclo Euleriano

Un [Camino de Euler](https://en.wikipedia.org/wiki/Eulerian_path) es un camino en un grafo que recorre todas las aristas de este, exactamente una vez. No neceariamente todo grafo admite un camino euleriano.

En particular, además se puede definir un ciclo Euleriano a un camino Euleriano que comienza y termina en el mismo vértice. Hierholzer demostró más adelante que un grafo tiene ciclo Euleriano si y sólo si es conexo y todos los vértices son de grado par. Además, también se demostró que un grafo no dirigido tiene camino de Euler si y sólo si la cantidad de vértices con grado impar es a lo sumo 2. 
Curioso es, que el problema que originó todo esto (Los 7 puentes de Köningberg) tiene 4 vértices de grado impar, por lo que no tiene un camino Euleriano. 

## Resolución

Lo primero a hacer es determinar si el grafo tiene o no un ciclo o camino Euleriano. Esto es simplemente chequeando si es conexo (en caso de necesitar validarlo) y si tiene 0 o 2 vértices de grado impar (por teorema, en un grafo no dirigido, la cantidad de vértices de grado impar, es par). Si tiene más, no tiene ninguna de estas dos opciones. 

Si tiene 0, presenta un ciclo Euleriano. Si tiene 2, presenta un camino Euleriano. 

Diferenciamos entre estos dos casos porque el algoritmo para determinar un ciclo Euleriano se realiza en tiempo lineal, mientras que en el otro caso es cuadrático. 

### Algoritmo de Hierholzer

Para detectar un ciclo Euleriano (tenemos todos vértices de grado par), aplicamos lo siguiente:

1. Elegimos cualquier vértice _v_ (o uno en particular, si la aplicación así lo requiere). 
2. Aplicamos un recorrido DFS desde _v_, considerando las aristas que estamos utilizando. Cuando nos volvemos a topar con _v_ (y es imposible que no suceda), nos quedamos con ese camino cerrado. Llamemos a este camino _C_.
3. Si existe algún vértice _u_ dentro del camino _C_ que tenga aristas que no se utilizaron aún, realizar el mismo recorrido mencionado antes desde _u_ (sin considerar las aristas ya utilizadas), y al terminar "agregar" el circuito hecho desde y hasta _u_ en nuestro camino _C_ obtenido antes, en el lugar donde estaba _u_. Volver a realizar esto hasta que ya no queden aristas sin revisar. 

Este algoritmo se asegura pasar por cada arista una sola vez, por lo que es $$\mathcal{O}(V + E)$$. 

### Algoritmo de Fleury

Este algoritmo también permite obtener ciclos de Euler, pero no conviene utilizarlo ya que es cuadrático, y en ese caso podemos utilizar el anterior. En caso que tengamos 2 vértices de grado impar, utilizamos este. El algoritmo es más bien simple:

1. Elegimos uno de los vértices de grado impar. 
2. Realizamos un recorrido DFS. Si el vértice en el que me encuentro tiene una única arista, la utilizo. Sino, si hay alguna arista que sea puente, evito utilizarla (salvo que sea la única). No vuelvo a pasar por aristas ya visitadas. 
3. Al terminarse las aristas, tenemos nuestro recorrido. 

Una arista es puente, si en caso de no existir el grafo deja de ser conexo. El algoritmo se basa en no utilizar los puentes hasta que sea necesario. 

El problema de este algoritmo radica en que para cada punto del recorrido tengo que determinar si una arista no utilizada es puente (si considero a las ya utilizadas como eliminadas). Esto se realiza eliminando la arista en cuestión y haciendo un simple recorrido para ver si el grafo sigue siendo conexo. Si es conexo, la arista no es puente, y podemos utilizar esta arista. Pero aquí vamos a chequear potencialmente por cada arista si la misma es puente, haciédose un recorrido por cada arista, terminando en un algoritmo cuadrático. 
Han habido mejoras en el algoritmo para que tenga complejidad $$\mathcal{O}(E \log E \log \log E)$$, pero sigue siendo peor que el algoritmo de Hierholzer, cuando este se puede utilizar.

