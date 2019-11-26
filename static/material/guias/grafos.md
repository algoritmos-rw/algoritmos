---
title: "Grafos: Usos, implementaciones, recorridos."
permalink: 'material/guias/grafos_1'
math: true
---

# Grafos
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Implementar un algoritmo que, dado un grafo no dirigido, nos devuelva un ciclo dentro del mismo, si es que los tiene. Indicar el orden del algoritmo. 

### Solución

Antes que nada, debemos entender que el ejercicio en sí es el mismo, se trate de un grafo dirigido o uno no dirigido. La única diferencia se encuentra en que un ciclo por definción necesita contar con al menos dos aristas. Esta definición en sí no nos importaría mucho en el caso de un grafo dirigido, pero si en el de uno no dirigido. Si no lo tuviéramos en cuenta, todo grafo no dirigido, con al menos una arista, va a tener un ciclo, lo cual no es cierto. 

Para resolver este problema, podemos pensar en simplemente recorrer el grafo no dirigido, sea con un recorrido _BFS_ o _DFS_. Una vez que nos topemos con un vértice ya visitado, ahí tenemos un posible ciclo. Esto es, si estoy viendo los adyacentes a un vértice dado, y dicho vértice está visitado, uno se apresuraría a decir que ahí se cierra un ciclo. Esto es cierto, salvo un caso: que dicho vértice visitado sea el antecesor a nuestro vértice en el recorrido (BFS o DFS). Recordar que se trata de un grafo no dirigido, por ende si _v_ tiene de adyacente a _w_, entonces también vale la recíproca, y no por ello se crea un ciclo. El problema se da con la arista de la que vengo. Básicamente, deberíamos obviar al vértice del que vengo en el recorrido, que justamente es el padre. Si nosotros ya tenemos que `padre[W] = V`, entonces simplemente tenemos que saltearnos a V cuando veamos a los adyacentes ya visitados.


Lo resolvemos con ambos recorridos. Por _BFS_:

``` python
def obtener_ciclo_bfs(grafo):
  visitados = {}
  for v in grafo:
    if v not in visitados:
      ciclo = bfs_ciclo(grafo, v, visitados)
      if ciclo is not None:
        return ciclo
  return None

def bfs_ciclo(grafo, v, visitados):
  q = Cola()
  q.encolar(v)
  visitados[v] = True
  padre = {}  # Para poder reconstruir el ciclo
  padre[v] = None

  while not q.esta_vacia():
    v = q.desencolar()
    for w in grafo.adyacentes(v):
      if w in visitados:
        # Si w fue visitado y es padre de v, entonces es la arista de donde vengo (no es ciclo).
        # Si no es su padre, esta arista (v, w) cierra un ciclo que empieza en w.
        if w != padre[v]:
          return reconstruir_ciclo(padre, w, v)
      else:
        q.encolar(w)
        visitados[v] = True
        padre[w] = v

  # Si llegamos hasta acá es porque no encontramos ningún ciclo.
  return None
```

La solución por _DFS_ sería:

``` python
def obtener_ciclo_dfs(grafo):
  visitados = {}
  padre = {}
  for v in grafo:
    if v not in visitados:
      ciclo = dfs_ciclo(grafo, v, visitados, padre)
      if ciclo is not None:
        return ciclo
  return None

def dfs_ciclo(grafo, v, visitados, padre):
  visitados[v] = True
  for w in grafo.adyacentes(v):
    if w in visitados:
      # Si w fue visitado y es padre de v, entonces es la arista de donde vengo (no es ciclo).
      # Si no es su padre, esta arista (v, w) cierra un ciclo que empieza en w.
      if w != padre[v]:
        return reconstruir_ciclo(padre, w, v)
    else:
      padre[w] = v
      ciclo = dfs_ciclo(grafo, w, visitados, padre)
      if ciclo is not None:
        return ciclo
        
  # Si llegamos hasta acá es porque no encontramos ningún ciclo.
  return None
```

Ambas técnicas usan la función para reconstruir el ciclo:

```python
def reconstruir_ciclo(padre, inicio, fin):
  v = fin
  camino = []
  while v != inicio:
    camino.append(v)
    v = padre[v]
  camino.append(inicio)
  return camino.invertir()
```

Ahora bien, para ver el orden, podemos ver que en el caso feliz, vamos a encontrar un ciclo muy rapido. Pero claramente eso no nos cambia mucho. Pensemos el caso de, a lo sumo, encontrar el ciclo muy tarde en el recorrido (también veremos el caso de no haber ciclo). En ese caso, en cualquiera de los dos recorridos vamos a pasar por cada vértice una vez, y solo una vez (a fin de cuentas, no volvemos a estar sobre un vértice ya visitado). Por cada vértice vemos _sus_ aristas. Recordar que es muy importante no caer en la tentación de decir que entonces el algoritmo es $$\mathcal{O}(V*E)$$, porque si bien es cierto, es una muy mala cota. Por cada vértice pasamos por _sus_ arisas, que distan de ser las totales del grafo. Si por cada vértice vemos sus aristas (y no las de todo el grafo), en total estamos viendo todas las aristas del grafo, dos veces (una por cada extremo). Entonces, el orden será $$\mathcal{O}(V + 2 E) = \mathcal{O}(V + E)$$.

