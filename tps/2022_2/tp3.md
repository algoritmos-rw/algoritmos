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

En medio del revuelo producido por la inminente **Copa Mundial de Esquí** que está por comenzar
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
* Claudia: cree que Paulo de Rodrick sólo va al mundial por ser amigo de Moshi. 
Pero cuando empiecen las carreras, lo único que importa es que todos tiren para el mismo lado
(que bueno... es el único lado al que se pueden tirar). A ella además le interesa
conocer todas las sedes del mundial. Y no sólo eso, también le interesa recorrer **cada ruta** que conecte cada par de ciudades. 
No le importa volver varias veces a la misma ciudad pero, como es aficionada a la fotografía, decidió sacarle fotos a cada ruta 
que haya (además de a las ciudades). No le importa cuánto le tome. Total, ¿cuándo en su vida va a volver a viajar a Qatar?
* Adam: No confía en que su selección tenga buenos resultados en el mundial desde que tuvo que
jugarse la clasificación con el seleccionado de Suecia, y menos aún porque en el sorteo le salió que su selección
debe jugar contra la de Moshi. Sin muchas esperanzas, cree que lo mejor
es aprovechar el viaje para conocer el lugar. Si bien su principal objetivo es ver partidos de su selección,
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
1. Obtener un itinerario de viaje para optimizar la experiencia del mismo (como quiere Adam), donde no nos importe la distancia entre sedes.
1. Obtener un recorrido que recorra todas las rutas entre sedes, exactamente una vez. No utilizar más de una vez la misma ruta, para brindarle el mejor servicio a Claudia. Debido a que la mayoría de los clientes van a querer luego volverse a sus casas desde el lugar de inicio, este recorrido debe terminar donde comenzó.
1. Obtener un Árbol de Tendido Mínimo para calcular la ruta deseada para Lorena.

### Ciclo de Euler

