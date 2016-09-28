---
title: TP 3
layout: default
permalink: /:path/:basename/
---

# TP 3: Grafos en el mundo Marvel

## Objetivo

El objetivo de este trabajo práctico es ver la aplicación del TDA Grafo, los algoritmos vistos, y algunos más, en una situación real. 
En particular, vamos a estar trabajando con grafos que representan redes sociales. Más en detalle, vamos a estar trabajando con la red social conformada por los personajes de Marvel Comics.

## Introducción
Antes de pasar a la consigna vamos a explicar dos algoritmos que se van a utilizar.

### Random Walks
Un [Random Walk](https://en.wikipedia.org/wiki/Random_walk) (o camino aleatorio) en un grafo no es más que un camino aleatorio sobre dicho grafo. La idea es comenzar desde un vértice específico, o uno aleatorio, y luego desde allí movernos aleatoriamente a un vecino de dicho vértice. Luego, movernos a un vecino desde el nuevo vértice, incluyendo el original. Continuar hasta llegar a un recorrido de largo N (prefijado). La probabilidad para movernos de un vértice a un vecino puede ser equiprobable (la misma para todos), o proporcional al peso que tenga cada arista, si es que existiera (pudiendo ser también alguna otra distribución). 
Por lo tanto, lo que es necesario determinar es el largo del recorrido, que podría variar según la aplicación, y si vamos a considerar los pesos de las aristas, o no (movernos de un vértice a cualquier vecino es equiprobable). También, es muy probable que se requieran hacer varios de estos recorridos, por lo que otro parámetro a determinar es la cantidad de esos recorridos a realizar (nuevamente, puede depender de la aplicación).


### El problema de las Comunidades y Label Propagation
Un problema común dentro de grafos que representan redes sociales, es querer obtener las comunidades que conforman la red social. Una comunidad dentro de una red social es un conjunto de vértices que se encuentran altamente conectados entre sí, y poco conectados con los vértices de afuera (o menos conectados que la comunidad en la que se encuentran dichos vértices). Este es un problema que está abarcado por el área de Aprendizaje Automático, más precisamente Aprendizaje No Supervisado (Clustering). Por supuesto, dicho tema no está dentro de los contenidos de la materia, por lo que vamos a usar un algoritmo sencillo, y semejante a otros algoritmos que se ven en la materia, y que suele encontrar muy buenos resultados: [Label Propagation](http://arxiv.org/pdf/0709.2938v1.pdf). Dicho algoritmo es utilizado, por ejemplo, en Facebook para realizar inferencias (ciudad de origen, dentro de estas).
En label propagation lo que hacemos es:

1) Para cada vértice $$V_i, Label[V_i] = i$$
2) Determinar un orden aleatorio para los vértices.
3) Por cada vértice, en el orden determinado en el punto anterior, definir:
		$$Label[V_i] = max\_freq(Label[V_j], ..., Label[V_k])$$ 
	Donde $$V_j, ..., V_k$$ son los vértices adyacentes a $$V_i$$. Se tiene en cuenta la última actualización realizada, inclusive si ya fueron procesados en esta iteración (actualización ascincrónica; pueden leer en el paper original los problemas que puede acarrear la actualización sincrónica).
$$Max\_freq$$ es una función que devuelve la Label que aparece más frecuentemente entre todos los adyacentes a $$V_i$$.  
4. Si no se llegó a la condición de corte, volver a 2. La condición de corte puede ser una vez que se llegó a una cantidad determinada de comunidades, se cree que se llegó a la convergencia (la mayoría de los vecinos de cada vértice tiene la misma Label que dicho vértice), o simplemente por una cantidad de iteraciones prefijada. 

Como opción alternativa, brindamos otro algoritmo que utiliza Random Walks para obtener las posibles comunidades: [Entropy Walker](https://drive.google.com/file/d/0B8rBD4QSqWnSLTdWTXdFaUtUNjQ/view). 

## Consigna

El trabajo práctico consiste de 2 partes:
1) La implementación del TDA Grafo, de forma genérica. Se brinda una [interfaz](https://sites.google.com/site/fiuba7541rw/tps/grafo.zip?attredirects=0&d=1) que puede servir de guía, tanto en Python como en C. No es necesario que implementen todas las primitivas allí descritas, ni tampoco están restringidos a agregar otras que consideren adecuadas, o incluso darles otros nombres. Debe tomarse únicamente como guía, especialmente si no saben cómo comenzar. 
2) Realizar un programa para realizar operaciones sobre nuestra red social. 

