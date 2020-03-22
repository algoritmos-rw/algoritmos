---
title: TP3 – Seis Grados de Kevin Bacon
---

# Trabajo Práctico 3 – Seis Grados de Kevin Bacon
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

<p style="text-align: center;">
  <img src="{{ 'assets/tps/2017_2/tp3/logo_tp3.png' | relative_url }}" width="300">
</p>

"Seis grados de separación" es la idea que asegura que toda persona está a seis "pasos" o menos de cualquiera otra persona en el mundo, a partir de una cadena de conocidos. Por ejemplo, si Juan conoce a Martín y Martín conoce a Pedro, Juan está, entonces, a dos pasos de Pedro. Para más información de por qué esto se cumple se puede ver [este video](https://youtu.be/TcxZSmzPw8k).

La teoría de los "Seis grados de Kevin Bacon" lleva esta idea al cine, afirmando que el prolífico actor Kevin Bacon actuó en tantas peliculas y con tantos actores conocidos que está conectado a cualquier actor del mundo en una cadena de seis películas como máximo.

Por ejemplo, con la idea de conectar a Naomi Watts con Kevin Bacon:

* Naomi Watts actuó con Sean Penn en _**21 Gramos.**_
* Sean Penn actuó con **Kevin Bacon** en _**Río Místico.**_¹

Por lo tanto, **Naomi Watts tiene un Kevin Bacon Number (KBN) de 2**.

Es importante ver que **el Bacon Number de un actor es siempre el mismo**, sin importar el camino. Esto es tanto porque los actores colaboren juntos en más de una película (de Naomi Watts a Sean Penn se puede llegar por _**The Assassination of Richard Nixon**_), como por que se tome un camino distinto (por ejemplo, Naomi Watts trabajo con Jeffrey Donovan en _**J Edgar**_ quien a su vez trabajo con Kevin Bacon en _**Sleepers**_).

Cuando un actor esta completamente desconectado de KB, es decir, no tiene forma de llegar a él, se dice que tiene un 'Kevin Bacon Number of infinity'.


¹Tanto _**Río Místico**_ como _**21 Gramos**_ son fuertes recomendaciones de muy buenas películas.

## Implementación

**El trabajo consiste de tres secciones**:

* El TDA Grafo, con sus primitivas.

* Una librería de funciones de grafos, que permita hacer distintas operaciones sobre un grafo de actores/películas, sin importar quienes sean.

* El programa 'Seis grados de Kevin Bacon' que utilice tanto el TDA como la librería para poder implementar todo lo requerido poniendo el foco en Kevin Bacon.

El programa a realizar debe recibir por parámetro y cargar en memoria el set de datos (`$ ./kevinbacon actors.csv`) y luego solicitar el ingreso de comandos por entrada estándar, del estilo `comando 'parametro'`. Notar que esto permite tener un archivo de instrucciones a ser ejecutadas (`cat comandos.txt | ./kevinbacon actors.csv`).

Para lograr esto, IMDB nos proporcionó² un sets de datos, [`actors.csv`](https://drive.google.com/drive/folders/0B2J1xTZnFQnBVnZzcF8xR3Z3SVE?usp=sharing) (**comma separated values**) con un total de 2.480.000 actores y actrices y 800.000 películas. Este archivo se va a usar para generar un grafo donde los vértices sean actores y las aristas sean las películas en las que hayan colaborado, así conectándolos. Los demás algoritmos y recorridos trabajaran directamente usando las primitivas de este TDA. Cada linea de este archivo tiene el formato de `apellido nombre, pelicula1, pelicula2, pelicula3, ...` Por ejemplo:

```
Bacon Kevin,A Few Good Men (1992),A Little Vicious (1991),Animal House (1978),Apollo 13 (1995/I),Balto (1995),Beauty Shop (2005),Beyond All Boundaries (2009),Black Mass (2015),Cavedweller (2004),Cop Car (2015),Crazy Stupid Love (2011),Criminal Law (1988),Death Sentence (2007),Digging to China (1997),Diner (1982),Elephant White (2011),End of the Line (1987),Enormous Changes at the Last Minute (1983),Flatliners (1990),Footloose (1984),Forty Deuce (1982),Friday the 13th (1980),Frost/Nixon (2008),He Said She Said (1991),Hero at Large (1980),Hollow Man (2000),Jayne Mansfields Car (2012),JFK (1991),Lemon Sky (1988),Loverboy (2005),Murder in the First (1995),My Dog Skip (2000),My One and Only (2009),Mystic River (2003),New York Skyride (1994),Only When I Laugh (1981),Patriots Day (2016),Picture Perfect (1997),Pyrates (1991),Queens Logic (1991),Quicksilver (1986),RIPD (2013),Rails & Ties (2007),Saving Angelo (2007),Shes Having a Baby (1988),Sleepers (1996),Starting Over (1979),Stir of Echoes (1999),Super (2010/I),Telling Lies in America (1997),The Air I Breathe (2007),The Air Up There (1994),The Big Green (2014),The Big Picture (1989),The Darkness (2016/I),The Making of Apollo 13 (1995),The River Wild (1994),The Woodsman (2004),These Vagabond Shoes (2009),Tough Day (2014),Trapped (2002/I),Tremors (1990),Where the Truth Lies (2005),White Water Summer (1987),Wild Things (1998),X First Class (2011)
```

Siendo que `actors.csv` es muy pesado, un archivo de prueba más ligero, `test.csv`, también es proporcionado para probar resultados localmente. Este contiene lineas del archivo original escogidas al azar, más la linea de Kevin Bacon.

²Las bases de datos de IMDB eran un poco más confusas que las proporcionadas. Si quieren ver cómo se trabajo con el archivo original ir [acá.](https://github.com/FdelMazo/IMDBtoCSV/)

### Primitivas del grafo

Se aclara previamente que no es necesario para el alcance de este TP hacer el grafo dirigido o pesado.

1. Crear grafo (y de ser necesario destruirlo).
1. Agregar y borrar arista. (tener en cuenta que en este trabajo las aristas tienen como nombre a la pelicula conectora)
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
   >>> [('Eastwood Clint', 'Stiller Ben', 'Unite for Japan (2011)') , ('Stiller Ben', 'Bale Christian' , 'Empire of The Sun (1987)')]
   ```

2. _Actores a distancia_:

   Los actores a _n_ distancia del actor original son aquellos que esten _n_ pasos del actor. Ordenarlos alfabéticamente.
   ```
   actores_a_distancia('Eastwood Clint', 2)
   >>> ['Douglas Michael', 'Rudd Paul', ...]
   ```

3. _Popularidad_ ⁴:

   Calculamos la popularidad de un actor como la sumatoria de la cantidad de personas con la que trabajó alguien que trabajó con él (es decir, los actores a distancia dos), multiplicado por la cantidad de películas en las que participó.
   ```
   popularidad('Eastwood Clint')
   >>> 100640852
   ```

4. _Similares_:

   Encuentra  a los _n_ actores más similares al actor dado.

   La similitud entre dos actores se refiere a dos actores que no hayan
   trabajado juntos entre sí, pero hayan trabajado con la mayor cantidad
   de actores en común.

   Para calcular la similitud, podemos utilizar [random walks](https://en.wikipedia.org/wiki/Random_walk),
   o recorrido aleatorio.
   Comienza desde un vértice de origen y se mueve aleatoriamente a un
   vecino; y luego, se mueve a un vecino de este, incluyendo el original.
   Este proceso continúa hasta que el camino cumpla con un largo _m_
   prefijado o proporcional a la cantidad de vértices del grafo.

   Si realizamos muchos de estos random walks, partiendo desde el actor en
   cuestión y moviéndonos de forma completamente aleatoria, los actores
   que más veces se visiten entre todos los recorridos, deben ser los más
   similares al actor de origen.

   Tener en cuenta que el algoritmo debería ser más preciso cuantos más
   largos y más recorridos se hagan.
   ```
   similares('Eastwood Clint', 2)
   >>> ['Snyder Brian', 'Mortensen Viggo']
   ```

   ⁴Esta métrica de popularidad es una estimación muy simple pero útil para el alcance de este trabajo práctico.


### Comandos del programa

* Camino hasta Kevin Bacon

    Imprime el camino más corto con el cual se llega desde cualquier actor hasta Kevin Bacon. De no haber camino posible se debe imprimir un mensaje acorde (por ejemplo: "No hay conexion entre KB y el actor"), y de no existir el actor ingresado se debe imprimir un mensaje acorde.
```
camino_hasta_KB 'Watts Naomi'
>>> 'Watts Naomi' actuó con 'Penn Sean' en 'Mystic River (2003)'.
>>> 'Penn Sean' actuó con 'Bacon Kevin' en '21 Grams (2003)'.
```

* Bacon Number

    Imprime el Kevin Bacon Number del actor recibido. Para representar un KBN infinito (no hay conexión entre KB y el actor) el KBN esperado es -1, y de no existir el actor ingresado se debe imprimir un mensaje acorde. Tener en cuenta que el KBN de Kevin Bacon es 0.
```
bacon_number 'Watts Naomi'
>>> 'Watts Naomi' tiene un Kevin Bacon Number igual a 2.
```

* Bacon Number mayor a 6

    Imprime la cantidad de actores (¿existirán?) a una distancia mayor a 6 pasos de Kevin Bacon. De no existir actores a más pasos que 6, se imprime un mensaje acorde. En este numero no influyen la cantidad de actores con un KBN infinito.
```
bacon_number_mayor_a_6
>>> Los actores con un KBN mayor a 6 son:
>>> Con KBN igual a 6: N actores
>>> Con KBN igual a 7: N actores
>>> ...
```

* Bacon Number infinito
	
	Imprime la cantidad de actores (¿existirán?) con un KBN infinito. De no haber, se debe imprimir un mensaje acorde.
```
bacon_number_infinito
>>> Los actores con un Bacon Number infinito son N
```

* Bacon Number promedio

    Imprime el Kevin Bacon Number promedio. En este numero no influyen la cantidad de actores con un KBN infinito, pero si lo hace el KBN de Kevin Bacon.
```
KBN_promedio
>>> El Kevin Bacon Number promedio es N
```

* Similares a Kevin Bacon

    ¿Si una película quisiese contratar a Kevin Bacon pero no tiene el presupuesto para pagarlo? ¡Contrata al que más se le parece!

    Imprime una lista de los n actores más similares a Kevin Bacon, ordenados de mayor similitud a menor.
```
similares_a_KB '3'
>>> Los 3 actores más similares KB son  ['Buscemi Steve', 'Brocksmith Roy', 'Hollander Providence']
```

* Popularidad contra Kevin Bacon

    Todo el mundo sabe que Kevin Bacon es el actor más popular de todos. Usando su popularidad como base, imprime en porcentaje cuán popular es el actor en comparación a KB. De no existir el actor ingresado, se debe imprimir un mensaje acorde y devolver None. Tener en cuenta que Kevin Bacon es un 100% de lo popular que es Kevin Bacon
```
popularidad_contra_KB 'Pattinson Robert'
>>> 'Pattinson Robert' es un 6.02% de lo popular que es Kevin Bacon
```

* Estadísticas ³:

    1. Cantidad de películas: imprime la cantidad de películas en el dataset.
    1. Cantidad de actores: imprime la cantidad de actores en el dataset.

    ```
cantidad_peliculas
>>> El dataset contiene 786879 películas.
cantidad_actores
>>> El dataset contiene 2454209 actores.
    ```

³IMDB se copó tanto con Kevin Bacon que dejó el balance anual para el final de todo, ¡casi se olvidan!

# Trivia

Como última tarea, y con el proposito de darle un pequeño uso al programa realizado, dejamos está trivia (no obligatoría) para que puedan completar haciendo uso del progama:

  * ¿Hay algun actor argentino con un KBN infinito?
  * ¿Cuál es el actor argentino más popular con respecto a KB?
  * ¿Cuál es el actor argentino más similar a KB?
  * ¿Hay algun actor 'mejor' que Kevin Bacon para realizar este trabajo? Es decir, ¿hay algun actor más popular? ¿con más conexiones?

# Anexo: links y más

Para ver una implementación online de Six Degrees of Bacon, pueden entrar al [Oracle de Bacon](https://oracleofbacon.org/). En su sección "How it Works" pueden encontrar información útil sobre teoría de grafos.

También tengan en cuenta que con solo escribir en Google, por ejemplo, `bacon number of Clint Eastwood` pueden rápidamente comprobar sus resultados.

Para una buena lectura sobre grafos en Python pueden leer [este ensayo](https://www.python.org/doc/essays/graphs/), y para un mejor manejo de clases pueden leer [acá](http://www.siafoo.net/article/57) y [acá](http://www.diveintopython3.net/special-method-names.html) acerca de sus 'métodos magicos' (o 'dunder methods').

# Criterios de aprobación

El trabajo puede ser realizado en cualquier lenguaje de programación previo acuerdo con el corrector, y debe estar separado al menos en tres módulos: grafo, librería de grafos de actores y programa de Kevin Bacon.

**Los resultados presentes en este enunciado no son definitivos, fueron dados solo como ejemplo.**

De ser realizado en Python, para poder ser probado, los nombres de dos de los archivos entregados deben ser:

* `seis_grados.py`, que deberá contener las funciones descriptas en la sección "[librería de funciones](#librería-de-funciones)".
  Se provee un archivo con los [prototipos de las funciones en Python]({{ 'assets/tps/2017_2/tp3/seis_grados.py' | relative_url }}).

* `kevin_bacon.py`, que deberá respetar la interfaz de entrada y salida de este enunciado, descriptas en la sección "[comandos del programa](#comandos-del-programa)".
