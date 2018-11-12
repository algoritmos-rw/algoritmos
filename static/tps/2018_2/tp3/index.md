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
para el **viernes 7 de diciembre**.

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

Aerolíneas de distintas partes del mundo, requieren distintos tipos de funcionalidades:
* Todas las aerolíneas quieren que los clientes puedan buscar el camino más rápido, 
el más barato, o el de menor cantidad de escalas, a gusto.
* Para poder entender dónde conviene invertir en mayor infraestructura, se quiere obtener 
cuáles son los aeropuertos más importantes, teniendo en cuenta en cuáles es más frecuente
terminar haciendo escalas para poder ir entre cualquier parte del mundo a otra. 
* Una nueva aerolínea (bAIRros Airlines, con sede principal en el aeropuerto de Lanús) 
quiere poder conectar absolutamente todo el mundo, pero quiere utilizar las rutas más baratas 
posibles para ello. Entre tantos datos que hay, no saben por dónde empezar!
* Algunas aerolíneas querrían poder agregar (en sus sofisticados sistemas de recomendación) la
posibilidad de ofrecer un viaje alrededor del mundo: poder visitar todo el mundo, con el menor 
costo o tiempo posible.
* Sobre lo anterior, algunas aerolíneas quieren que sea la mejor solución posible, sin excepciones.
Otras, entienden que la capacidad de cómputo de dicha solución puede llevar mucho tiempo para sus 
_no tan capaces_ servidores (comparten capacidad junto con el sistema SIU Guaraní de la FIUBA). 
Por ello, aceptarían una _buena solución_ que se calcule rápidamente. 
* Algunas aerolíneas querrían ofrecer un viaje que empiece desde la ciudad del cliente, y
haga un viaje por alguna cantidad de ciudades del mundo y vuelva luego a la ciudad origen 
(así pueden ofrecer descuentos para tentar a los clientes).
* Otras aerolíneas pidieron poder ofrecer un viaje cultural: que se pueda indicar qué ciudades se
quieren conocer, y además si hay alguna ciudad que deba visitarse antes que otra (para poder
disfrutar más del viaje). 
* Muchas de las aerolíneas quisieran poder exportar un mapa que nos permita visualizar las rutas de vuelo. 

## Datos disponibles

Se cuenta con los datos de los [aeropuertos de Estados Unidos](https://www.kaggle.com/usdot/flight-delays/version/1#airports.csv), así como de más de medio millón de [vuelos](https://www.kaggle.com/usdot/flight-delays/version/1#flights.csv) durante el año 2015. 

Una consultora uso un [innovador script](parser.py) para parsear dichos datos en los siguiente archivos: 
* El archivo [aeropuertos.csv](aeropuertos.csv) con el formato:
	```
	ciudad,codigo_aeropuerto,latitud,longitud
	```
* El archivo [vuelos.csv](vuelos.csv) con el formato: 
	```
	aeropuerto_i,aeropuerto_j,tiempo_promedio,precio,cant_vuelos_entre_aeropuertos
	```

### Aclaraciones

* Una ciudad puede tener **uno o más aeropuertos** asociados.
* El tiempo promedio es el promedio (redondeado) de todos los tiempos de los vuelos entre ese par de
ciudades.
* Los precios han sido inventados completamente (puede verse en el script generador) y no tienen 
ninguna relación con la realidad. El curso no se hace responsable por las recomendaciones que pueda 
hacer alguno de los programas implementados. 
* Sería de mayor interés tener los datos disponibles de todo el mundo, o de diversos países. De todas
formas, hay que considerar que se tratan de casi 6 millones de vuelos sólo considerando un país, en un
año. 
* Más allá de tener los datos de un país en especial, el programa debería funcionar para cualquier 
parte del mundo. 

## Implementación

El trabajo puede realizarse en lenguaje a elección, siendo aceptados Python y C, y cualquier otro a ser discutido con el corrector asignado.

El trabajo consiste de 3 partes:
1. El TDA Grafo, con sus primitivas. 
1. Una biblioteca de funciones de grafos, que permitan hacer distintas operaciones sobre un grafo de aeropuertos del mundo, sin importar cuál sea el aeropuerto ni país al que pertence.
1. El programa `FlyCombi` que utilice tanto el TDA como la biblioteca para poder implementar todo 
lo requerido. 

El programa debe recibir por parámetro y cargar en memoria el set de datos (`~$./flycombi 
aeropuertos.csv vuelos.csv`) y luego solicitar el ingreso de comandos por entrada estándar, 
del estilo `<comando> 'parametro'`. Notar que esto permite tener un archivo de instrucciones a ser 
ejecutadas (i.e. `~$./flycombi aeropuertos.csv vuelos.csv < entrada.txt`).

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
* Parámetros: `barato` ó `rapido`, `origen` y `destino`. Origen y destino son **ciudades**.
* Utilidad: nos imprime una lista con los **aeropuertos** (código) con los cuales vamos de la 
**ciudad** `origen` a la **ciudad** `destino` de la forma más rápida o más barata, según corresponda. 
Tener en cuenta que tanto la ciudad `origen` como la `destino` pueden tener más de un aeropuerto, y 
nos interesa la mejor forma (rápida o barata) entre todas las combinaciones posibles.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F \log(A))$$, siendo $$A$$ la cantidad
de aeropuertos, y $$F$$ la cantidad de vuelos entre aeropuertos (sin contar frecuencia). 
Podemos considerar que la cantidad de aeropuertos que tenga cada ciudad es despreciable.
* Ejemplo: 
Entrada:
	```
	camino_mas rapido,San Diego,New York
	camino_mas barato,San Diego,New York
	```