La implementación del TDA Grafo, y el posterior programa del trabajo práctico pueden realizarse en lenguaje de programación a elección, con previa aprobación del corrector asignado. 

El programa a realizar debe recibir por parámetro la ruta del archivo con los datos de la red social: 

	$ ./tp3 marvel.tsv

El archivo marvel.tsv que nosotros les otorgamos es de la forma:
```
Personaje1		Personaje2		N1
Personaje1		Personaje3		N2
...
PersonajeY		PersonajeJ		Nx
...
```
Que se puede leer como: “El personaje1 y el personaje2 participan juntos en N1 comics juntos”. Por supuesto, la relación es recíproca, por lo que no se agrega la otra línea correspondiente (Personaje2, Personaje1, N1). El archivo es un “tsv”, similar a un “csv”, pero en el que cada campo está separado por tabulaciones en vez de comas. 

El programa debe cargar la red social de dicho archivo, y luego esperar a que se ingresen comandos por entrada estándar. Los comandos se ejecutarán de la siguiente forma:

	> Comando parametro1, parametro2, ..., parametroN

### Comandos a Implementar
1) _Similares_: dado un personaje, encontrar los personajes más similares a este.
   
	Parámetros:
		Personaje: el personaje en cuestión, al que se le buscan los similares.
		Cantidad: la cantidad de personajes semejantes que se desean busca.
		
	Salida: De mayor a menor similaridad, los personajes ‘Cantidad’ personajes más similares al personaje indicado.
	Ejemplo:
		> similares IRON MAN, 3
		Salida de ejemplo: 
		> CAPTAIN AMERICA, SPIDER-MAN, SCARLET WITCH
   

2) _Recomendar_: Dado un personaje con el cual se quiere realizar un nuevo comic, recomendar otro (u otros) personaje con el cual no haya participado aún en un comic, y sea lo más similar a él posible. 
   
	Parámetros: 
		Personaje: el personaje en cuestión, al que se le busca recomendar un nuevo compañero.
	Salida: Personaje a recomendar. Los ‘Cantidad’ personajes más similares al personaje, ordenados de mayor a menor similaridad.
	Ejemplo:
		> recomendar SPIDER-MAN, 5
		Salida de ejemplo:
		> JUBILEE, RICTOR, APOCALYPSE, DOMINO III, SKIDS
   

Para implementar estos dos comandos, podemos utilizar **Random Walks**.
¿Cómo esto nos puede ayudar a determinar si un personaje es similar a otro? Si realizamos muchos de estos recorridos aleatorios, partiendo desde el personaje en cuestión, moviéndonos de forma completamente aleatoria, el/los personajes que más veces aparezcan entre todos los recorridos, deben ser los más similares al personaje de origen. Este es un algoritmo bastante usado, por ejemplo en Twitter, para recomendar seguidores (sería similar a nuestro recomendar). 
	Tener en cuenta que cuantos más largos y más recorridos se hagan, debería ser más preciso el algoritmo (en ambos casos, y siempre que se utilicen Random Walks).

3) _Camino_: Queremos que un comunicado llegue lo más rápido posible de un personaje A a un Personaje B. Sabemos que los personajes se reúnen usualmente con sus ex-compañeros, por lo que la mejor estrategia, para que el mensaje llegue rápido, es definir como “ruta de comunicación” a aquellos que con los cuales haya participado más veces en distintos comics.
   
	Parámetros:
		Personaje1: personaje de partida.
		Personaje2: personaje de llegada.
	Salida: Camino más corto en tiempo para llegar desde el Personaje1 al Personaje2.
	Ejemplo:
		> camino STAN LEE, CAPTAIN AMERICA
		Salida:
		> STAN LEE -> HUMAN TORCH -> CAPTAIN AMERICA
   
4) Centralidad (o Betweeness): permite obtener los personajes más centrales de la red. Los personajes más centrales suelen ser a su vez los más importantes (o lo que se dice en redes sociales, influyente). 
   
	Parámetros: 
		Cantidad: la cantidad de personajes que se desean mostrar.	
	Salida: Los ‘Cantidad’ Personajes más centrales de la red, mostrado de mayor a menor.
	Ejemplo:
		> centralidad 10

