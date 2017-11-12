---
layout: page
title: TP3 – Seis Grados de Kevin Bacon
permalink: '/tps/2017_2/tp3'
---

# Trabajo Práctico 3 - Seis Grados de Kevin Bacon

{:.no_toc}

## Contenido

{:.no_toc}

* Contenido
{:toc}

El Trabajo Práctico número 3 es de elaboración grupal, tiene fecha de entrega para el **viernes 1/12**, y
está divido en tres partes interconectadas:
* TDA Grafo
* Librería de funciones de grafos de actores
* Programa principal

## Introducción

Llega diciembre y la conocida comunidad IMDB está realizando un balance del año. Son devotos de conocer qué películas son las más populares y a qué actores se les podría llamar más famosos. 
Pero no solo quieren saber esto, ya que este año el CEO de la página escuchó sobre la idea de los “Seis grados de Kevin Bacon” y decidió que podía utilizar la enorme base de datos que maneja diariamente la página para corroborar la veracidad de esta idea.
Para esto, decidió sabiamente confiar en los alumnos de Algoritmos y Programación II de la FIUBA, aprovechando su conocimiento para poder así resolver el misterio.

## ¿Seis grados de separación? ¿Seis grados de Kevin Bacon? 

<p align="center">
  <img src=https://github.com/algoritmos-rw/algo2/blob/Enunciado-TP3/static/tps/2017_2/tp3/kv%20logo2.png>
</p>