Salida:
	```
	SAN -> JFK
	SAN -> DEN -> JFK
	```

#### Camino con menor cantidad de escalas $$(\star)$$

* Comando: `camino_escalas`
* Parámetros: `origen` y `destino`. 
* Utilidad: nos imprime una lista con los **aeropuertos** (código) con los cuales vamos de la 
**ciudad** `origen` a la **ciudad** `destino` con la menor cantidad de escalas. Tener en cuenta 
que tanto la ciudad `origen` como la `destino` pueden tener más de un aeropuerto, y 
nos interesa la mejor forma (en cantidad de escalas) entre todas las combinaciones posibles.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F + A)$$, siendo $$A$$ la cantidad
de aeropuertos, y $$F$$ la cantidad de vuelos entre aeropuertos (sin contar frecuencia). 
Podemos considerar que la cantidad de aeropuertos que tenga cada ciudad es despreciable.
* Ejemplos:
Entrada:
	```
	camino_escalas San Diego,New York
	```
Salida:
	```
	SAN -> JFK
	``` 

### Aeropuertos más importantes (obligatorio implementar al menos uno)

Utlizaremos alguno (o algunos) de estos comandos para poder obtener cuáles son los aeropuertos
más importantes. Esto lo podemos hacer obteniendo cuáles son los aeropuertos más centrales,
o bien usando un algoritmo como el de PageRank. Es necesario tener en cuenta además la frecuencia 
de vuelos: no es lo mismo un aeropuerto que se conecte contra todos con un vuelo al año, que uno que 
se conecte al 80% con muchos vuelos al año. ¡Cuantos más vuelos, mejor!

Dejamos un apunte para la explicación de qué es y cómo se calcula el 
[Betweeness Centrality](/algo2/material/centralidad) y otro sobre 
[PageRank](/algo2/material/pagerank).

#### Betweeness Centrality $$(\star\star\star)$$

* Comando: `centralidad`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo, 
de mayor importancia a menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A \times F\log(A))$$.
* Ejemplo: 
Entrada:
	```
	centralidad 3
	```
Salida:
	```
	SFO, TPA, MSN
	``` 


#### Betweeness Centrality aproximada ($$\star$$)

* Comando: `centralidad_aprox`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo de forma aproximada, 
de mayor importancia a menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A + F)$$.
* Ejemplo: 
Entrada:
	```
	centralidad_aprox 3
	```
Salida:
	```
	ATL, ORD, DFW
	``` 

#### Pagerank $$(\star\star)$$

* Comando: `pagerank`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo según el algoritmo de
pagerank, de mayor importancia a menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(K(A + F))$$, siendo $$K$$ la cantidad de
iteraciones a realizar para llegar a la convergencia (puede simplificarse a $$\mathcal{O}(A + F)$$).
Entrada:
	```
	pagerank 5
	```
Salida:
	```
	ATL, DFW, ORD, DEN, MSP
	``` 

### Optimización de rutas para nueva aerolínea $$(\star\star)$$

