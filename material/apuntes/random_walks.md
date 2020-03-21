---
math: true
---

# Random Walks

Un [Random Walk](https://en.wikipedia.org/wiki/Random_walk) es, como su nombre indica, un camino aleatorio
sobre un grafo. Comienza desde un vértice (que puede ser uno específico o uno aleatorio) y se mueve
aleatoriamente a un vecino; y luego, se mueve a un vecino (incluyendo el original) desde el nuevo vértice.

Este proceso continúa hasta que el recorrido tenga un largo $$n$$ prefijado. La probabilidad para movernos
de un vértice a un vecino puede ser equiprobable (la misma para todos) o proporcional al peso que tenga
cada arista (si el grafo fuera pesado), u otra alternativa dependiendo de la aplicación. Finalmente, una
aplicación que utiliza este algoritmo puede realizar varios recorridos. Por lo tanto, para realizar un
random walk es necesario determinar:
* El largo del recorrido.
* La probabilidad para movernos desde un vértice a sus vecinos.
* La cantidad de recorridos a realizar.

Todas estas caracterizaciones dependen de la aplicación del algoritmo.

## Ejemplo de aplicación

Una aplicación usual (al menos en TPs de esta materia) es la de utilizar random walks para determinar
cuál es el (o los) vértices más _similares_ a uno en particular. ¿Cómo esto nos puede ayudar a determinar
si un vértice es similar a otro? Si realizamos muchos de estos recorridos aleatorios, partiendo desde el
vértice en cuestión, moviéndonos de forma completamente aleatoria, el/los vértices que más veces aparezcan
entre todos los recorridos, deben ser los más similares al personaje de origen. Este es un algoritmo
bastante usado, por ejemplo en Twitter, para recomendar seguidores. Tener en cuenta que cuantos más
largos y más recorridos se hagan, debería ser más preciso el algoritmo (en ambos casos, y siempre que se
utilicen Random Walks).

## Utilizando los pesos de las aristas

En caso que la aplicación implique moverse teniendo en cuenta los pesos de las aristas, tratando de moverse
preferentemente a través de las aristas de más peso, podemos elegir el vértice con un algoritmo sencillo
como el siguiente:

```python
def vertice_aleatorio(pesos):
    #Pesos es un diccionario de pesos, clave vértice vecino, valor el peso.
    total = sum(pesos.values())
    rand = random.uniform(0, total)
    acum = 0
    for vertice, peso_arista in pesos.items():
        if acum + peso_arista >= rand:
            return vertice
        acum += peso_arista
```

Dicho algoritmo trata a cada "unidad de peso" de forma equiprobable (sería como si en una rifa cada vértice
tenga tantos números como peso tiene su unión con el origen). Si se quisiera implementar ésto con otro
tipo de distribución de probabilidad, habría que utilizar otros métodos de inversión de variables
aleatorias.
