---
layout: page
title: "TP3 – Grafos y agencias de viaje"
permalink: '/tps/2018_1/tp3'
math: true
---

Trabajo Práctico 3
================
{:.no_toc}

El Trabajo Práctico número 3 es de elaboración grupal, y tiene fecha de entrega
para el **viernes XX de junio**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}


## Introducción

En medio del revuelo producido por el inminente mundial de tejo de playa que está por comenzar en Rusia, 
una reconocida agencia de viajes tiene dos preocupaciones:

1. Cómo deberá ser la vestimenta oficial de los participantes?
1. Cómo aprovechar el mundial para ofrecer distintos paquetes de viajes

Dado que la primer cuestión escapa un poco de su control, decidieron atacar la segunda. Para esto, 
realizaron encuestas por distintas redes sociales para saber cuáles serían los tipos de viajes que más
les gustaría a la gente. 

Conoceremos a distintos personajes que nos ayudarán a entender qué nos puede llegar a ayudar: 

* Sergio: es un fanático del tejo. Ya ha declarado que "ama más a Moshi (la estrella del equipo) que a su madre". 
Quiere seguir a la selección de su país por todas las sedes a las que vaya. No le interesa conocer nada más, salvo 
lo que sea estrictamente necesario para hacer un camino más corto, porque no quiere perder ni un segundo de poder 
estar cerca del equipo. 
* Claudia: cree que _el Semilla_ Ibrahim es un toque mufa, y va al mundial sólo por ser amigo de Moshi. Pero cuando 
empiece a tirarse la bocha, lo único que importa es que todos tiren para el mismo lado (que bueno... es el único lado 
al que se pueden tirar las bochas de tejo). A ella además le interesa conocer todas las sedes del mundial. Sabe que todas 
las ciudades están conectadas con todas las demás, y quiere poder conocer todas y volver a la inicial (de dónde puede 
volver en avión) en la menor cantidad de tiempo posible (tiene vacaciones limitadas, así que quiere reducir a lo mínimo el
tiempo perdido en viajes).
* Roberto: dado que no confía en que la selección tenga buenos resultados en el mundial, desde que tuvo que jugarse la 
clasificación con el seleccionado de Eslovaquia (que ni siquiera tiene playas), cree que lo mejor es aprovechar el viaje para 
conocer el lugar.  Si bien su principal objetivo es ver partidos de la selección, también tiene una particular afición por la 
historia, y más si se trata de la de Rusia. Por eso, quiere aprovechar y visitar varias ciudades, pero no quiere hacerlo
en cualquier orden. Quiere conocer ciertas ciudades antes que otras, porque eso le ayudará a entender mejor los tours y 
visitas a museos, según un artículo que vio en Trip Advisor. 
* Lorena: no le gusta andar mucho andar por lugares desconocidos, por lo que prefiere conocer la menor cantidad de rutas posibles, pero que al mismo tiempo impliquen el menor costo posible. No le molesta recorrer varias veces la misma ruta, 
si fuera necesario. 

## Análisis de la situación

La agencia ha tomado nota de lo que los distintos personajes requieren, por lo que han decidio implementar un programa
que, partiendo de un archivo inicial que contenga la información de todas las sedes del mundial, y la distancia a la que
se encuentra una de otra, podamos resolver todas sus inquietudes. 

El programa debe permitir: 

1. Obtener el camino mínimo desde y hacia distintas sedes del mundial (Sergio dijo que compraría pasajes para toda la 
familia, inclusive para su mamá). También, exportar un archivo KML para que pueda ir viendo en un mapa como va a ser su 
recorrido.
1. Obtener un recorrido que minimice el costo de todos los viajes entre todas las sedes, pasando una vez, y solo una vez por 
cada sede, como pide Claudia. 
1. Obtener un itinerario de viaje para optimizar la experiencia del viaje, donde no nos importe la distancia entre sedes. 
1. Obtener un Árbol de Tendido Mínimo para tener la ruta deseada para Lorena. 

### Problema del viajante

El segundo punto hace alusión a un problema muy conocido en computación, denominado _El problema del viajante_, o TSP por sus 
siglas en inglés. Este pide que, teniendo un Grafo no dirigido, pesado y completo, obtener un recorrido sobre este que: 
1. Minimice la suma de los pesos de las aristas por los que se transita. 
1. Pase por todos los vértices, una vez y solo una vez. 
1. Finalice volviendo al punto de origen. 

Dicho problema es _muy difícil_ de resolver, en el sentido del orden temporal. Es un problema en el que, para obtener la 
solución exacta, no distaremos demasiado de haber probado todas las soluciones posibles hasta encontrar una que cumpla las 
tres restricciones, siendo que las dos últimas permiten recortar el árbol de posibilidades, pero la tercera nos implica 
necesariamente ver más de una opción posible.

Dado esto, es necesario implementar: 
1. Una solución exacta, que si bien demore tiempo, permita obtener la mejor solución de todas. 
1. Una solución aproximada, que permita resolver el problema de la mejor forma posible, pero rápidamente.

La primera deberá implementarse con un algoritmo de Backtracking, mientras la segunda deberá ser con un algoritmo Greedy. 

## Implementación

El trabajo consiste de tres partes: 
* El TDA Grafo, con sus primitivas. 
* Una biblioteca de funciones de grafos, que permitan hacer distintas operaciones sobre un grafo de ciudades de algún 
país, sin importar cuál sea el país ni cuáles las ciudades. 
* El programa 'Traeme la copa Moshi' que utilice tanto el TDA como la biblioteca para poder implementar todo lo requerido, 
poniendo foco en Rusia.

El programa a realizar debe recibir por parámetro y cargar en memoria el set de datos (`$ ./traemelaco ciudades.csv) y luego 
solicitar el ingreso de comandos por entrada estándar, del estilo `comando 'parametro'`. Notar que esto permite tener un 
archivo de instrucciones a ser ejecutadas (`cat comandos.txt | ./traemelaco ciudades.csv`).

El archivo contará con el siguiente formato: 
```
#Cantidad de ciudades (n)
Ciudad1 lat1 long1
Ciudad1 lat1 long1
...
Ciudad_n lat_n long_n
```

Dado que para este problema en particular consideraremos que todas las ciudades se encuentran conectadas directamente con
todas las demás, no es necesario incluir las aristas en dicho archivo. Para conocer la distancia que hay entre dos ciudades
(el peso de la arista), se podrá utilizar la fórmula de Haversine: 

$$ distancia = 2 \times R \ times \arcsin\left( \sqrt{ \sin^2\left( \frac{lat_2 - lat_1}{2} \right) + \cos(lat_1) \cos(lat_2) \sqrt{ \sin^2\left( \frac{long_2 - long_1}{2} \right)} \right) $$

**Importante**: es necesario pasar las longitudes y latitudes (originalmente en coordenadas polares) a radianes antes de aplicar la fórmula. 

(Seguir, poniendo comandos, funciones de la biblioteca, etc...)