* Comando: `nueva_aerolinea`.
* Parámetros: `ruta`, ruta del archivo de salida.
* Utilidad: devolver una lista de las rutas que permitan implementar una nueva aerolínea tal que se
pueda comunicar a todo el mundo (por ahora, solo los Estados Unidos) con dicha aerolínea, pero que el 
costo total de la licitación de las rutas aéreas sea mínima. Se considera que el costo de las rutas es
proporcional al costo de los pasajes, por lo que se puede trabajar directamente con dicho costo. 
Se busca que la nueva aerolínea pueda llegar a todos los **aeropuertos** de alguna forma.
La salida de este comando debe ser un archivo con el mismo formato del archivo `vuelos.csv`, pero
únicamente con las rutas de vuelo a utilizar por ésta aerolínea.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(F\log(A))$$.
* Ejemplo:
Entrada:
	```
	nueva_aerolinea bAIRos.csv
	```
Salida (aparte del archivo creado):
	```
	OK
	``` 


### Recorrer el mundo, de forma óptima $$(\star\star\star)$$

* Comando: `recorrer_mundo`.
* Parámetros: ninguno.
* Utilidad: nos devuelve una lista en orden de cómo debemos movernos por el mundo para visitar todas
**las ciudades** del mundo (por ahora, Estados Unidos), demorando lo menos posible. Podemos volver 
a usar un aeropuerto ya usado, u otro de alguna ciudad ya visitada, si eso mejora el costo de nuestro
viaje.
* Complejidad: que demore lo que deba demorar para obtener el resultado óptimo.
* Ejemplo:
Entrada:
	```
	recorrer_mundo
	```


### Recorrer el mundo, de forma aproximada $$(\star)$$
* Comando: `recorrer_mundo_aprox`
* Parámetros: ninguno
* Utilidad: nos devuelve una lista en orden de cómo debemos movernos por el mundo para visitar todas
las ciudades del mundo (por ahora, Estados Unidos), demorando aproximadamente lo menos posible.
* Complejidad: idealmente, que sea un algoritmo cuanto mucho cuadrático.
* Ejemplo:
Entrada:
	```
	recorrer_mundo_aprox
	```
