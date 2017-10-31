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
* TDA Grafo con sus primitivas
* Librería de funciones de grafos de actores
* Programa 'Seis grados de Kevin Bacon'

## Introducción

Llega diciembre y la conocida comunidad IMDB está realizando un balance del año. Son devotos de conocer qué películas son las más populares y a qué actores se les podría llamar más famosos. 
Pero no solo quieren saber esto, ya que este año el CEO de la página escuchó sobre la idea de los “Seis grados de Kevin Bacon” y decidió que podía utilizar la enorme base de datos que maneja diariamente la página para corroborar la veracidad de esta idea.
Para esto, decidió sabiamente confiar en los alumnos de Algoritmos y Programación II de la FIUBA, aprovechando su conocimiento para poder así resolver el misterio.

## Interludio: ¿Seis grados de separación? ¿Seis grados de Kevin Bacon? 

"Seis grados de separación" es la idea que asegura que toda persona está a seis "pasos" o menos de cualquiera otra persona en el mundo, a partir de una cadena de conocidos. Por ejemplo, si Juan conoce a Martín y Martín conoce a Pedro, Juan está, entonces, a dos pasos de Pedro. Para más información de por qué esto se cumple se puede ver [este video](https://youtu.be/TcxZSmzPw8k).

La teoría de los "Seis grados de Kevin Bacon" lleva esta idea al cine, afirmando que el prolífico actor Kevin Bacon actuó en tantas peliculas y con tantos actores conocidos que está conectado a cualquier actor del mundo en una cadena de 6 películas como máximo.

Por ejemplo, con la idea de conectar a Naomi Watts con Kevin Bacon:

* Naomi Watts actuó con Sean Penn en _**21 Gramos.**_
* Sean Penn actuó con **Kevin Bacon** en _**Río Místico¹.**_

Por lo tanto, **Naomi Watts tiene un Bacon Number de 2**.

Es importante ver que **el Bacon Number de un actor es siempre el mismo**, sin importar el camino. Esto es tanto porque los actores colaboren juntos en más de una película (De Naomi Watts a Sean Penn se puede llegar por _**The Assassination of Richard Nixon**_), como por que se tome un camino distinto (por ejemplo, Naomi Watts trabajo con Jeffrey Donovan en _**J Edgar**_ quien a su vez trabajo con Kevin Bacon en _**Sleepers**_).

¹Tanto _**Río Místico**_ como _**21 Gramos**_ son fuertes recomendaciones de muy buenas películas.

## Trabajo

IMDB nos pidió las siguientes funciones:

* camino_hasta_KB(actor)

Devuelve el camino de cómo llegar desde cualquier actor hasta Kevin Bacon. 
```
camino_hasta_KB("Naomi Watts")
>>> "Naomi Watts" actuó con "Sean Penn" en "Mystic River".
>>> "Sean Penn" actuó con "Kevin Bacon" en "21 Grams".
```

* bacon_number(actor)

Devuelve el Kevin Bacon Number del actor recibido.
```
bacon_number("Naomi Watts")
>>> "Naomi Watts" tiene un Kevin Bacon Number igual a 2.
```

* bacon_number_mayor_a_6() 

Devuelve los actores (¿existirán?) a una distancia mayor a 6 pasos de Kevin Bacon.
```
bacon_number_mayor_a_6()
>>> Los actores con un KBN mayor a 6 son: ???
```

* peliculas_mas_populares(n)

Devuelve las n películas más populares de Kevin Bacon. 

La "popularidad" de una película se puede calcular como el promedio de la popularidad de sus actores.
```
peliculas_mas_populares(2)
>>> Las 2 películas más populares de Kevin Bacon son: "Footloose", "X Men First Class".
```

* similares(n)

Devuelve los n actores más similares a Kevin Bacon. 

¿Si una película quisiese contratar a Kevin Bacon pero no tiene el presupuesto para pagarlo? ¡Contrata al que más se le parece!
```
similares(2)
>>> Los dos actores más similares KB son "Christopher Lee", "Morgan Freeman".
```

* popularidad_contra_KB(actor)

Todo el mundo sabe que Kevin Bacon es el actor más popular de todos. Usando su popularidad como base (puede ser calculada solamente una vez), devuelve en porcentaje cuán popular es el actor en comparación a KB.

```
popularidad_contra_KB("Robert Pattinson")
>>> "Robert Pattinson" es un 10% de lo popular que es Kevin Bacon
```

* KBN_promedio()

Devuelve cual es el Kevin Bacon Number promedio.

```
KBN_promedio()
>>> El Kevin Bacon Number promedio es N
```

* Estadísticas²: 
    
    1. cantidad_peliculas(): Devuelve la cantidad de películas en el dataset.
    1. cantidad_actores(): Devuelve la cantidad de actores en el dataset.
```
cantidad_peliculas()
>>> El dataset contiene N películas.
cantidad_actores()
>>> El dataset contiene N películas.
```

²IMDB se copó tanto con Kevin Bacon que dejó el balance anual para el final de todo, ¡casi se olvidan!

## Implementación

Para lograr todo esto, IMDB nos proporcionó³ un sets de datos, [`actors.csv`](https://drive.google.com/drive/folders/0B2J1xTZnFQnBVnZzcF8xR3Z3SVE?usp=sharing)⁴ (**comma separated values**) con un total de 2.480.000 actores. Este tiene el formato de `apellido nombre, pelicula1, pelicula2, pelicula3, ...` Por ejemplo:

```
Bacon Jon,Atlantic Blues (2009),I Fight Piranhas (2009),Violet Party (2009)
Bacon Karl,Catch 22 (2013)
Bacon Kevin (I),A Few Good Men (1992),A Little Vicious (1991),Animal House (1978),Apollo 13 (1995/I),Balto (1995),Beauty Shop (2005),Beyond All Boundaries (2009),Black Mass (2015),Cavedweller (2004),Cop Car (2015),Crazy Stupid Love (2011),Criminal Law (1988),Death Sentence (2007),Digging to China (1997),Diner (1982),Elephant White (2011),End of the Line (1987),Enormous Changes at the Last Minute (1983),Flatliners (1990),Footloose (1984),Forty Deuce (1982),Friday the 13th (1980),Frost/Nixon (2008),He Said She Said (1991),Hero at Large (1980),Hollow Man (2000),Jayne Mansfields Car (2012),JFK (1991),Lemon Sky (1988),Loverboy (2005),Murder in the First (1995),My Dog Skip (2000),My One and Only (2009),Mystic River (2003),New York Skyride (1994),Only When I Laugh (1981),Patriots Day (2016),Picture Perfect (1997),Pyrates (1991),Queens Logic (1991),Quicksilver (1986),RIPD (2013),Rails & Ties (2007),Saving Angelo (2007),Shes Having a Baby (1988),Sleepers (1996),Starting Over (1979),Stir of Echoes (1999),Super (2010/I),Telling Lies in America (1997),The Air I Breathe (2007),The Air Up There (1994),The Big Green (2014),The Big Picture (1989),The Darkness (2016/I),The Making of Apollo 13 (1995),The River Wild (1994),The Woodsman (2004),These Vagabond Shoes (2009),Tough Day (2014),Trapped (2002/I),Tremors (1990),Where the Truth Lies (2005),White Water Summer (1987),Wild Things (1998),X First Class (2011)
Bacon Kevin (II),Behind the Scene (2011)
Bacon Les,Barack Obama on 60 Minutes Talks Osama Bin Laden (2011)
Bacon Lewis,Beverley (2015)
```

Este archivo se va a usar para generar un grafo donde los vértices sean actores y las aristas sean las películas en las que hayan colaborado, así conectándolos. 

³Las bases de datos de IMDB eran un poco más confusas que las proporcionadas. Si quieren ver cómo se trabajo con el archivo original ir [acá.](https://github.com/FdelMazo/IMDBtoCSV/blob/master/imdbtocsv.py)

⁴Siendo que `actors.csv` es muy pesado, un archivo más ligero, `test.csv`, también es proporcionado para no tener que procesar el dataset entero a la hora de probar resultados localmente. Este contiene lineas del archivo original escogidas al azar, más la linea de Kevin Bacon.

### Primitivas del grafo

1. Crear grafo (y de ser necesario destruirlo).
1. Agregar y borrar arista.
1. Agregar y borrar vértice.
1. Obtener adyacentes de un vértice.
1. Verificar si dos vértices son adyacentes.
1. Obtener aristas.
1. Obtener vértices.

### Funciones a implementar

1. _Camino_: 
 
   Dado dos actores, devuelve el camino **más corto** que recorre el primer actor para llegar al segundo.
   ```
   camino("Clint Eastwood", "Christian Bale")
   >>> [("Empire of The Sun (1987)", "Clint Eastwood", "Ben Stiller"), ("Unite for Japan (2011)", "Ben Stiller", "Christian Bale")]
   ```

2. _Distancia_: 

   Devuelve la lista de actores a n pasos del actor (ni más ni menos). De n ser 0 debe devolver una lista con solo el nombre del actor
   ```
   distancia("Clint Eastwood", 2)
   >>> ["Paul Rudd", "Michael Douglas", ...]
   ```

3. _Cantidad Alcanzados_:

   Devuelve la cantidad de personas a las que puede llegar el actor ingresado. 
   ```
   cantidad_alcanzados("Clint Eastwood")
   >>> 2331685
   ```
   
4. _Popularidad_: 
 
    La popularidad⁵ de un actor puede ser medida por la sumatoria de a cuánta gente alcanza toda persona con la que el actor trabajó alguna vez, multiplicado por la cantidad de películas hechas por él.    
    ```
    popularidad("Clint Eastwood")
    >>>  ???
    ```

5. _Similares_:

    Devuelve una lista de los n actores más similares al actor dado.
    
	La similitud entre dos actores se refiere a dos actores que no hayan trabajado juntos entre sí, pero hayan trabajado con la mayor cantidad de actores en común
    ```
    similares("Clint Eastwood", 2)
    >>> ["Christian Bale", "Marlon Brando"]
    ```
⁵El algoritmo de popularidad no es universal, fue pensado para el presente trabajo

# Anexo: Links y más

Para ver una implementación online de Six Degrees of Bacon, pueden entrar al [Oracle de Bacon](https://oracleofbacon.org/). En su sección "How it Works" pueden encontrar información útil sobre teoría de grafos.

También tengan en cuenta que con solo escribir en Google, por ejemplo, `bacon number of Clint Eastwood` pueden rápidamente comprobar sus resultados.

Para una buena lectura sobre grafos en Python pueden leer [este ensayo](https://www.python.org/doc/essays/graphs/)

# Criterios de aprobación

El trabajo puede ser realizado en cualquier lenguaje de programación. 

Se pide 3 archivos: grafo, librería de grafos de actores y programa de Kevin Bacon. 