Para implementar este comando recomendamos analizar estas dos formas:

a) _Centralidad exacta_: La definición correcta es que los vértices centrales son aquellos que aparecen más veces entre todos los caminos mínimos existentes en el grafo (sin contar los extremos de cada camino mínimo, por supuesto). Por ende, una forma de calcularlo es obtener todos los caminos mínimos (desde todos los vértices, hacia todos los vértices), luego determinar la cantidad de veces que aparece cada vértice en cada camino mínimo (sin ser extremo del mismo), y mostrar los K mayores.

b) _Centralidad con Random Walks_: Realizando muchos caminos largos, de forma aleatoria, comenzando desde cualquier vértice, suena razonable pensar que los personajes que más veces aparezcan entre todos los recorridos, deberían ser los más centrales. Por supuesto, esto es una aproximación. 

Cualquier opción elegida debe ser analizada con sus pros y contras en el informe a entregar (tener en cuenta el orden de cada algoritmo, y cuál es posible que sea más exacto). 
Si se deseara, puede implementarse dicho comando con sus dos alternativas (por supuesto, esto tendría un impacto positivo en la nota ;-) ).

5) _Distancias_: dado un personaje, obtener los personajes que se encuentran a cada una de las distancias posibles, considerando las distancias como la cantidad de saltos (no tenemos en cuenta los eventuales pesos de las aristas del grafo). 

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
	
6) _Estadísticas_: Muchas veces es de interés obtener ciertas estadísticas sobre las uniones del grafo. Nos interesa que nos muestre el total de vértices, el total de aristas, el promedio del grado de cada vértice, el desvío estándar del grado de cada vértice y la densidad del grafo (la proporción entre la cantidad de aristas, y la cantidad de aristas máximas que puede llegar tener el grafo, con esa cantidad de vértices).
	
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
	
7) _Comunidades_: Nos permite mostrar las comunidades que se encuentren en la red. Recomendamos utilizar el algoritmo de Label Propagation descrito en la introducción de este trabajo práctico.

	Parámetros:
		Ninguno
		Salida: Por cada comunidad, la cantidad de integrantes, y un listado con los		integrantes. Filtrar las comunidades con muy pocos vértices (menos de 4), o con muchos vértices (más de 1000). 

La entrega del trabajo práctico debe constar del código (tanto del programa como del TDA Grafo), así como del informe correspondiente, analizando el orden de cada uno de los comandos implementados en función de los algoritmos utilizados en cada caso. 
Además, en caso de sacar conclusiones sobre la estructura de la red social de marvel, es más que bienvenida, ya que además de estudiar el orden de los algoritmos, nos gusta ver que se puedan sacar conclusiones a partir de ellos!

**La fecha de entrega del Trabajo Práctico es el XX de Diciembre de 2016.** 

## Referencias y Datos de Interés

Una propiedad interesante que cumplen todas las redes sociales es que cumplen la [Ley de Potencias](https://en.wikipedia.org/wiki/Power_law) (en el caso de grafos, sobre el grado de los vértices). Es importante, antes de empezar a implementar algoritmos de redes sociales sobre un determinado grafo, revisar que dicho grafo cumple con la Ley de Potencias, para estar seguros que representa a una red social (por ejemplo, un grafo aleatorio tendría una distribución normal de los grados posibles). En el caso de nuestro set de datos, podemos ver que realmente se cumple dicha ley:

![Power Law Marvel](img "Power Law Marvel")

1. [Trabajo base utilizado](http://courses.cs.washington.edu/courses/cse331/16wi/hws/hw6/hw6.html) y [Fuente original del que obtuvimos los datos](http://bioinfo.uib.es/~joemiro/marvel.html) (con transformación de los datos)
2. [Página con base de datos de personajes del Universo Marvel](http://marvelousdb.com/)
3. [Breve análisis sobre la composición de comunidades en el Universo Marvel](http://marvelentertainment.tumblr.com/post/30536120271/marvel-universe-data)
 (considerar que nuestros resultados pueden diferir, ya que Marvel tiene los datos de primera mano, y los nuestros datan de 2002).
4. [Video de la conferencia de Nueva York sobre Visualizaciones y análisis de datos, 2014](https://vimeo.com/88234257)