Salida:
	```
	MCI -> BNA -> PNS -> ATL -> VPS -> DFW -> ROW -> ORD -> EAU -> BNA -> JAX -> ORD -> DAY -> DFW -> LFT -> DEN -> SAF -> LAX -> MSP -> CWA -> LAS -> BUR -> CVG -> RIC -> DEN -> GJT -> DEN -> FAT -> IND -> JFK -> HYA -> ATL -> SAV -> DEN -> COD -> SFO -> CEC -> DFW -> GRI -> MSP -> ANC -> ATL -> GNV -> IAD -> UST -> ORD -> MKG -> MSP -> BIS -> DEN -> HDN -> FLL -> MCO -> BQN -> DAL -> MEM -> OAK -> ORD -> ROA -> DTW -> SWF -> ATL -> TYS -> DTW -> ACY -> ORD -> EVV -> ORD -> LAN -> MIA -> DEN -> PUB -> CLT -> DEN -> HNL -> GUM -> ATL -> FAY -> MDW -> ORF -> DFW -> JAN -> DFW -> TYR -> DEN -> SMF -> DFW -> FSM -> SLC -> VEL -> ORD -> TVC -> SLC -> CNY -> SFO -> ACV -> SEA -> BLI -> DEN -> BOI -> BOS -> MVY -> ATL -> TRI -> DTW -> ABE -> STL -> RDU -> PHF -> SLC -> MFR -> DFW -> MFE -> DTW -> BGM -> DFW -> MEI -> DTW -> SYR -> ATL -> MYR -> PBG -> DAL -> ELP -> BNA -> MOB -> MSP -> IMT -> SLC -> SUN -> DAL -> AUS -> DEN -> DVL -> MSP -> RHI -> ORD -> CMI -> STL -> TTN -> ORD -> CMX -> DEN -> HYS -> DEN -> ASE -> ORD -> TOL -> MKE -> MDW -> BDL -> DFW -> JLN -> LAS -> LGB -> LAX -> SBA -> DLH -> DFW -> TXK -> STL -> CMH -> MSP -> BRD -> SEA -> KTN -> WRG -> MSP -> INL -> PHX -> YUM -> STL -> PHL -> SLC -> EKO -> ORD -> DBQ -> DCA -> DEN -> MTJ -> DAL -> SAT -> STL -> GRR -> DFW -> SJT -> DFW -> SGF -> LAX -> CLD -> LAS -> ONT -> ORD -> STC -> MDW -> PIT -> DFW -> MHK -> LNK -> SLC -> BTM -> BWI -> ATL -> TLH -> DEN -> RAP -> SLC -> TWF -> ATL -> ABY -> ATL -> STT -> DFW -> LRD -> ATL -> STX -> ATL -> DHN -> MSP -> ANC -> CDV -> DEN -> OTH -> DAL -> LBB -> MSP -> ANC -> OTZ -> DEN -> GEG -> DEN -> JMS -> IAH -> HOB -> SLC -> LWS -> DFW -> GRK -> BWI -> ISP -> DTW -> AVP -> DEN -> LAR -> OAK -> OGG -> DEN -> RKS -> MSP -> MOT -> ATL -> MYR -> IAG -> ATL -> SRQ -> MSP -> ANC -> AKN -> ATL -> GTR -> LAX -> ITO -> ORD -> SUX -> MSP -> FSD -> DFW -> AEX -> DFW -> MLU -> DFW -> BTR -> CLT -> GSO -> ATL -> MGM -> MDW -> SDF -> ORD -> MQT -> BOS -> ACK -> DEN -> HNL -> PPG -> DEN -> PSC -> SLC -> EUG -> ORD -> ALO -> OAK -> KOA -> ATL -> EYW -> DAL -> LIT -> MSP -> ANC -> ADK -> DTW -> PLN -> MSP -> ATW -> DFW -> GPT -> DTW -> ELM -> MCO -> PSE -> DFW -> GGG -> ATL -> DAB -> MSP -> FAR -> TPA -> SJU -> SLC -> RDM -> MSP -> LSE -> MSY -> MSP -> ANC -> DLG -> DTW -> CAK -> DFW -> BPT -> MSP -> BJI -> PDX -> ORD -> PAH -> STL -> OMA -> ORD -> COU -> MSP -> CID -> DFW -> LAW -> SLC -> WYS -> MSP -> FAI -> BRW -> DEN -> CPR -> SFO -> RDD -> ATL -> BQK -> DEN -> COS -> MSP -> ANC -> SCC -> ATL -> PBI -> DEN -> FCA -> DEN -> BFL -> PHX -> PSP -> DEN -> IDA -> STL -> TUL -> DTW -> BGR -> DTW -> SCE -> DAL -> AMA -> SFO -> MRY -> DEN -> RNO -> SEA -> JNU -> YAK -> DEN -> SGU -> DEN -> HLN -> ATL -> BHM -> SLC -> CDC -> DEN -> MSO -> ORD -> MBS -> DEN -> MMH -> MSP -> GRB -> ORD -> BMI -> DFW -> BRO -> OAK -> LIH -> HOU -> CRP -> MSP -> RST -> DFW -> XNA -> PHX -> SBP -> ATL -> GSP -> MDW -> DSM -> MSP -> GFK -> DTW -> MDT -> ORD -> CHO -> DEN -> BIL -> DCA -> HPN -> DFW -> PIB -> MSP -> ANC -> OME -> DEN -> GUC -> MSP -> ANC -> BET -> ATL -> AGS -> PHX -> FLG -> STL -> ECP -> DTW -> ERI -> PHX -> TUS -> IAH -> LCH -> ABQ -> ORD -> LEX -> DFW -> GCK -> ORD -> FWA -> SEA -> KTN -> WRG -> PSG -> DEN -> GTF -> DTW -> CIU -> MDW -> CLE -> SEA -> JNU -> GST -> RSW -> MSP -> ABR -> ORD -> MLI -> ORD -> CRW -> MDW -> PVD -> DFW -> ABI -> ATL -> EWN -> DTW -> ESC -> ORD -> PIA -> DAL -> OKC -> MCO -> ILG -> MSP -> MSN -> DTW -> BTV -> SEA -> SIT -> DFW -> SPS -> DEN -> GCC -> ATL -> AVL -> MSP -> HIB -> MDW -> MHT -> ORD -> AZO -> DAL -> ICT -> ATL -> CHA -> MCO -> ORH -> MSP -> DIK -> ATL -> VLD -> LAX -> SMX -> DTW -> APN -> ORD -> FNT -> LAS -> SJC -> ORD -> SBN -> HOU -> HRL -> ATL -> HSV -> DAL -> MAF -> DTW -> ITH -> ORD -> LBE -> EWR -> DFW -> CLL -> MDW -> BUF -> SNA -> SLC -> PIH -> MSP -> ANC -> ADQ -> DEN -> EGE -> DEN -> DRO -> DEN -> BZN -> MSP -> ISN -> DFW -> ACT -> ATL -> MLB -> DFW -> SHV
	Costo: 59337
	``` 

