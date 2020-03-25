---
title: TP 3
excerpt: |
  TP3 de Algoritmos II (2017/1): grafos. Fecha de entrega 23/06.
math: true
---

# Grafos en YouTube
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Objetivo

El objetivo de este Trabajo Práctico es usar el TDA grafo y sus algoritmos para modelar una red social y obtener información de ella.
En este caso trabajaremos con la red social conformada por los usuarios de [YouTube](http://www.youtube.com).

## Algoritmos

Antes de pasar a la consigna vamos a explicar dos algoritmos que se van a utilizar.

### Random walks
Un [random walk](https://en.wikipedia.org/wiki/Random_walk) es, como su nombre indica, un camino aleatorio sobre un grafo. Comienza desde un vértice (que puede ser uno específico o uno aleatorio) y se mueve aleatoriamente a un vecino; y luego, se mueve a un vecino (incluyendo el original) desde el nuevo vértice. Este proceso continúa hasta que el recorrido tenga un largo _n_ prefijado.
La probabilidad para movernos de un vértice a un vecino puede ser equiprobable (la misma para todos) o proporcional al peso que tenga cada arista (si el grafo fuera pesado), u otra alternativa dependiendo de la aplicación.
Finalmente, un aplicación que utiliza este algoritmo puede realizar varios recorridos. Por lo tanto, para realizar un random walk es necesario determinar:

* el largo del recorrido
* la probabilidad para movernos desde un vértice a sus vecinos
* la cantidad de recorridos a realizar

Todas estas caracterizaciones dependen de la aplicación del algoritmo.


### Comunidades y label propagation
Un problema común dentro de grafos que representan redes sociales es querer obtener las comunidades que la conforman. Una comunidad dentro de una red social es un conjunto de vértices que se encuentran altamente conectados entre sí, y poco conectados con los vértices de afuera.
Este es un problema que está abarcado por el área de Aprendizaje No Supervisado (Clustering) dentro del Aprendizaje Automático.

Como estos temas no están incluidos dentro de los contenidos de la materia, usaremos un algoritmo sencillo que suele encontrar muy buenos resultados: [label propagation](http://arxiv.org/pdf/0709.2938v1.pdf). Dicho algoritmo es utilizado, por ejemplo, en Facebook para realizar inferencias de posibles amistades.

En label propagation lo que hacemos es:

  1) Para cada vértice $$V_i$$:

  $$Label[V_i] = i$$

  2) Determinar un orden aleatorio para los vértices.

  3) Por cada vértice, en el orden determinado en el punto anterior, definir:

  $$Label[V_i] = max\_freq(Label[V_j], ..., Label[V_k])$$

  Donde $$V_j, ..., V_k$$ son los vértices adyacentes a $$V_i$$. Se tiene en cuenta la última actualización realizada, inclusive si ya fueron procesados en esta iteración (_actualización ascincrónica_).
  $$max\_freq$$ es una función que devuelve la etiqueta que aparece más frecuentemente entre todos los adyacentes a $$V_i$$.

  4) Si no se llegó a la condición de corte, volver a 2. La condición de corte puede ser una vez que se llegó a una cantidad determinada de comunidades, se cree que se llegó a la convergencia (la mayoría de los vecinos de cada vértice tiene la misma Label que dicho vértice), o simplemente por una cantidad de iteraciones prefijada.

