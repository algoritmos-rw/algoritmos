---
layout: page
title: "TP3 – Grafos y la red de delicuencia"
permalink: '/tps/2019_1/tp3'
math: true
---

Trabajo Práctico 3
==================

{:.no_toc}

El Trabajo Práctico número 3 es de elaboración grupal, y tiene fecha de entrega
para el **viernes 28 de junio**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}

## Introducción

Luego de una ardua investigación por parte del FBI sobre una red de delicuentes, lograron encontrar 
una serie de mensajes enviados que los pueden llegar a comprometer. Lograron obtener los datos de 
más de 420.000 mensajes enviados por distintos medios: algunos son mensajes de texto, otros llamadas 
telefónicas, otros mensajitos por diversas redes sociales, mails, etc... Todos estos conectan a 260.000 
sospechosos a nivel mundial. El problema que ahora enfrentan es que no saben bien cómo trabajar con 
estos datos, por lo que le pidieron a alumnes de la FIUBA si pueden ayudar con esta tarea.

## Análisis de la situación

Los agentes del FBI se contactaron pidieron que se implementen las siguientes funcionalidades (o 
_features_):
1. Tienen a algunos de los delicuentes menores bien vigilados, y saben que se van a contactar con los 
demás. Eventualmente, si siguen el rastro pueden acabar encontrando y atrapando a algún _pez gordo_ de 
la lista de más buscados del mundo. Por esto, quieren poder obtener la mínima cantidad de seguimientos 
de personas que debe realizar un agente para dar con dicho _pez gordo_. Por ejemplo, ese tal 
_Toni, el Gordo_ es un delicuente muy buscado en una ciudad de Estados Unidos. 
1. Con tantos datos obtenidos, no tienen forma de definir cuáles son los delicuentes más importantes, 
para saber contra quienes conviene apuntar en esta operación. 
1. En función de lo anterior, les intersa poder tener una lista de cuales pueden ser esos delicuentes.
El problema es que son tantos, que saben que un algoritmo exacto puede tomar demasiado tiempo en calcular
esto, y temen que los delicuentes se enteren que el FBI ha obtenido todos estos datos, y escapen. 
Por lo tanto, aceptan una buena aproximación. 
1. Otra cosa que desean es, dado una lista de delicuentes a los que están siguiendo en estos momentos, 
determinar cuál es el mínimo esfuerzo para encontrar a alguno de los delicuentes más importantes.
1. Algo más que les permitiría entender como está conformada esta red de delicuentes sería poder determinar 
comunidades dentro de esta red.
1. Además de esto, cuentan con agentes infiltrados. Les interesa saber, si alguno de estos agentes comienza 
una noticia/rumor, hasta dónde puede llegar!
1. En conjunto con lo anterior, les interesa poder saber si existe algún camino de un determinado largo que 
empiece en un delicuente en particular (que en realidad será un agente encubierto), y que termine en dicho 
agente otra vez.
1. Les interesaría poder obtener los conjuntos de delicuentes entre los cuales todos se conectan con todos. 
Pueden ser más de uno estos conjuntos. 

## Datos disponibles

Se cuenta con un [set de datos](mensajes.zip)<sup>1</sup> de los 
mensajes, comunicaciones, encuentros, etc... entre los mencionados delicuentes (y agentes encubiertos). 
Por motivos tanto legales como de seguridad para les alumnes, solo se han dejado los números de 
identificación de dichos delicuentes, sin nungún dato personal.
El formato del archivo es un tsv (los campos se separan por tabuladores): 
```
id_vertice1	id_vertice2
id_vertice1	id_vertice3
...
id_vertice2	id_vertice1
id_vertice2	id_vertice3
...
id_vertice3	id_vertice5
```

Adicionalmente, se cuenta con el siguiente [set mínimo de pruebas inventado](minimo.zip), por lo que no 
representa un escenario real donde valga la pena realizar todas las operaciones pedidas, pero puede servir 
de prueba, y se utilizará este set de datos para los ejemplos. 

