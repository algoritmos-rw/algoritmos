---
math: true
title: "TP3 – Grafos y agencias de viaje"
---

{% assign tp = site.data.trabajos.TP3 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

Trabajo Práctico 3
==================
{:.no_toc}

El Trabajo Práctico número 3 es de elaboración grupal, y tiene fecha de entrega
para el **{{fecha}}**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}


## Introducción

En medio del revuelo producido por la inminente **Copa Mundial de Tejo de Esquí** que está por comenzar
en Qatar, una reconocida agencia de viajes tiene dos preocupaciones:

1. ¿Cómo deberá ser la vestimenta oficial de los participantes?
1. ¿Cómo aprovechar el mundial para ofrecer distintos paquetes de viajes?

Dado que la primer cuestión escapa un poco de su control, decidieron atacar la segunda. Para esto,
realizaron encuestas por distintas redes sociales (por ejemplo, AlgoGram) para saber cuáles serían los tipos de viajes que
más les gustaría a la gente.

Conoceremos a distintos personajes que nos ayudarán a entender qué nos puede llegar a ayudar:

* Sergio: es un fanático del esquí. Ya ha declarado que "ama más a Moshi (la estrella del equipo) que
a su madre". Quiere seguir a la selección de su país por todas las sedes a las que vaya. No le interesa
conocer nada más, salvo lo que sea estrictamente necesario para hacer un camino más corto, porque no
quiere perder ni un segundo de poder estar cerca del equipo.
* Claudia: cree que Paulo de Rodri sólo va al mundial por ser amigo de Moshi. 
Pero cuando empiecen las carreras, lo único que importa es que todos tiren para el mismo lado
(que bueno... es el único lado al que se pueden tirar). A ella además le interesa
conocer todas las sedes del mundial. Sabe que todas las ciudades están conectadas con todas las demás,
y quiere poder conocer todas y volver a la inicial (de dónde puede volver en avión) en la menor cantidad
de tiempo posible (tiene vacaciones limitadas, así que quiere reducir a lo mínimo el tiempo perdido en
viajes).
* Roberto: dado que no confía en que la selección tenga buenos resultados en el mundial desde que tuvo que
jugarse la clasificación con el seleccionado de República Dominicana, cree que lo mejor
es aprovechar el viaje para conocer el lugar.  Si bien su principal objetivo es ver partidos de la selección,
también tiene una particular afición por la historia, y más si se trata de la de Qatar. Por eso, quiere
aprovechar y visitar varias ciudades, pero no quiere hacerlo en cualquier orden. Quiere conocer ciertas
ciudades antes que otras, porque eso le ayudará a entender mejor los tours y visitas a museos, según un
artículo que vio en Trip Advisor.
* Lorena: no le gusta mucho andar por lugares desconocidos, por lo que prefiere conocer la menor cantidad
de rutas posibles que la conecten a todas las sedes, pero que al mismo tiempo impliquen el menor costo
posible. No le molesta recorrer varias veces la misma ruta, si fuera necesario.

## Análisis de la situación

La agencia ha tomado nota de lo que los distintos personajes requieren, por lo que han decidio implementar
un programa que, partiendo de un archivo inicial que contenga la información de todas las sedes del mundial, y
la distancia a la que se encuentra una de otra, podamos resolver todas sus inquietudes.

El programa debe permitir:

1. Obtener el camino mínimo desde y hacia distintas sedes del mundial (Sergio dijo que compraría pasajes para
toda la familia, inclusive para su mamá). También, exportar algún tipo de archivo que permita visualizar
el recorrido a hacer.
1. Obtener un recorrido que minimice el costo de todos los viajes entre todas las sedes, pasando una vez, y solo
una vez por cada sede, como pide Claudia. Como se explica más abajo, esta tarea puede demandar mucho tiempo, por lo que se puede optar por una aproximación. 
1. Obtener un itinerario de viaje para optimizar la experiencia del mismo (como quiere Roberto), donde no nos
importe la distancia entre sedes.
1. Obtener un Árbol de Tendido Mínimo para calcular la ruta deseada para Lorena.

### Problema del viajante

El segundo punto hace alusión a un problema muy conocido en computación, denominado _El problema del viajante_,
o TSP por sus siglas en inglés. Este pide que, teniendo un Grafo no dirigido, pesado y completo (en caso de no ser completo, se puede completar con aristas de peso _infinito_),
y un vértice inicial obtener un recorrido sobre el grafo tal que:
1. Minimice la suma de los pesos de las aristas por los que se transita.
1. Pase por todos los vértices, una vez y solo una vez.
1. Finalice volviendo al punto de origen.

Dicho problema es _muy difícil_ de resolver, en el sentido del orden temporal. Es un problema en el que, para
obtener la solución exacta, no distaremos demasiado de haber probado todas las soluciones posibles hasta encontrar
una que cumpla las tres restricciones, siendo que las dos últimas permiten recortar el árbol de posibilidades,
pero la primera nos implica necesariamente ver más de una opción posible.

Dado esto, simplemente se pedirá que piensen e implementen una solución aproximada que les parezca razonable. Mientras no sea completamente aleatoria, debería funcionar. Las pruebas del curso tendrán en cuenta esto, aceptando un margen respecto a la solución óptima en cada caso. 

## Implementación

