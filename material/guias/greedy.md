---
math: true
---

# Algoritmos greedy
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Un camión debe viajar desde una ciudad a otra deteniéndose a cargar combustible cuando sea necesario. El tanque de combustible le permite viajar hasta _K_ kilometros.
Las estaciones se encuentran distribuidas a lo largo de la ruta siendo di la distancia desde la estación _i-1_ a la estación _i_.

1. Implementar un algoritmo que decida en qué estaciones debe cargar combustible de manera que se detenga la menor cantidad de veces posible.
2. ¿Cuál es la complejidad algorítmica?

### Solución

Desde un inicio, es muy probable que la primer idea que se nos ocurra sea "_vayamos hasta al estación de servicio más alejada desde el inicio, que se mantenga a distancia K, y hacer eso en cada paso_". Esa suena como una buena primera propuesta, ante lo cual deberíamos preguntarnos:

- ¿Es este un algorito greedy?
    Por supuesto. Notar que lo que busca un algoritmo greedy es que, utilizando reglas sencillas (y aplicándolas iterativamente), lograr que *el óptimo local en cada paso nos lleve al óptimo global*. En este caso, el óptimo desde el punto en el que nos encontremos, ir "hasta tan lejos como podamos" es claramente buscar el óptimo local, y que la sucesión de estos nos lleve al global.

- ¿Es óptima la solución?
    A veces es difícil saber si la solución greedy es óptima, pero en este caso debería ser fácil verlo. Si nos cuesta tanto encontrar un contraejemplo, suele pasar (no siempre) que suele ser óptima la solución (en problemas más complejos, y con mejores aproximaciones, puede ser difícil de ver que no lo sea). Acá, intentar ir hasta tan lejos como podamos, es imposible que eso no nos lleve a la mejor solución.
    Llegado el caso, puede haber otra solución, pero que será igual de óptima (misma cantidad de veces que se carga el tanque de nafta).
    En el libro _Algorithm Design_ de Kleinberg y Tardos, capítulo de algoritmos Greedy, se encuentra este mismo problema con otro enunciado, con la misma explicación intuitiva, pero además la demostración matemática de por qué esta solución es óptima.

Implementación de la solución:


```python
def carga_estaciones(L, K, total_km):
    # Asumimos que nunca L[i] > K, y que sum(L) + K <= total_km (que siempre cargando en la ultima llegamos al final),
    # sino no habrá solución
    restante = K
    estaciones = []

    # Agregamos una "estacion de mentira" al final del camino, para no tener que considerar
    # al final del camino como un caso especial
    if sum(L) < total_km:
        L.append(total_km - sum(L))

    for indice in L:
        if indice + 1 == len(L):
            continue
        # Resto lo que recorri para llegar hasta esta estacion
        restante -= L[indice]
        # Es necesario cargar? Que tan lejos queda la siguiente estacion?
        if restante < L[indice + 1]:
            # No llego a la siguiente con la carga que tengo, asi que cargo aca
            estaciones.append(indice)
            restante = K

    return estaciones
```
Para la pregunta de la complejidad, se ve que pasamos una vez por cada estación para validar la condición, y una sola vez, y nada depende del valor de $$K$$. Por lo tanto, el algoritmo es $$\mathcal{O}(n)$$, con $$n = |L|$$.

## Ejercicios propuestos

1.  Se tienen paquetes que se quieren transportar, y camiones para realizar dichos transportes. Cada camión puede utilizarse más de una vez, y puede utilizarse para algunos paquetes (no todos los camiones pueden transportar todos los paquetes, se conoce cuáles paquetes puede llevar cada camión) y cada camión tiene un costo de envío diferente (por cada paquete se debe realizar un envío por separado).

    Proponer, en pseudocódigo, un algoritmo Greedy que permita determinar qué camiones utilizar para cada paquete, de forma de minimizar los costos. ¿Por qué el algoritmo implementado es de tipo Greedy? ¿Cuál es el orden de dicho algoritmo? ¿Es óptima (siempre) la solución? Justificar.

2. Las bolsas de un supermercado se cobran por separado y soportan hasta un peso máximo _P_, por encima del cual se rompen.

   Implementar el pseudocódigo de un algoritmo greedy que, teniendo una lista de pesos de _n_ productos comprados, encuentre la mejor forma de distribuir los productos en la menor cantidad posible de bolsas.

   Realizar el seguimiento del algoritmo propuesto para bolsas con peso máximo 5 y para una lista con los pesos: `[ 4, 2, 1, 3, 5 ]`.
¿El algoritmo implementado encuentra siempre la solución óptima? Justificar.

3. Una empresa tiene _n_ empleados, y _k_ proyectos posibles a realizar. Cada proyecto debe ser realizado por unos empleados en particular, y cada empleado puede realizar a lo sumo dos trabajos en total, en el tiempo que se tiene destinado para realizar todos los proyectos (suponer que podrían trabajar en ambos en simultáneo).

   Por lo tanto, puede no ser posible realizar todos los proyectos. Implementar un algoritmo greedy que permita determinar los proyectos a realizar, de forma de maximizar las ganancias (cada proyecto da una ganancia distinta).

   Teniendo en cuenta que los valores de _n_ y _k_ son independientes, ¿cuál es el orden del algoritmo? ¿Es óptimo? Justificar.

4. El siguiente algoritmo encuentra una farmacia abierta:
    1. Tengo un papel en donde voy a ir anotando la lista de farmacias visitadas, inicialmente vacía.
    2. Ir a la farmacia más cercana que no esté en la lista.
    3. Si está de turno, llegue.
    4. Si no, anotar la farmacia en la que estoy, y repetir desde (2).

   Responder:
    1. ¿Es esta un algoritmo de tipo Greedy? ¿Por qué?
    2. ¿Encuentra siempre alguna solución? Si encuentra una solución, ¿podemos estar seguros de que es la mejor?
Justificar.

## Bibliografía y referencias

- Weiss, Mark Allen: "Data Structures and Algorithms" (tercera edición), Pearson, 1999. Cap. 10.1: _Greedy algorithms_.
- Kruse, Robert Leroy;  Tondon, Clovis L.;  Leung, Bruce P: "Data structures and program design in C", Prentice-Hall, 1997. Cap 12.5: _A Greedy Algorithm_
- Guerequeta, Rosa; Vallecillo, Antonio: "Técnicas de Diseño de Algoritmos" (segunda edición), Servicio de Publicaciones de la Universidad de Málaga, 1998. Cap 4: _Algoritmos ávidos_.
- Cormen, Thomas; Leiserson, Charles; Rivest, Ronald; Stein, Clifford: "Introduction to Algorithms" (tercera edición), MIT Press, 2009. Cap. 16: _Greedy algorithms_.
