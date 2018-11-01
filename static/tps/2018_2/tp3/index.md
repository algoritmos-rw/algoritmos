---
layout: page
title: "TP3 – Grafos y aeropuertos"
permalink: '/tps/2018_2/tp3'
math: true
---

Trabajo Práctico 3
================
{:.no_toc}

El Trabajo Práctico número 3 es de elaboración grupal, y tiene fecha de entrega
para el **bla bla bla**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}


## Introducción

Debido al éxito rotundo del nuevo software en el aeropuerto de Algueiza, las distintas 
aerolíneas del mundo (!) nos han pedido que desarollemos un programa que permita 
dar información sobre las conexiones entre los aeropuertos. Son tantos, pero tantos los 
pedidos que será necesario limitar la cantidad de _features_ a implementar para poder 
llegar con la fecha de entrega. Eso sí, será necesario lograr que el programa tenga el 
suficiente valor para poder dejar a todos medianamente contentos.

## Análisis de la situación 

Las aerolíneas distintas partes del mundo, requieren distintos tipos de funcionalidades:
* Todas las aerolíneas quieren que los clientes puedan buscar el camino más rápido, 
el más barato, o el de menor cantidad de escalas, a gusto.
* Para poder entender donde conviene invertir en mayor infraestructura, se quiere obtener 
cuáles son los aeropuertos más importantes, teniendo en cuenta sobre cuáles es más frecuente
terminar haciendo escalas para poder ir entre cualquier parte del mundo a otra. 
* Una nueva aerolínea (bAIRros Airlines, con sede principal en el aeropuerto de Lanús) 
quiere poder conectar absolutamente todo el mundo, pero quiere utilizar las rutas más baratas 
posibles para ello. Entre tantos datos que hay, no saben por dónde empezar!
* Algunas aerolíneas querrían poder agregar (en sus sofisticados sistemas de recomendación) la
posibilidad de ofrecer un viaje alrededor del mundo: poder visitar todo el mundo, con el menor 
costo o tiempo posible.
* Sobre lo anterior, algunas aerolíneas quieren que sea la mejor solución posible, sin excepciones.
Otras, entienden que la capacidad de computo de dicha solución puede llevar mucho tiempo para sus 
_no tan capaces_ servidores (comparten capacidad junto con el sistema SIU Guaraní de la FIUBA). 
Por ello, aceptarían una _buena solución_ que se calcule rápidamente. 
* Algunas aerolíneas querrían ofrecer un viaje que empiece desde la ciudad del cliente, y
haga un viaje por alguna cantidad de ciudades del mundo y vuelva luego a la ciudad origen 
(así pueden ofrecer descuentos para tentar a los cliente).
* Otras aerolíneas pidieron poder ofrecer un viaje cultural: que se pueda indicar qué ciudades se
quieren conocer, y además si hay alguna ciudad que deba visitarse antes que otra (para poder
disfrutar más del viaje). 
* Poder obtener estadísticas de las rutas de vuelo. 
* Poder exportar un mapa que nos permita visualizar las rutas de vuelo. 

## Datos disponibles

