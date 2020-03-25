---
excerpt: |
  TP3 de Algoritmos II (2016/2): grafos. Fecha de entrega 2/12/16.
math: true
---

# TP 3: grafos en el mundo Marvel
{:.no_toc}

<img src="{{ 'assets/tps/2016_2/tp3/wachen_studios_box.jpeg' | relative_url }}" width="500" height="300" />


## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Objetivo

El objetivo de este Trabajo Práctico es usar el TDA grafo para modelar una red social y sus algoritmos para obtener información de ella.
En este caso trabajaremos con la red social conformada por los personajes de Marvel Comics.

## Algoritmos

Antes de pasar a la consigna vamos a explicar dos algoritmos que se van a utilizar.

### Random Walks
Un [Random Walk](https://en.wikipedia.org/wiki/Random_walk) es, como su nombre indica, un camino aleatorio sobre un grafo. Comienza desde un vértice (que puede ser uno específico o uno aleatorio) y se mueve aleatoriamente a un vecino; y luego, se mueve a un vecino (incluyendo el original) desde el nuevo vértice. Este proceso continúa hasta que el recorrido tenga un largo _n_ prefijado.
La probabilidad para movernos de un vértice a un vecino puede ser equiprobable (la misma para todos) o proporcional al peso que tenga cada arista (si el grafo fuera pesado), u otra alternativa dependiendo de la aplicación.
Finalmente, un aplicación que utiliza este algoritmo puede realizar varios recorridos. Por lo tanto, para realizar un random walk es necesario determinar:

* el largo del recorrido
* la probabilidad para movernos desde un vértice a sus vecinos
* la cantidad de recorridos a realizar

Todas estas caracterizaciones dependen de la aplicación del algoritmo.


### El problema de las Comunidades y Label Propagation
Un problema común dentro de grafos que representan redes sociales es querer obtener las comunidades que la conforman. Una comunidad dentro de una red social es un conjunto de vértices que se encuentran altamente conectados entre sí, y poco conectados con los vértices de afuera.
Este es un problema que está abarcado por el área de Aprendizaje No Supervisado (Clustering) dentro del Aprendizaje Automático.

Como estos temas no están incluidos dentro de los contenidos de la materia, usaremos un algoritmo sencillo que suele encontrar muy buenos resultados: [Label Propagation](http://arxiv.org/pdf/0709.2938v1.pdf). Dicho algoritmo es utilizado, por ejemplo, en Facebook para realizar inferencias.

En label propagation lo que hacemos es:

1) Para cada vértice $$V_i$$:

$$Label[V_i] = i$$

2) Determinar un orden aleatorio para los vértices.

3) Por cada vértice, en el orden determinado en el punto anterior, definir:

$$Label[V_i] = max\_freq(Label[V_j], ..., Label[V_k])$$

Donde $$V_j, ..., V_k$$ son los vértices adyacentes a $$V_i$$. Se tiene en cuenta la última actualización realizada, inclusive si ya fueron procesados en esta iteración (_actualización ascincrónica_).
$$max\_freq$$ es una función que devuelve la Label que aparece más frecuentemente entre todos los adyacentes a $$V_i$$.

4) Si no se llegó a la condición de corte, volver a 2. La condición de corte puede ser una vez que se llegó a una cantidad determinada de comunidades, se cree que se llegó a la convergencia (la mayoría de los vecinos de cada vértice tiene la misma Label que dicho vértice), o simplemente por una cantidad de iteraciones prefijada.