### Viaje de N lugares $$(\star\star\star)$$
* Comando: `vacaciones`
* Parámetros: `origen`, y `n`. 
* Utilidad: Obtener algún recorrido que comience en `origen` y que termine en `origen` también, de largo `n` (sin contar la última vuelta al `origen`). No debe pasarse por un aeropuerto más de una vez (salvo el
`origen`, cuando volvemos a éste).
* Ejemplo:
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A^n)$$.
Entrada:
	```
	vacaciones San Diego,6
	vacaciones New York,15
	```
Salida:
	```
	SAN -> ABQ -> HOU -> AUS -> LAX -> BNA -> SAN
	JFK -> AUS -> LAX -> ASE -> DEN -> AMA -> DAL -> ABQ -> HOU -> BHM -> MIA -> BDL -> IAD -> ALB -> MCO -> JFK
	``` 

### Itinerario cultural $$(\star\star)$$

* Comando: `itinerario`
* Parámetros: `ruta`, la ruta el archivo del itinerario. 
* Utilidad: El archivo de `ruta` tiene el formato: 
	```
	ciudad_1,ciudad_2,ciudad_3, ...,ciudad_N
	ciudad_i,ciudad_j
	```
	La primera línea indica las ciudades que se desean visitar. Las siguientes indican que la 
	`ciudad_i` debe visitarse **si o si** antes que la `ciudad_j`. 
	Se debe: 
		1. Imprimir el orden en el que deben visitarse dichas ciudades. 
		1. Imprimir el camino mínimo en tiempo o escalas (según lo que se haya
		implementado en ese caso) a realizar.
* Complejidad: El cálculo de la obtención del itinerario debe realizarse en $$\mathcal{O}(I + R)$$,
siendo $$I$$ la cantidad de ciudades a visitar, y $$R$$ la cantidad de restricciones impuestas. Luego, 
el cálculo de los caminos debe realizarse en $$\mathcal{O}\left(I\times F \log (A)\right)$$ o bien $$\mathcal{O}\left(I\times (A + F)\right)$$, dependiendo de si se trata de un caso u otro.
* Ejemplo, trabajando con [itinerario_ejemplo.csv](itinerario_ejemplo.csv),
Entrada:
	```
	itinerario itinerario_ejemplo.csv
	```
Salida:
	```
	Asheville, Newburgh, Oakland, Wilmington, Jackson, Garden City, Kalispell, Hobbs, Aberdeen, Traverse City, Rhinelander, San Diego, Waco, Dallas-Fort Worth, New York, West Yellowstone
	AVL -> ATL -> DTW -> SWF
	SWF -> FLL -> OAK
	OAK -> ABQ -> MCO -> ILG
	ILG -> MCO -> DEN -> JAC
	JAC -> DFW -> GCK
	GCK -> DFW -> DEN -> FCA
	FCA -> ATL -> IAH -> HOB
	HOB -> IAH -> MSP -> ABR
	ABR -> MSP -> TVC
	TVC -> MSP -> RHI
	RHI -> MSP -> LAX -> CLD
	CLD -> LAX -> DFW -> ACT
	ACT -> DFW
	DFW -> JFK
	JFK -> SLC -> WYS
	```  

### Exportar a archivo KML $$(\star)$$

* Comando: `exportar_kml`. 
* Parámetros: `archivo`. 
* Utilidad: exporta el archivo KML con la ruta del último comando ejecutado (que incluya algún camino,
o rutas áereas). Esto aplica para todos los comandos salvo el de estadísticas, u obtención de los
aeropuertos más centrales. Contamos con un [apunte sobre cómo crear, usar y visualizar archivos KML](/algo2/material/kml).
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A + F)$$.
* Ejemplo: 
Entrada:
	```
	vacaciones San Diego,6
	exportar_kml kml-ejemplo.kml
	```
Salida:
	```
	SAN -> ABQ -> HOU -> AUS -> LAX -> BNA -> SAN
	OK
	```
[Aquí](kml-ejemplo.kml) pueden encontrar el archivo KML exportado.

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