El tercer punto hace referencia al problema que originó la existencia de los grafos: [el Camino de Euler, o camino de Königsberg](https://en.wikipedia.org/wiki/Eulerian_path). Literalmente se trata de un camino que recorre todas las aristas de un grafo exactamente una vez.
En el problema planteado es necesario terminar y comenzar en el mismo lugar, por lo que buscaremos un ciclo de Euler. 

Para resolver esto en tiempo lineal, vamos a implementar el algoritmo de Hierholzer, que [explicamos aquí](/algo2/material/apuntes/camino_euler). En caso que no exista un ciclo Euleriano, no se puede cumplir con lo pedido en la consigna (ver más abajo el error que debe mostrarse en ese caso). 


## Implementación

El trabajo puede realizarse en lenguaje a elección, siendo aceptados Go, Python y C, y cualquier otro a ser discutido con el corrector asignado.

El trabajo consiste de tres partes:
* El TDA Grafo, con sus primitivas.
* Una biblioteca de funciones de grafos, que permitan hacer las distintas operaciones sobre un grafo de las características del que se va a utilizar para el TP.
* La interfaz del programa `vamosmoshi` que utilice tanto el TDA como la biblioteca para poder implementar todo
lo requerido.

Es importante notar que el TDA Grafo debe ser agnótico al TP completamente, la biblioteca de funciones debe implementar las funcionalidades específicas del TP, pero no deben hacer referencia a este (es decir, si quisiéramos utilizar dicha funcionalidad para otro TP, deberíamos poder). La interaz, en cambio, estaría completamente acoplada al TP. 

El programa a realizar debe recibir por parámetro y cargar en memoria el set de datos (`$ ./vamosmoshi
ciudades.pj`) y luego solicitar el ingreso de comandos por entrada estándar, del estilo
`comando 'parametro'`.

El archivo contará con el siguiente formato (formato Pajek):
```
# Cantidad de ciudades (n)
Ciudad1,lat1,long1
Ciudad2,lat2,long2
...
Ciudad_n,lat_n,long_n
# Cantidad de conexiones
Ciudad_i,Ciudad_j,tiempo
...
```

Es necesario tener en cuenta que los tiempos encontrados corresponden a distintos medios de transporte. Debido
a que la agencia de viajes decidió hacer este negocio casi en el comienzo del certamen, no todos los medios
de transporte estaban habilitados a la hora de buscar los datos, por lo que se obtuvo lo mejor a nuestra
disposición. En [el sitio de descargas]({{site.skel}}) pueden encontrar un archivo completo con las sedes de este caso particular. 

Las pruebas del curso considerarán el mapa de este presente mundial de Esquí, el mapa [del último mundial de tejo de playa (Rusia 2018)](/algo2/tps/2018_1/tp3), así como un mapa generado al azar para un escenario de volumen. 

### Comandos

Los comandos a implementar serán:
* `ir desde, hasta, archivo`: nos devolverá el camino mínimo entre la ciudad `desde` y la ciudad `hasta`. Además guardará un archivo KML con el resultado del camino. Si no existe forma de conectar dichos lugares (o si alguno no existe), debe imprimirse `No se encontro recorrido`.

	Por ejemplo:
	```
	ir Doha, Uum Bab, mapa.kml
	```
	Nos debería imprimir:
	```
	Doha -> Rayan -> Zekreet -> Dukhan -> Uum Bab
	Tiempo total: 10
	```

* `itinerario recomendaciones.csv`: el archivo `recomendaciones.csv` es un archivo con formato:
		```
		ciudad_1,ciudad_2
		...
		```
	Donde indica que la `ciudad_1` debe visitarse antes que la `ciudad_2`.
	Notar que todas las ciudades a tener en cuenta son
	las del mapa original, pero podría tranquilamente suceder que alguna ciudad no aparezca en el archivo
	`recomendaciones.csv `, e igualmente es necesario visitarla. 
	Luego de cargar el archivo, se deberá devolver un orden válido para ir a las ciudades. No es necesario poner los caminos mínimos para luego ir desde cada par de puntos. Para eso se puede utilizar el comando anterior posteriormente. En caso que no se puedo resolver el problema con las restricciones dadas, imprimir `No se encontro recorrido`.
	Dejamos un ejemplo de un posible archivo de recomendaciones entre los archivos disponibles a descargar. En este caso, una posible salida será:
	```
	Al Ruwais -> Fuwayrit -> Al Wakrah -> Doha -> Dukhan -> Mesaleed -> Zekreet -> Rayan -> Uum Bab -> Jor
	```
* `viaje origen, archivo`: nos devuelve un listado con el orden de las ciudades a
visitar para ver todas las rutas una vez y volver al origen. Además guardará un archivo KML con el resultado del camino. En caso de no poderse resolver el problema, debe imprimir `No se encontro recorrido`
	
	Por ejemplo:
	```
	viaje Doha, resultado.kml
	```
	Nos puede imprimir:
	```
	Doha -> Rayan -> Jor -> Zekreet -> Mesaleed -> Rayan -> Zekreet -> Al Ruwais -> Jor -> Mesaleed -> Doha -> Al Wakrah -> Mesaleed -> Uum Bab -> Fuwayrit -> Al Ruwais -> Dukhan -> Fuwayrit -> Zekreet -> Dukhan -> Uum Bab -> Doha -> Fuwayrit -> Jor -> Doha
	Tiempo total: 172
	```

	Los resultados podrían ser otros, pero siempre tienen que aparecer la totalidad de aristas (y, por lo tanto, el tiempo total siempre debería ser el mismo)

* `reducir_caminos destino.pj`: nos crea un archivo pajek (formáto idéntico al archivo de ciudades
inicial, pero únicamente con los caminos estrictamente necesarios. Al finalizar, debe imprimir por salida
estándar la suma de los pesos de las aristas del árbol, en formato `"Peso total: ..."`. Para el archivo de ejemplo, el peso del árbol de tendido mínimo debe ser 26.

Como se indica antes, para los comandos `ir` y `viaje`, será necesario además exportar un archivo KML a la ruta indicada por
parámetro al invocarse el programa. Se incluye, entre los archivos disponibles a descargar, un ejemplo para el camino mínimo entre Doha y Uum bab.

### Archivos KML

Contamos con un [apunte sobre cómo crear, usar y visualizar archivos KML](/algo2/material/apuntes/kml).

## Entrega

Adicionalmente a los archivos propios del trabajo práctico debe agregarse un archivo `entrega.mk` que contenga la regla `vamosmoshi` para generar el ejecutable de dicho programa (sea compilando o los comandos que fueren necesarios). Por ejemplo, teniendo un TP elaborado en Python, podría ser:

``` makefile
vamosmoshi:
    cp vamosmoshi.py vamosmoshi
    chmod +x vamosmoshi
```

**Importante**: En caso de recibir un error `FileNotFoundError: [Errno 2] No such file or directory: './vamosmoshi': './vamosmoshi'`, tener en cuenta que para el caso de enviar código escrito en Python es necesario además indicar la ruta del intérprete. Esto puede hacerse agregando como primera línea del archivo principal (en el ejemplo, sería `vamosmoshi.py`) la línea: `#!/usr/bin/python3`.

Si el TP fuera realizado en Go, un posible ejemplo del archivo podría ser:

``` makefile
vamosmoshi:
    cd mi_implementacion_tp3; go build -o ../vamosmoshi
```

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- el código del TDA Grafo programado, y cualquier otro TDA que fuere necesario.
- el código de la solución del TP.

La entrega se realiza en forma digital a través del [sistema de entregas]({{site.entregas}}),
con todos los archivos mencionados en un único archivo ZIP.