El trabajo puede realizarse en lenguaje a elección, siendo aceptados Go, Python y C, y cualquier otro a ser discutido con el corrector asignado.

El trabajo consiste de tres partes:
* El TDA Grafo, con sus primitivas.
* Una biblioteca de funciones de grafos, que permitan hacer las distintas operaciones sobre un grafo de las características del que se va a utilizar para el TP.
* La interfaz del programa `vamosmoshi` que utilice tanto el TDA como la biblioteca para poder implementar todo
lo requerido.

Es importante notar que el TDA Grafo debe ser agnótico al TP completamente, la biblioteca de funciones debe implementar las funcionalidades específicas del TP, pero no deben hacer referencia a este (es decir, si quisiéramos utilizar dicha funcionalidad para otro TP, deberíamos poder). La interaz, en cambio, estaría completamente acoplada al TP. 

El programa a realizar debe recibir por parámetro y cargar en memoria el set de datos (`$ ./vamosmoshi
ciudades.csv`) y luego solicitar el ingreso de comandos por entrada estándar, del estilo
`comando 'parametro'`.

El archivo contará con el siguiente formato:
```
# Cantidad de ciudades (n)
Ciudad1,lat1,long1
Ciudad1,lat1,long1
...
Ciudad_n,lat_n,long_n
# Cantidad de conexiones
Ciudad_i,Ciudad_j,tiempo
...
```

Es necesario tener en cuenta que los tiempos encontrados corresponden a distintos medios de transporte. Debido
a que la agencia de viajes decidió hacer este negocio casi en el comienzo del certamen, no todos los medios
de transporte estaban habilitados a la hora de buscar los datos, por lo que se obtuvo lo mejor a nuestra
disposición. [Se puede encontrar aquí un archivo completo con las sedes](https://drive.google.com/file/d/1427w60dvNAg3UdVz5CsgRvafCjA34EkE/view?usp=sharing).

### Comandos

Los comandos a implementar serán:
* `ir desde, hasta, archivo`: nos devolverá el camino mínimo entre la ciudad `desde` y la ciudad `hasta`. Además guardará un archivo KML con el resultado del camino. 

	Por ejemplo:
	```
	ir Doha, Uum bab, mapa.kml
	```
	Nos debería imprimir:
	```
	Moscu -> Samara -> Saransk   // CORREGIR
	Tiempo total: 8
	```

* `viaje origen, archivo`: nos devuelve un listado con el orden de las ciudades a
visitar para ver todas las ciudades una vez y volver al origen. Además guardará un archivo KML con el resultado del camino. 
	
	Por ejemplo:
	```
	viaje Doha, resultado.kml
	```
	Nos puede imprimir:
	```
	Sochi -> Volgogrado -> Kazan -> Nizhni Novgorod -> Ekaterinburgo -> Kaliningrado -> San Petesburgo -> Saransk -> Samara -> Moscu -> Rostov del Don -> Sochi
	Costo total: 43 // CORREGIR
	```

* `itinerario recomendaciones.csv, archivo`: el archivo `recomendaciones.csv` es un archivo con formato:
		```
		ciudad_1,ciudad_2
		...
		```
	Donde indica que la `ciudad_1` debe visitarse antes que la `ciudad_2`.
	Notar que todas las ciudades a tener en cuenta son
	las del mapa original, pero podría tranquilamente suceder que alguna ciudad no aparezca en el archivo
	`recomendaciones.csv `, e igualmente es necesario visitarla.
	Luego de cargar el archivo, se deberá devolver un itinerario válido para visitar las ciudades,
	cumpliendo con las recomendaciones. El formato en el cual se deben mostrar es igual al de
	`ir` y `viajero`. Considerar que los caminos deben ser válidos. Es decir, si primero vamos a ciudad A y luego decimos que vamos a ciudad B, es que hay camino entre A y B. Por simplificación, incluso si una ciudad C debe visitarse antes que B, si vamos de A hacia C, y debemos pasar por B, esto lo consideraremos correcto ya que por B sólo "estamos de paso". Dejamos [un ejemplo de un posible archivo de recomendaciones](https://drive.google.com/file/d/1fLeb0g6DGlNzh3XwWD7jPYPVbIpcQ1la/view?usp=sharing).
* `reducir_caminos destino.csv`: nos crea un archivo csv con un formáto idéntico al archivo de ciudades
inicial, pero únicamente con los caminos estrictamente necesarios. Al finalizar, debe imprimir por salida
estándar la suma de los pesos de las aristas del árbol, en formato `"Peso total: ..."`. Para el archivo de ejemplo,
el peso del árbol de tendido mínimo debe ser XX.

Como se indica antes, salvo para el comando `reducir_caminos`, será necesario además exportar un archivo KML a la ruta indicada por
parámetro al invocarse el programa. [Se incluye un ejemplo para el camino mínimo entre Moscu y Sochi](https://drive.google.com/file/d/1u6jkaLcMSHarPgKDwmzDqkfVNcUpvYN2/view?usp=sharing).

### Archivos KML

Contamos con un [apunte sobre cómo crear, usar y visualizar archivos KML](/algo2/material/apuntes/kml).

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- el código del TDA Grafo programado, y cualquier otro TDA que fuere necesario.
- el código de la solución del TP.

La entrega se realiza en forma digital a través del [sistema de entregas]({{site.entregas}}),
con todos los archivos mencionados en un único archivo ZIP.