<sup>1</sup>El set de datos corresponde a un set de Emails enviados entre investigadores de la Unión 
Europea, obtenidos por la Universidad de Stanford.
[Fuente real aquí](https://snap.stanford.edu/data/email-EuAll.html).

### Aclaraciones

* Que un delicuente se comunique con otro no implica que también suceda la recíproca.
* Se ha visto también que hay delicuentes que se han enviado mensajes **a sí mismos**. Tener esto en cuenta 
a la hora de procesar los datos. 
* Aunque un delicuente se comunique 1, 2 o _n_ veces, sólo aparece una vez esa conexión en el archivo (que 
quiere decir que se hace esa comunicación _al menos una vez_). 

## Implementación

El trabajo puede realizarse en lenguaje a elección, siendo aceptados Python y C, y cualquier otro a ser 
discutido con le correctore asignado.

El trabajo consiste de 3 partes:
1. El TDA Grafo, con sus primitivas. 
1. Una biblioteca de funciones de grafos, que permitan hacer distintas operaciones sobre un grafo que 
luego se utilicen particularmente para el caso de la red de delicuentes.
1. El programa `AlgoPoli` que utilice tanto el TDA como la biblioteca para poder implementar todo 
lo requerido. 

El programa debe recibir por parámetro y cargar en memoria el set de datos (`$ ./algopoli 
mensajes.tsv`) y luego solicitar el ingreso de comandos por entrada estándar, 
del estilo `<comando> 'parametro'`. Notar que esto permite tener un archivo de instrucciones a ser 
ejecutadas (i.e. `$ ./algopoli mensajes.tsv < entrada.txt`).

A continuación, se explica cada comando. 

### Mínimos Seguimientos

* Comando: `min_seguimientos` ANALIZAR SI VOLVEMOS PESADO AL GRAFO (inventamos tiempo de envio de mensaje)
* Parámetros: `origen` y `destino`. 
* Utilidad: nos imprime una lista con los **delicuentes** (código) con los cuales vamos del
**delicuente** `origen` al **delicuente** `destino` de la forma más rápida.
* Ejemplo: 
Entrada:
	```
	min_seguimientos PONER
	min_seguimientos PONER
	```
Salida:
	```
	SALIDA
	```

### Delicuentes más importantes

Usualmente nos gustaría determinar cuáles son los vértices en un grafo en función de su
centralidad exacta. Teniendo en cuenta que se cuenta con demasiados delicuentes, el cálculo 
exacto de la centralidad puede consumir una cantidad excesiva de tiempo. 
Por lo tanto, se pide realizar una aproximación para determinar los delicuentes más importantes. 
Las formas posibles son:
 * [Betweeness Centrality, aproximado](/algo2/material/centralidad).
 * [PageRank](/algo2/material/pagerank).

Por lo tanto, el comando pedido debe ser: 
* Comando: `mas_imp`.
* Parámetros: `cant`. 
* Utildad: Imprime, de mayor a menor, los `cant` delicuentes más importantes.


### Persecución rápida

* Comando: `persecucion`.
* Parámetros: `delicuente1,delincuente2,...,delicuenteN` y `K`.
* Utilidad: Dado cada uno de los delicuentes pasados, obtener cual es el camino más corto para llegar desde
alguno de los delicuentes pasados por parámetros, a alguno de los `K` delicuentes más importantes. 
* Ejemplo:
Entrada
```
```
Salida:
```
```

### Comunidades

Para implementar esto, utilizaremos el algoritmo de [Label Propagation](/algo2/material/label_propagation) 
para detectar comunidades.

* Comando: `comunidades`. 
* Parámetros: `n`.
* Utilidad: Imprime un listado de comunidades de al menos `n` integrantes. 
* Ejemplo:
Entrada:
```
```
Salida:
```
```

### Divulgación de rumor

* Comando: `divulgar`.
* Parámetros: `delicuente`. 
* Utilidad: Imprime una lista con todos los delicuentes a los cuales les termina llegando un rumor que
comienza en el delicuente pasado por parámetro, teniendo en cuenta que _todos_ los delicuentes transmitirán
el rumor a sus allegados. 
* Ejemplo:
Entrada
```
```
Salida:
```
```


### Ciclo de largo n

* Comando: `divulgar_ciclo`
* Parámetros: `delicuente` y `n`. 
* Utilidad: Permite encontrar un camino que empiece y termine en el delicuente pasado por parámetro, de largo `n`. 
* Ejemplo: 
Entrada:
```
```
Salida:
```
```

### Componentes Fuertemente Conexas

Se debe leer el apunte sobre [componentes fuertemente conexas](/algo2/material/cfc).

* Comando: `cfc`
* Parámetros: ninguno. 
* Utilidad: Imprime cada conjunto de vértices entre los cuales todos están conectados con todos.
* Ejemplo:
Entrada:
```
```
Salida:
```
```