Se cuenta con los datos de los [aeropuertos](https://www.kaggle.com/usdot/flight-delays/version/1#airports.csv), así como de más de medio millón de [vuelos](https://www.kaggle.com/usdot/flight-delays/version/1#flights.csv) durante el año 2015. 

Para evitar tener que realizar el procesamiento, se incluye el archivo [aeropuertos.csv](sarasa)
con el formato:
```
aeropuerto_i,ciudad,latitud,longitud
```
Y el archivo [conexiones](saralala) con el formato: 
```
aeropuerto_i,aeropuerto_j,distancia,precio,cant_vuelos_entre_aeropuertos
```
_Aclaración_: Si bien es más interesante el tiempo que la distancia entre aeropuertos, y no siempre
la relación es necesariamente directa (por las rutas de vuelo), podemos considerar ésto como despreciable
y que además los vuelos pueden variar en tiempo debido a distintos factores, como pueden ser climáticos. 
Los precios han sido inventados completamente y no tienen ninguna relación con la realidad. El curso no
se hace responsable por las recomendaciones que pueda hacer alguno de los programas implementados. 

## Implementación

El trabajo puede realizarse en lenguaje a elección, siendo aceptados Python y C, y cualquier otro a ser discutido con el corrector asignado.

El trabajo consiste de 3 partes:
1. El TDA Grafo, con sus primitivas. 
1. Una biblioteca de funciones de grafos, que permitan hacer distintas operaciones sobre un grafo de aeropuertos del mundo, sin importar cuál sea el aeropuerto ni ciudad al que pertence.
1. El programa `FlyCombi` que utilice tanto el TDA como la biblioteca para poder implementar todo 
lo requerido. 

El programa debe recibir por parámetro y cargar en memoria el set de datos (`$./flycombi 
aeropuertos.csv vuelos.csv`) y luego solicitar el ingreso de comandos por entrada estándar, 
del estilo comando 'parametro'. Notar que esto permite tener un archivo de instrucciones a ser 
ejecutadas (i.e. `$./flycombi aeropuertos.csv vuelos.csv < entrada.txt`).

De todas las funcionalidades, algunas son obligatorias, y las que lo son tienen más de una opción
para ser implementadas. Algunas consideraciones: 
1. Cada funcionalidad e implementación otorga distinta cantidad de puntos, basado en dificultad y
el interés del curso en que implementen dicha funcionalidad o implementación de la misma.
1. Se deben conseguir al menos 10 puntos para poder aprobar el TP 
1. En caso de obtener menos de 12 puntos, la nota máxima será 9. 
1. En caso de obtener 16 puntos o más, se otorgará un punto extra en la nota del trabajo práctico. 
1. El total de puntos entre todas las funcionalidades es 20. 

### Listar operaciones (obligatorio, sin puntos)

* Comando: `listar_operaciones`.
* Parámetros: ninguno.
* Utilidad: Dado que no todas las funcionalidades o implementaciones son obligatorias, debe 
existir un comando que nos permita saber cuáles son las funcionalidades disponibles. Debe 
imprimirse una línea por cada **comando** que esté implementado.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(1)$$.
* Ejemplo:
Entrada:
	```
	listar_operaciones
	```
Salida:
	```
	camino_mas
	camino_escalas
	centralidad
	nueva_aerolinea
	vacaciones
	```

### Caminos mínimos (obligatorio implementar al menos 1)

#### Camino más barato y camino más rápido $$(\star)$$

* Comando: `camino_mas`
* Parámetros: `barato` ó `rapido`, `origen` y `destino`. Origen y destino son ciudades. 
Tener en cuenta que existen más de un aeropuerto por ciudad. 
* Utilidad: nos imprime una lista con los **aeropuertos** con los cuales vamos de la **ciudad**
`origen` a la **ciudad** `destino` de la forma más rápida o más barata, según corresponda. 
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F \log(A))$$, siendo $$A$$ la cantidad
de aeropuertos, y $$F$$ la cantidad de conexiones entre aeropuertos.
* Ejemplo: 
Entrada:
	```
	camino_mas rapido "Buenos Aires" "Berlin"
	```
Salida:
	```
	```

#### Camino con menor cantidad de escalas $$(\star)$$

* Comando: `camino_escalas`
* Parámetros: `origen` y `destino`. 
* Utilidad: nos imprime una lista con los **aeropuertos** con los cuales vamos de la **ciudad**
`origen` a la **ciudad** `destino` con la menor cantidad de escalas.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A + F)$$, siendo $$A$$ la cantidad
de aeropuertos, y $$F$$ la cantidad de conexiones entre aeropuertos.
* Ejemplos:
Entrada:
	```
	camino_escalas "Buenos Aires" "Berlin"
	```
Salida:
	```
	``` 

### Aeropuertos más importantes (obligatorio implementar al menos uno)

Utlizaremos alguno (o algunos) de estos comandos para poder obtener cuáles son los aeropuertos
más importantes. Esto lo podemos hacer obteniendo cuáles son los aeropuertos más centrales,
o bien usando un algoritmo como el de PageRank. 

Dejamos un apunte para la explicación de qué es y cómo se calcula el [Betweeness Centrality](/algo2/material/betweeness_centrality) y otro sobre [PageRank](/algo2/material/pagerank).

#### Betweeness Centrality $$(\star\star\star)$$

* Comando: `centralidad`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo, de mayor importancia a 
menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A \times F\log(A))$$.
* Ejemplo: 


#### Betweeness Centrality aproximada ($$\star$$)

* Comando: `centralidad`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo de forma aproximada, 
de mayor importancia a menor importancia.
* Complejidad: Revisar orden con Random Walks.

#### Pagerank $$(\star\star)$$

* Comando: `pagerank`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo según el algoritmo de
pagerank, de mayor importancia a menor importancia.
* Complejidad: Revisar complejidad de pagerank(!!).