"Seis grados de separación" es la idea que asegura que toda persona está a seis "pasos" o menos de cualquiera otra persona en el mundo, a partir de una cadena de conocidos. Por ejemplo, si Juan conoce a Martín y Martín conoce a Pedro, Juan está, entonces, a dos pasos de Pedro. Para más información de por qué esto se cumple se puede ver [este video](https://youtu.be/TcxZSmzPw8k).

La teoría de los "Seis grados de Kevin Bacon" lleva esta idea al cine, afirmando que el prolífico actor Kevin Bacon actuó en tantas peliculas y con tantos actores conocidos que está conectado a cualquier actor del mundo en una cadena de 6 películas como máximo.

Por ejemplo, con la idea de conectar a Naomi Watts con Kevin Bacon:

* Naomi Watts actuó con Sean Penn en _**21 Gramos.**_
* Sean Penn actuó con **Kevin Bacon** en _**Río Místico¹.**_

Por lo tanto, **Naomi Watts tiene un Kevin Bacon Number (KBN) de 2**.

Es importante ver que **el Bacon Number de un actor es siempre el mismo**, sin importar el camino. Esto es tanto porque los actores colaboren juntos en más de una película (De Naomi Watts a Sean Penn se puede llegar por _**The Assassination of Richard Nixon**_), como por que se tome un camino distinto (por ejemplo, Naomi Watts trabajo con Jeffrey Donovan en _**J Edgar**_ quien a su vez trabajo con Kevin Bacon en _**Sleepers**_).

¹Tanto _**Río Místico**_ como _**21 Gramos**_ son fuertes recomendaciones de muy buenas películas.

## Implementación

**El trabajo consiste de tres secciones**:

* El TDA Grafo, con sus primitivas. 

* Una librería de funciones de grafos, que permita hacer distintas operaciones sobre un grafo de actores/películas, sin importar quienes sean.

* El programa 'Seis grados de Kevin Bacon' que utilice tanto el TDA como la librería para poder implementar todo lo requerido poniendo el foco en Kevin Bacon.

El programa a realizar debe recibir por parámetro y cargar en memoria al dataset (`$ ./kevinbacon actors.csv`) y luego solicitar el ingreso de comandos por entrada estándar, del estilo `comando "parametro"`. Notar que esto permite tener un archivo de instrucciones a ser ejecutadas (`cat comandos.txt | ./kevinbacon actors.csv`).

Para lograr esto, IMDB nos proporcionó² un sets de datos, [`actors.csv`](https://drive.google.com/drive/folders/0B2J1xTZnFQnBVnZzcF8xR3Z3SVE?usp=sharing) (**comma separated values**) con un total de 2.480.000 actores y actrices y 800.000 películas. Este archivo se va a usar para generar un grafo donde los vértices sean actores y las aristas sean las películas en las que hayan colaborado, así conectándolos. Los demás algoritmos y recorridos trabajaran directamente usando las primitivas de este TDA. Cada linea de este archivo tiene el formato de `apellido nombre, pelicula1, pelicula2, pelicula3, ...` Por ejemplo:

```
Bacon Kevin,A Few Good Men (1992),A Little Vicious (1991),Animal House (1978),Apollo 13 (1995/I),Balto (1995),Beauty Shop (2005),Beyond All Boundaries (2009),Black Mass (2015),Cavedweller (2004),Cop Car (2015),Crazy Stupid Love (2011),Criminal Law (1988),Death Sentence (2007),Digging to China (1997),Diner (1982),Elephant White (2011),End of the Line (1987),Enormous Changes at the Last Minute (1983),Flatliners (1990),Footloose (1984),Forty Deuce (1982),Friday the 13th (1980),Frost/Nixon (2008),He Said She Said (1991),Hero at Large (1980),Hollow Man (2000),Jayne Mansfields Car (2012),JFK (1991),Lemon Sky (1988),Loverboy (2005),Murder in the First (1995),My Dog Skip (2000),My One and Only (2009),Mystic River (2003),New York Skyride (1994),Only When I Laugh (1981),Patriots Day (2016),Picture Perfect (1997),Pyrates (1991),Queens Logic (1991),Quicksilver (1986),RIPD (2013),Rails & Ties (2007),Saving Angelo (2007),Shes Having a Baby (1988),Sleepers (1996),Starting Over (1979),Stir of Echoes (1999),Super (2010/I),Telling Lies in America (1997),The Air I Breathe (2007),The Air Up There (1994),The Big Green (2014),The Big Picture (1989),The Darkness (2016/I),The Making of Apollo 13 (1995),The River Wild (1994),The Woodsman (2004),These Vagabond Shoes (2009),Tough Day (2014),Trapped (2002/I),Tremors (1990),Where the Truth Lies (2005),White Water Summer (1987),Wild Things (1998),X First Class (2011)
```

Siendo que `actors.csv` es muy pesado, un archivo de prueba más ligero, `test.csv`, también es proporcionado para probar resultados localmente. Este contiene lineas del archivo original escogidas al azar, más la linea de Kevin Bacon.

²Las bases de datos de IMDB eran un poco más confusas que las proporcionadas. Si quieren ver cómo se trabajo con el archivo original ir [acá.](https://github.com/FdelMazo/IMDBtoCSV/blob/master/)

### Primitivas del grafo

1. Crear grafo (y de ser necesario destruirlo).
1. Agregar y borrar arista.
1. Agregar y borrar vértice.
1. Obtener adyacentes de un vértice.
1. Verificar si dos vértices son adyacentes.
1. Obtener aristas.
1. Obtener vértices.

### Librería de funciones

1. _Camino_: 
 
   Dado dos actores, busca el camino **más corto** que recorre el primer actor para llegar al segundo.
   ```
   camino('Eastwood Clint', 'Bale Christian')
   >>> [('Eastwood Clint', 'Stiller Ben', 'Unite for Japan (2011)'), , ('Stiller Ben', 'Bale Christian' , 'Empire of The Sun (1987)')]
   ```

2. _Distancia_: 

   Los actores a n distancia del actor original son aquellos que esten n pasos del actor (ni más ni menos).
   ```
   distancia('Eastwood Clint', 2)
   >>> ['Rudd Paul', 'Douglas Michael', ...]
   ```
  
3. _Popularidad_ ⁴: 
 
   La popularidad de un actor puede ser medida por la sumatoria de con cuanta gente trabajo toda persona con la que el actor trabajó alguna vez, multiplicado por la cantidad de películas hechas por él.
    ```
    popularidad('Eastwood Clint')
    >>>  100640852
    ```
    
4. _Similares_:

    Encuentra  a los n actores más similares al actor dado.
    
    La similitud entre dos actores se refiere a dos actores que no hayan trabajado juntos entre sí, pero hayan trabajado con la mayor cantidad de actores en común.
    
    Para calcular la similitud, podemos utilizar [random walks](https://en.wikipedia.org/wiki/Random_walk). Un random walk es, como su nombre lo indica, un recorrido aleatorio. Comienza desde un vértice y se mueve aleatoriamente a un vecino; y luego, se mueve a un vecino de este, incluyendo el original. Este proceso continúa hasta que el recorrido cumpla con un largo n prefijado. Si realizamos muchos de estos recorridos aleatorios, partiendo desde el actor en cuestión y moviéndonos de forma completamente aleatoria, los actores que más veces aparezcan entre todos los recorridos, deben ser los más similares al actor de origen. Tener en cuenta que cuantos más largos y más recorridos se hagan, debería ser más preciso el algoritmo.
    ```
    similares('Eastwood Clint', 2)
    >>> ['Snyder Brian', 'Mortensen Viggo']
    ```

⁴El algoritmo de popularidad no es universal, fue pensado para el presente trabajo


### Comandos del programa

* Camino hasta Kevin Bacon

    Imprime y devuelve el camino de cómo llegar desde cualquier actor hasta Kevin Bacon. De no haber camino posible se debe imprimir un mensaje acorde y devolverse una lista vacía, y de no existir el actor ingresado se debe imprimir un mensaje acorde y devolver None.
```
camino_hasta_KB(grafo, 'Naomi Watts')
>>> 'Naomi Watts' actuó con 'Sean Penn' en 'Mystic River (2003)'.
>>> 'Sean Penn' actuó con 'Kevin Bacon' en '21 Grams (2003)'.
```

* Bacon Number

    Imprime y devuelve el Kevin Bacon Number del actor recibido. De no existir conexión entre los dos se debe imprimir un mensaje acorde y el KBN esperado es -1, y de no existir el actor ingresado se debe imprimir un mensaje acorde y devolver None. Tener en cuenta que el KBN de Kevin Bacon es 0.
```
bacon_number(grafo, 'Naomi Watts')
>>> 'Naomi Watts' tiene un Kevin Bacon Number igual a 2.
```

* Bacon Number mayor a 6 

    Imprime la cantidad de actores (¿existirán?) a una distancia mayor a 6 pasos de Kevin Bacon y devuelve el total de estos. De no existir actores a más pasos que 6, se imprime un mensaje acorde y se espera que se devuelva -1.
```
bacon_number_mayor_a_6(grafo)
>>> Los actores con un KBN mayor a 6 son:
>>> Con KBN igual a 6: N actores
>>> Con KBN igual a 7: N actores
>>> ...
``` 

* Bacon Number infinito

	Cuando un actor esta completamente desconectado de KB, es decir, no tiene forma de llegar a el, se dice que tiene un 'Kevin Bacon Number of infinity'.
	
	Imprime y devuelve cuantos actores (¿existirán?) con un KBN infinito hay. De no haber, se debe imprimir un mensaje acorde y devolver -1.
```
bacon_number_infinito(grafo)
>>>  Los actores con un Bacon Number infinito son N
``` 

* Bacon Number promedio

    Imprime y devuelve el Kevin Bacon Number promedio. En este numero no influyen la cantidad de actores con un KBN infinito.

```
KBN_promedio(grafo)
>>> El Kevin Bacon Number promedio es N
```

* Similares a Kevin Bacon

    ¿Si una película quisiese contratar a Kevin Bacon pero no tiene el presupuesto para pagarlo? ¡Contrata al que más se le parece!

    Imprime y devuelve una lista de los n actores más similares a Kevin Bacon, ordenados de mayor similitud a menor. 

```
similares_a_KB(grafo, 3)
>>> Los 3 actores más similares KB son  ['Buscemi Steve', 'Brocksmith Roy', 'Hollander Providence']
```

* Popularidad contra Kevin Bacon

    Todo el mundo sabe que Kevin Bacon es el actor más popular de todos. Usando su popularidad como base, imprime y devuelve en porcentaje cuán popular es el actor en comparación a KB. De no existir el actor ingresado, se debe imprimir un mensaje acorde y devolver None.

```
popularidad_contra_KB(grafo, 'Pattinson Robert')
>>> 'Pattinson Robert' es un 6.02 % de lo popular que es Kevin Bacon
```

* Estadísticas³: 
    
    1. Cantidad de películas: Imprime y devuelve la cantidad de películas en el dataset.
    1. Cantidad de actores: Imprime y devuelve la cantidad de actores en el dataset.

```
cantidad_peliculas(grafo)
>>> El dataset contiene 786879 películas.
cantidad_actores(grafo)
>>> El dataset contiene 2454209 actores.
```

³IMDB se copó tanto con Kevin Bacon que dejó el balance anual para el final de todo, ¡casi se olvidan!

# Trivia

Como última tarea, y con el proposito de darle un pequeño uso al programa realizado, dejamos está trivia (no obligatoría) para que puedan completar haciendo uso del progama:

  * ¿Hay algun actor argentino con un KBN infinito?
  * ¿Cuál es el actor argentino más popular con respecto a KB?
  * ¿Cuál es el actor argentino más similar a KB?
  * ¿Hay algun actor 'mejor' que Kevin Bacon para realizar este trabajo? Es decir, ¿hay algun actor más popular? ¿con más conexiones?

# Anexo: Links y más

Para ver una implementación online de Six Degrees of Bacon, pueden entrar al [Oracle de Bacon](https://oracleofbacon.org/). En su sección "How it Works" pueden encontrar información útil sobre teoría de grafos.

También tengan en cuenta que con solo escribir en Google, por ejemplo, `bacon number of Clint Eastwood` pueden rápidamente comprobar sus resultados.

Para una buena lectura sobre grafos en Python pueden leer [este ensayo](https://www.python.org/doc/essays/graphs/), y para un mejor manejo de clases pueden leer [acá](http://www.siafoo.net/article/57) y [acá](http://www.diveintopython3.net/special-method-names.html) acerca de los 'métodos magicos' (o 'dunder methods') de Python

# Criterios de aprobación

El trabajo puede ser realizado en cualquier lenguaje de programación y se pide 3 archivos: grafo, librería de grafos de actores y programa de Kevin Bacon. 

De ser realizado en Python, los archivos entregados deben ser:

* `grafo.py`.

* `grafo_lib.py`, que deberá contener una función `generar_grafo(nombre_archivo)`.

* `kevinbacon.py`, que deberá respetar los nombres y firmas de las funciones dadas en este enunciado.