Como opción alternativa, brindamos otro algoritmo que utiliza random walks para obtener las posibles comunidades: [entropy walker](https://drive.google.com/file/d/0B8rBD4QSqWnSLTdWTXdFaUtUNjQ/view).

## Consigna

El trabajo práctico consiste de dos partes:

1. La implementación del TDA grafo mínimo, como fue explicado en clase, con las primitivas:
	* Crear un grafo. En caso de necesitarlo, una primitiva para poder destruirlo.
	* Agregar y quitar un vértice.
	* Agregar y quitar una arista. **Atención**: tener en cuenta si se trata de un grafo dirigido o no dirigido.
	* Verificar si dos vértices son adyacentes.
	* Obtener los adyacentes de un vértice.
	* Verificar si un vértice existe en el grafo.
	* Obtener todos los identificadores del grafo.
	* Obtener la cantidad de vértices del grafo.
	* La posibilidad de iterar el grafo. La forma de realizar esto dependerá del lenguaje elegido para la implementación del TP.

2. Implementar un programa para realizar operaciones sobre nuestra red social.

La implementación del TDA grafo, y el posterior programa del trabajo práctico pueden realizarse en lenguaje de programación a elección, con previa aprobación del corrector asignado.

El programa a realizar debe recibir por parámetro la ruta del archivo con los datos de la red social:

	$ ./tp3 youtube.txt

El archivo se puede obtener de la página del [Proyecto de Análisis de Redes de la Universidad de Stanford](https://snap.stanford.edu/about.html), descargable [aquí](https://snap.stanford.edu/data/bigdata/communities/com-youtube.ungraph.txt.gz).

El fichero tiene las relaciones de la red social de YouTube.
El formato que tiene el archivo son unas líneas de cabecera, donde se pueden obtener la cantidad de nodos y aristas totales (útiles, por ejemplo, si interesara implementarse el grafo con una matriz de adyacencia), y luego las uniones entre vértices (identificados con números, puesto que se anonimizaron los datos), separados por tabulaciones. Tener en cuenta que no hay peso en dichas uniones.

El programa debe cargar la red social de dicho archivo en memoria, y luego solicitar el ingreso de comandos por entrada estándar.
Los comandos se ejecutarán de la siguiente forma:

	> comando parametro1 parametro2 ... parametroN

Notar que esto permite tener un archivo de instrucciones a ser ejecutadas:

	> cat comandos.txt | ./tp3 youtube.txt

### Comandos a implementar

1. _Similares_: dado un usuario, encontrar los personajes más similares a este.

	Parámetros:
	- _id_: el id del usuario.
	- _n_: la cantidad de usuarios semejantes que se desea buscar.

	Salida: los _n_ usuarios más similares al indicado, ordenados de mayor a menor similaridad.

	Ejemplo:

			> similares 1 5
			> 20 22 21583 1219 3

2. _Recomendar_: dado un usuario, recomendar otro (u otros) usuario con el cual aún no tenga relación, y sea lo más similar a él posible.

	Parámetros:
	- _id_: el id del usuario en cuestión.
	- _n_: la cantidad de usuarios a recomendar.

	Salida: los _n_ usuarios más similares al indicado, ordenados de mayor a menor similaridad.

	Ejemplo:

			> recomendar 5 4
			> 1072, 884, 29664, 29686


	Para implementar estos dos comandos, podemos utilizar **random walks**.

	¿Cómo esto nos puede ayudar a determinar si un usuario es similar a otro? Si realizamos muchos de estos recorridos aleatorios, partiendo desde el usuario en cuestión, moviéndonos de forma completamente aleatoria, el/los usuarios que más veces aparezcan entre todos los recorridos, deben ser los más similares al usuario de origen. Este es un algoritmo bastante usado, por ejemplo en Twitter, para recomendar seguidores.
  Tener en cuenta que cuantos más largos y más recorridos se hagan, debería ser más preciso el algoritmo.

3. _Camino_: queremos que un comunicado llegue lo más rápido posible de un usuario A a un usuario B.
  Sabemos que un usuario puede comunicar su mensaje solo a sus contactos directos, por lo que la mejor estrategia será pasar por la menor cantidad de usuarios posibles. Tener presente que es posible que el grafo tenga más de una componente conexa, por lo que pueden haber vértices entre los cuales no exista camino posible.

	Parámetros:
	- _id1_: el id del usuario de partida.
	- _id2_: el id del usuario de llegada.

	Salida: camino más corto para llegar desde el usuario con _id1_ al usuario con _id2_.

	Ejemplo 1:

			> camino 11 1991
			> 11 -> 663545 -> 106 -> 1991

	Ejemplo 2:

			> camino 1, 7
			> 1 -> 7

4. _Centralidad_ (o _Betweeness_): permite obtener los usuarios más centrales de la red. Los usuarios más centrales suelen ser a su vez los más importantes (o como se denomina en redes sociales, influyente).

	Parámetros:
	- _n_: la cantidad de usuarios que se desean mostrar.

	Salida: los _n_ usuarios más centrales de la red, ordenados de mayor a menor.

	Ejemplo:

			> centralidad 3
			> 83 663545 832

	Para implementar este comando recomendamos analizar estas dos formas:

	* _Centralidad exacta_: por definición, los vértices centrales son aquellos que aparecen más veces entre todos los caminos mínimos existentes en el grafo (sin contar los extremos de cada camino mínimo, por supuesto).
  Por ende, una forma de calcularlo es obtener todos los caminos mínimos (desde todos los vértices, hacia todos los vértices), luego determinar la cantidad de veces que aparece cada vértice en cada uno.

	* _Centralidad con random walks_: realizando muchos caminos largos, de forma aleatoria, comenzando desde cualquier vértice, suena razonable pensar que los usuarios que más veces aparezcan entre todos los recorridos, deberían ser los más centrales. Por supuesto, esto es una aproximación.

	Cualquier opción elegida debe ser analizada con sus pros y contras en el informe a entregar (tener en cuenta el orden de cada algoritmo, y cuál es posible que sea más exacto).
	Si se deseara, puede implementarse dicho comando con sus dos alternativas (por supuesto, esto tendría un impacto positivo en la nota).

5. _Distancias_: dado un usuario, obtener la cantidad de personajes que se encuentran a cada una de las distancias posibles, considerando las distancias como la cantidad de saltos.

	Parámetro:
	- _id_: el id del usuario al cuál se le desean obtener las distancias.

	Salida:
	- Distancia 1: cantidad de usuarios adyacentes al usuario en cuestión.
	- Distancia 2: cantidad de usuarios a distancia 2 del usuario en cuestión.
	- etc.

	Ejemplo:

			> distancias 9
			> Distancia 1: 1
			> Distancia 2: 28
			> Distancia 3: 7147
			> Distancia 4: 233773
			> Distancia 5: 573173
			> Distancia 6: 236908
			> Distancia 7: 62668
			> Distancia 8: 15824
			> Distancia 9: 3923
			> Distancia 10: 1091
			> Distancia 11: 235
			> Distancia 12: 78
			> Distancia 13: 23
			> Distancia 14: 17

6. _Estadísticas_: muchas veces es de interés obtener ciertas estadísticas sobre las uniones del grafo. Nos interesa que nos muestre el total de vértices, el total de aristas, el promedio del grado de cada vértice y la densidad del grafo (la proporción entre la cantidad de aristas, y la cantidad de aristas máximas que puede llegar tener el grafo, con esa cantidad de vértices).

	Parámetros: (ninguno)

	Salida:
	- Cantidad de vértices.
	- Cantidad de aristas.
	- Promedio del grado de entrada cada vértice.
	- Promedio del grado de salida cada vértice.
	- Densidad del grafo.

	Ejemplo:

			> estadisticas
			> Cantidad de vértices: 12
			> Cantidad de aristas: 144
			> Promedio de grado de entrada de cada vértice: 11
			> Promedio de grado de salida de cada vértice: 11
			> Densidad del grafo: 1

7. _Comunidades_: nos permite mostrar las comunidades que se encuentren en la red. Recomendamos utilizar el algoritmo de Label Propagation descrito en la introducción de este trabajo práctico.

	Parámetros: (ninguno)
	Salida: Por cada comunidad, la cantidad de integrantes, y un listado con los integrantes. Filtrar las comunidades con muy pocos vértices (menos de 4), o con muchos vértices (más de 2000).


La entrega se realiza:

  1. por mail a la casilla de TPs (`tps.7541rw@gmail.com`): todos los archivos correspondientes (programa y TDA grafo) en un único archivo ZIP, más un breve informe como un adjunto PDF sin comprimir. En el asunto deben indicar: `TP3 - <Padrón 1> - <Apellido 1> - <Padrón 2> - <Apellido 2>`.
  2. en papel durante la clase (si su ayudante lo requiere), tanto el informe como el código.

El informe deberá explicar brevemente los algoritmos y estructuras de datos utilizados; orden de ejecución de cada programa o función.

Adicionalmente los alentamos a sacar conclusiones sobre la estructura de la red social de YouTube. Además de estudiar el orden de los algoritmos, nos interesa ver qué conclusiones se puedan sacar conclusiones a partir de ellos.

**La fecha de entrega del Trabajo Práctico es el 23 de Junio de 2017.**


## Ley de potencias

Una propiedad interesante que cumplen todas las redes sociales es que cumplen la [Ley de Potencias](https://en.wikipedia.org/wiki/Power_law) (en el caso de grafos, sobre el grado de los vértices). Es importante, antes de empezar a implementar algoritmos de redes sociales sobre un determinado grafo, revisar que dicho grafo cumple con la Ley de Potencias, para estar seguros que representa a una red social (por ejemplo, un grafo aleatorio tendría una distribución normal de los grados posibles).