### Optimización de rutas para nueva aerolínea $$(\star\star)$$

* Comando: `nueva_aerolinea`
* Parámetros: ninguno
* Utilidad: devolver una lista de las rutas que permitan implementar una nueva aerolínea tal que se
pueda comunicar a todo el mundo con dicha aerolínea, pero que el costo total de la licitación de las 
rutas aéreas sea mínima. Se considera que el costo de las rutas es proporcional al costo de los pasajes,
por lo que se puede trabajar directamente con dicho costo.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F\log(A))$$
* Ejemplo:

### Recorrer el mundo, de forma óptima $$(\star\star)$$

* Comando: `recorrer_mundo`
* Parámetros: ninguno
* Utilidad: nos devuelve una lista en orden de cómo debemos movernos por el mundo para visitar todas las
**ciudades** del mundo, recorriendo la menor distancia posible.
* Complejidad: que demore lo que deba demorar para obtener el resultado óptimo.
* Ejemplo:


### Recorrer el mundo, de forma aproximada $$(\star)$$
* Comando: `recorrer_mundo_aproximado`
* Parámetros: ninguno
* Utilidad: nos devuelve una lista en orden de cómo debemos movernos por el mundo para visitar todas las
**ciudades** del mundo, recorriendo aproximadamente la menor distancia posible.
* Complejidad: idealmente, que sea un algoritmo cuanto mucho cuadrático.
* Ejemplo:

### Viaje de N lugares $$(\star\star\star)$$
* Comando: `vacaciones`
* Parámetros: `origen`, y `n`. 
* Utilidad: Obtener algún recorrido que comience en `origen` y que termine en `origen` también, de largo `n` (sin contar la última vuelta al `origen`). No es necesario que se trate de ciudades diferentes.
* Complejidad: El algoritmo debe ejecutar en $$\mathcal{O}(F \times A)$$.
* Ejemplo:

### Itinerario cultural $$(\star\star)$$

* Comando: `itinerario`
* Parámetros: `ruta`, la ruta el archivo del itinerario. 
* Utilidad: El archivo de `ruta` tiene el formato: 
	```
	ciudad_1,ciudad_2,ciudad_3, ...,ciudadN
	ciudad_i,ciudad_j
	```
	La primera línea indica las ciudades que se desean visitar. Las siguientes indican que la 
	`ciudad_i` debe visitarse **si o si** antes que la `ciudad_j`. 
	Se debe: 
		1. Imprimir el orden en el que deben visitarse dichas ciudades. 
		1. Imprimir el camino mínimo en distancia o escalas (según lo que se haya
		implementado en ese caso) a realizar.
* Complejidad: El cálculo de la obtención del itinerario debe realizarse en $$\mathcal{O}(C + R)$$,
siendo $$C$$ la cantidad de ciudades a visitar, y $$R$$ la cantidad de restricciones impuestas. Luego, 
el cálculo de los caminos debe realizarse en $$\mathcal{O}\left(C\times F \log (A)\right)$$ o bien $$\mathcal{O}\left(C\times (A + F)\right)$$, dependiendo de si se trata de un caso u otro.
* Ejemplo:


### Obtener estadísticas $$(\star)$$
* Comando: `estadisticas`
* Parámetros: ninguno. 
* Utilidad: nos imprime las siguiente estadísticas: 
	* Cantidad de Aeropuertos
	* Cantidad de Vuelos posibles
	* Densidad? 
	* Aeropuerto con mayor cantidad de Vuelos
	* Alguna cosa más
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F + A)$$.
* Ejemplo: 

### Exportar a archivo KML $$(\star)$$

* Comando: `exportar_kml`. 
* Parámetros: `archivo`. 
* Utilidad: exporta el archivo KML con la ruta del último comando ejecutado (que incluya algún camino,
o rutas áereas). Esto aplica para todos los comandos salvo el de estadísticas, u obtención de los
aeropuertos más centrales.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F + A)$$.
* Ejemplo: Contamos con un [apunte sobre cómo crear, usar y visualizar archivos KML](/algo2/material/kml).

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- el código del TDA Grafo programado, y cualquier otro TDA que fuere necesario.
- el código de la solución del TP.

La entrega se realiza:

1. en forma digital a través del [sistema de entregas]({{site.entregas}}),
con todos los archivos mencionados en un único archivo ZIP.
2. en papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, informe ni carátula**. 