Como opción alternativa, brindamos otro algoritmo que utiliza Random Walks para obtener las posibles comunidades: [Entropy Walker](https://drive.google.com/file/d/0B8rBD4QSqWnSLTdWTXdFaUtUNjQ/view).

## Consigna

El trabajo práctico consiste de 2 partes:

1. La implementación del TDA grafo genérico. Se brinda una [interfaz](https://sites.google.com/site/fiuba7541rw/tps/grafo.zip?attredirects=0&d=1) que puede servir de guía, tanto en Python como en C. No es necesario que implementen todas las primitivas allí descritas, ni tampoco están restringidos a agregar otras que consideren adecuadas, o incluso darles otros nombres. Debe tomarse únicamente como guía, especialmente si no saben cómo comenzar.

2. Realizar un programa para realizar operaciones sobre nuestra red social.

La implementación del TDA grafo, y el posterior programa del trabajo práctico pueden realizarse en lenguaje de programación a elección, con previa aprobación del corrector asignado.

El programa a realizar debe recibir por parámetro la ruta del archivo con los datos de la red social:

	$ ./tp3 marvel.pjk

El archivo [marvel.pkj] que les proporcionamos está en formato _Pajek_. Este formato tiene la ventaja que es posible leer el grafo sin necesidad de un diccionario.

Como ejemplo del formato (ver la [documentación] para una descripción más extensa):

  - los vértices comienzan tras la línea marcada con `*Vertices V`, y las aristas tras `*Arcs`

  - la línea `*Vertices N` indica la cantidad de vértices $$V$$ para poder pre-reservar la memoria necesaria

  - la línea `*Vertices` va seguida del nombre de cada vértice entre comillas dobles (técnicamente los nombres son opcionales en la especificación del formato; nosotros los incluimos)

  - cada arista incluye vértice origen, vértice destino, y peso.

[documentación]: https://gephi.org/users/supported-graph-formats/pajek-net-format/
[marvel.pkj]: https://drive.google.com/file/d/0B837rronynczaUJXWHp4WDJ6bHM/view

Ejemplo:

```
*Vertices 4
1 "P. Uno"
2 "S. Personaje"
3 "P. T. Tercero"
4 "Personaje Último"
*Arcs
1 2 3
1 3 1
...
3 4 17
...
```

En este ejemplo hay solamente 4 personajes, y las aristas se leen tal que: “_P. Uno_ y _S. Personaje_ participan juntos en 3 comics juntos”. Por supuesto, la relación es recíproca, por lo que no se agrega la otra línea correspondiente (`2 1 3`).

El programa debe cargar la red social de dicho archivo en memoria, y luego esperar a que se ingresen comandos por entrada estándar. Los comandos se ejecutarán de la siguiente forma:

	> Comando parametro1, parametro2, ..., parametroN

### Comandos a Implementar

1. _Similares_: dado un personaje, encontrar los personajes más similares a este.

		Parámetros:
			Personaje: el personaje en cuestión, al que se le buscan los similares.
			Cantidad: la cantidad de personajes semejantes que se desean busca.

		Salida: De mayor a menor similaridad, los personajes ‘Cantidad’ personajes más similares al personaje indicado.
		Ejemplo:
			> similares IRON MAN, 3
			Salida de ejemplo:
			> CAPTAIN AMERICA, SPIDER-MAN, SCARLET WITCH


2. _Recomendar_: Dado un personaje con el cual se quiere realizar un nuevo comic, recomendar otro (u otros) personaje con el cual no haya participado aún en un comic, y sea lo más similar a él posible.

		Parámetros:
			Personaje: el personaje en cuestión, al que se le busca recomendar un nuevo compañero.
		Salida: Personaje a recomendar. Los ‘Cantidad’ personajes más similares al personaje, ordenados de mayor a menor similaridad.
		Ejemplo:
			> recomendar SPIDER-MAN, 5
			Salida de ejemplo:
			> JUBILEE, RICTOR, APOCALYPSE, DOMINO III, SKIDS


	Para implementar estos dos comandos, podemos utilizar **Random Walks**.
	¿Cómo esto nos puede ayudar a determinar si un personaje es similar a otro? Si realizamos muchos de estos recorridos aleatorios, partiendo desde el personaje en cuestión, moviéndonos de forma completamente aleatoria, el/los personajes que más veces aparezcan entre todos los recorridos, deben ser los más similares al personaje de origen. Este es un algoritmo bastante usado, por ejemplo en Twitter, para recomendar seguidores (sería similar a nuestro recomendar). Tener en cuenta que cuantos más largos y más recorridos se hagan, debería ser más preciso el algoritmo (en ambos casos, y siempre que se utilicen Random Walks).

3. _Camino_: Queremos que un comunicado llegue lo más rápido posible de un personaje A a un Personaje B. Sabemos que los personajes se reúnen usualmente con sus ex-compañeros, por lo que la mejor estrategia, para que el mensaje llegue rápido, es definir como “ruta de comunicación” a aquellos que con los cuales haya participado más veces en distintos comics.

		Parámetros:
			Personaje1: personaje de partida.
			Personaje2: personaje de llegada.
		Salida: Camino más corto en tiempo para llegar desde el Personaje1 al Personaje2.
		Ejemplo:
			> camino STAN LEE, CAPTAIN AMERICA
			Salida:
			> STAN LEE -> HUMAN TORCH -> CAPTAIN AMERICA

4. _Centralidad_ (o _Betweeness_): permite obtener los personajes más centrales de la red. Los personajes más centrales suelen ser a su vez los más importantes (o lo que se dice en redes sociales, influyente).

		Parámetros:
			Cantidad: la cantidad de personajes que se desean mostrar.
		Salida: Los ‘Cantidad’ Personajes más centrales de la red, mostrado de mayor a menor.
		Ejemplo:
			> centralidad 10

	Para implementar este comando recomendamos analizar estas dos formas:

	* _Centralidad exacta_: La definición correcta es que los vértices centrales son aquellos que aparecen más veces entre todos los caminos mínimos existentes en el grafo (sin contar los extremos de cada camino mínimo, por supuesto). Por ende, una forma de calcularlo es obtener todos los caminos mínimos (desde todos los vértices, hacia todos los vértices), luego determinar la cantidad de veces que aparece cada vértice en cada camino mínimo (sin ser extremo del mismo), y mostrar los K mayores.

	* _Centralidad con Random Walks_: Realizando muchos caminos largos, de forma aleatoria, comenzando desde cualquier vértice, suena razonable pensar que los personajes que más veces aparezcan entre todos los recorridos, deberían ser los más centrales. Por supuesto, esto es una aproximación.

	Cualquier opción elegida debe ser analizada con sus pros y contras en el informe a entregar (tener en cuenta el orden de cada algoritmo, y cuál es posible que sea más exacto).
	Si se deseara, puede implementarse dicho comando con sus dos alternativas (por supuesto, esto tendría un impacto positivo en la nota ;-) ).

5. _Distancias_: dado un personaje, obtener la cantidad de personajes que se encuentran a cada una de las distancias posibles, considerando las distancias como la cantidad de saltos (no tenemos en cuenta los eventuales pesos de las aristas del grafo).

		Parámetro:
			Personaje: personaje al cuál se le desean obtener las distancias.
		Salida:
			Distancia 1: cantidad de personajes adyacentes al personaje en cuestión.
			Distancia 2: cantidad de personajes a distancia 2 del personaje en cuestión.
			...
		Ejemplo:
			> distancias BLACK PANTHER
			Salida de ejemplo:
			> Distancia 1: 711
			> Distancia 2: 5498
			> Distancia 3: 183

6. _Estadísticas_: Muchas veces es de interés obtener ciertas estadísticas sobre las uniones del grafo. Nos interesa que nos muestre el total de vértices, el total de aristas, el promedio del grado de cada vértice, el desvío estándar del grado de cada vértice y la densidad del grafo (la proporción entre la cantidad de aristas, y la cantidad de aristas máximas que puede llegar tener el grafo, con esa cantidad de vértices).

		Parámetros:
			Ninguno
		Salida:
			“Cantidad de vértices: ...
			Cantidad de aristas: ...
			Promedio del grado de cada vértice: ...
			Desvío estándar del grado de cada vértice: ...
			Densidad del grafo: ...“
		Ejemplo:
			> estadisticas

7. _Comunidades_: Nos permite mostrar las comunidades que se encuentren en la red. Recomendamos utilizar el algoritmo de Label Propagation descrito en la introducción de este trabajo práctico.

		Parámetros:
			Ninguno
		Salida: Por cada comunidad, la cantidad de integrantes, y un listado con los integrantes.
		Filtrar las comunidades con muy pocos vértices (menos de 4), o con muchos vértices (más de 1000).


La entrega se realiza:

  1. por mail a la casilla de TPs (`tps.7541rw@gmail.com`): todos los archivos correspondientes (programa y TDA grafo) en un único archivo ZIP, más el informe como un adjunto PDF sin comprimir. En el asunto deben indicar: `TP3 - <Padrón 1> - <Apellido 1> - <Padrón 2> - <Apellido 2>`.
  2. en papel durante la clase (si su ayudante lo requiere), tanto el informe como el código.

El informe deberá consistir de las siguientes partes:

  * carátula con los datos personales del grupo y el ayudante asignado.
  * análisis y diseño de la solución, en particular: algoritmos y estructuras de datos utilizados; orden de ejecución de cada programa o función.

Nuevamente, pueden revisar el [informe de ejemplo](https://drive.google.com/open?id=11ufmyqYKWt18Ty3Wg0fxtjqU7slRU-MT) para la confección del mismo.

Adicionalmente los alentamos a sacar conclusiones sobre la estructura de la red social de Marvel. Además de estudiar el orden de los algoritmos, nos interesa ver qué conclusiones se puedan sacar conclusiones a partir de ellos.


**La fecha de entrega del Trabajo Práctico es el 2 de Diciembre de 2016.**

## Referencias y datos de interés

Una propiedad interesante que cumplen todas las redes sociales es que cumplen la [Ley de Potencias](https://en.wikipedia.org/wiki/Power_law) (en el caso de grafos, sobre el grado de los vértices). Es importante, antes de empezar a implementar algoritmos de redes sociales sobre un determinado grafo, revisar que dicho grafo cumple con la Ley de Potencias, para estar seguros que representa a una red social (por ejemplo, un grafo aleatorio tendría una distribución normal de los grados posibles). En el caso de nuestro set de datos, podemos ver que realmente se cumple dicha ley:

![Power Law Marvel]({{ 'assets/tps/2016_2/tp3/degree-distribution.png' | relative_url }})

1. [Trabajo base utilizado](http://courses.cs.washington.edu/courses/cse331/16wi/hws/hw6/hw6.html) y [Fuente original del que obtuvimos los datos](http://bioinfo.uib.es/~joemiro/marvel.html) (con transformación de los datos)
2. [Página con base de datos de personajes del Universo Marvel](http://marvelousdb.com/)
3. [Breve análisis sobre la composición de comunidades en el Universo Marvel](http://marvelentertainment.tumblr.com/post/30536120271/marvel-universe-data)
 (considerar que nuestros resultados pueden diferir, ya que Marvel tiene los datos de primera mano, y los nuestros datan de 2002).
4. [Video de la conferencia de Nueva York sobre Visualizaciones y análisis de datos, 2014](https://vimeo.com/88234257)