Haciendo un poco más de análisis: ¿es acaso el caso de no tener ciclos nuestro peor caso? Supongamos que el grafo es conexo, por simplifcación. Si el grafo no tiene ciclos, y es conexo, necesariamente se trata de un árbol. Para este caso, $$E = V - 1$$, por ende nuestro orden a fin de cuentas terminaría siendo $$\mathcal{O}(V)$$. ¿Esto implica que entonces nuestro algoritmo es en realidad $$\mathcal{O}(V)$$? No, significa que ese, que a priori podíamos pensar que era nuestro peor caso, en realidad no lo es. Nuestro peor caso implica que haya un ciclo, pero tener la mala suerte de tardar en encontrarlo. Ya sea porque el vértice en el que se empieza el recorrido está lejos del ciclo, o por el orden aleatorio de las cosas.

¿Cuáles serían las diferencias si en vez de trabajar con un grafo no dirigido, lo hiciéramos sobre un grafo dirigido? Notar que la solución no debería ser demasiado distinta a estas propuestas, pero tienen sus pequeñas diferencias que dejamos para resolver en los ejercicios propuestos. 

## Ejercicios propuestos

1. Implementar un algoritmo que, dado un grafo dirigido, nos devuelva un ciclo dentro del mismo, si es que los tiene. Indicar el orden del algoritmo. 

2. Un árbol es un grafo no dirigido que cumple con las siguientes propiedades:

    1. _\|E\| = \|V\| - 1_
    2. Es acíclico
    3. Es conexo

    Por teorema, si un grafo cumple dos de estas tres condiciones, será árbol (y por consiguiente, cumplirá la tercera). Haciendo uso de ésto (y únicamente de ésto), se pide implementar una función que reciba un grafo no dirigido y determine si se trata de un árbol, o no. Indicar el orden de la función implementada. 

3. Se tiene un grafo dirigido G, que representa la jerarquía de personal dentro de una empresa (es un _organigrama_). En este grafo los vértices modelan a personas, y una arista _(v, w)_ representa la relación _v es jefe directo de w_. 
Implementar una función que nos devuelva una secuencia para comunicar cierta noticia a todos los empleados, siendo que los cargos de mayor rango deben enterarse primero. Tener en cuenta que hay personas que tienen varios jefes, y que no pueden enterarse de la noticia antes que todos ellos. Además, podría haber más de un dueño/accionista de la empresa, por lo que no puede asumirse que haya una única persona sin jefe. 

4. Proponer una primitiva para calcular el grafo traspuesto $$G^T$$ de un grafo dirigido _G_. El grafo traspuesto $$G^T$$ posee los mismos vértices que G, pero con todas sus aristas invertidas (por cada arista _(v, w)_ en _G_, existe una arista _(w, v)_ en $$G^T$$) para un grafo implementado con:

    1. lista de adyancencias
    2. matriz de adyacencias

5. La teoría de los 6 grados de separación dice que cualquiera en la Tierra puede estar conectado a cualquier otra persona del planeta a través de una cadena de conocidos que no tiene más de cinco intermediarios (conectando a ambas personas con solo seis enlaces). Suponiendo que se tiene un grafo G en el que cada vértice es una persona y cada arista conecta gente que se conoce (el grafo es no dirigido): 

    1. Implementar un algoritmo para comprobar si se cumple tal teoría para todo el conjunto de personas representadas en el grafo G. Indicar el orden del algoritmo. 
    2. Suponiendo que en el grafo G no habrán altas ni bajas de vértices, pero podrían haberla de aristas (la gente se va conociendo), explicar ventajas y desventajas tendría implementar al grafo G con una matriz de adyacencia. 


## Bibliografía y referencias

- Weiss, Mark Allen: "Data Structures and Algorithms" (tercera edición), Pearson, 1999. Cap. 9: _Graph algorithms_.
- Kruse, Robert Leroy;  Tondon, Clovis L.;  Leung, Bruce P: "Data structures and program design in C", Prentice-Hall, 1997. Cap 10.4: _Graphs_
- Cormen, Thomas; Leiserson, Charles; Rivest, Ronald; Stein, Clifford: "Introduction to Algorithms" (tercera edición), MIT Press, 2009. Cap. 22: _Graphs_.
