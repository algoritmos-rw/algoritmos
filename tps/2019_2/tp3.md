---
title: "TP3 – Grafos y aeropuertos"
math: true
---

Trabajo Práctico 3
==================
{:.no_toc}

El Trabajo Práctico número 3 es de elaboración grupal, y tiene fecha de entrega
para el **viernes 6 de diciembre**.

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
costo o tiempo posible. Algunas aerolíneas quieren que sea la mejor solución posible, sin excepciones.
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

Una consultora uso un [innovador script](parser.py) para parsear dichos datos en los siguientes archivos:
* El archivo [aeropuertos.csv](aeropuertos.csv) con el formato:
	```
	ciudad,codigo_aeropuerto,latitud,longitud
	```
* El archivo [vuelos.csv](vuelos.csv) con el formato:
	```
	aeropuerto_i,aeropuerto_j,tiempo_promedio,precio,cant_vuelos_entre_aeropuertos
	```

Adicionalmente, para poder realizar algunas pruebas rápidas (especialmente en los algoritmos que
más tiempo puedan demorar) se crea este otro set con [aeropuertos](aeropuertos_inventados.csv) y
[vuelos](vuelos_inventados.csv) inventados.

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

El programa debe recibir por parámetro y cargar en memoria el set de datos (`$ ./flycombi
aeropuertos.csv vuelos.csv`) y luego solicitar el ingreso de comandos por entrada estándar,
del estilo `<comando> 'parametro'`. Notar que esto permite tener un archivo de instrucciones a ser
ejecutadas (i.e. `$ ./flycombi aeropuertos.csv vuelos.csv < entrada.txt`).

De todas las funcionalidades, algunas son obligatorias, y las que lo son tienen más de una opción
para ser implementadas. Algunas consideraciones:
1. Cada funcionalidad e implementación otorga distinta cantidad de puntos, basado en dificultad y
el interés del curso en que implementen dicha funcionalidad o implementación
particular de la misma. (Cada estrella ★ corresponde a un punto.)
1. Se pueden implementar todas las implementaciones posibles de una misma funcionalidad. Se tomarán
en cuenta los puntos de todas las partes implementadas.
1. Se deben conseguir al menos 10 puntos para poder aprobar el TP.
1. En caso de obtener menos de 12 puntos, la nota máxima será 9.
1. En caso de obtener 16 puntos o más la nota máxima del trabajo práctico puede llegar a 11.
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

### Caminos mínimos (obligatorio implementar al menos uno)

#### Camino más barato y camino más rápido (★)

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

#### Camino con menor cantidad de escalas (★)

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
[Betweeness Centrality](/algo2/material/apuntes/centralidad) y otro sobre
[PageRank](/algo2/material/apuntes/pagerank).

_Nota_: PageRank en realidad realiza una aproximación de otro tipo de centralidad (_Eigenvector Centrality_) que
la que realmente buscamos en este ejercicio. De todas formas, la consideramos como una implementación válida para
este punto.

#### Betweeness Centrality (★★★)

* Comando: `centralidad`
* Parámetros: `n`, la cantidad de aeropuertos más importantes a mostrar.
* Utilidad: nos muestra los `n` aeropuertos más centrales/importantes del mundo,
de mayor importancia a menor importancia.
* Complejidad: Este comando debe ejecutar en $$\mathcal{O}(A \times F\log(A))$$.
* Ejemplo:
Entrada:
	```
	centralidad 5
	```
Salida:
	```
	ATL, ORD, LAX, DFW, DEN
	```


#### Betweeness Centrality aproximada (★)

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

#### Pagerank (★★)

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

### Optimización de rutas para nueva aerolínea (★★)

* Comando: `nueva_aerolinea`.
* Parámetros: `ruta`, ruta del archivo de salida.
* Utilidad: exportar un archivo con las rutas que permitan implementar una nueva aerolínea tal que se
pueda comunicar a todos los aeropuertos (en esta primera iteración, sólo de Estados Unidos) con dicha
aerolínea, pero que el costo total de la licitación de las rutas aéreas sea mínima. Se considera que
el costo de las rutas es proporcional al costo de los pasajes, por lo que se puede trabajar
directamente con dicho costo.
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


### Recorrer el mundo, de forma óptima (★★★)

* Comando: `recorrer_mundo`.
* Parámetros: `origen`, ciudad desde la que se parte para comenzar el recorrido.
* Utilidad: nos devuelve una lista en orden de cómo debemos movernos por el mundo para visitar todas
**las ciudades** del mundo, demorando lo menos posible. Podemos volver a usar un aeropuerto ya usado,
u otro de alguna ciudad ya visitada, si eso mejora la duración de nuestro viaje.
* Complejidad: que demore lo que deba demorar para obtener el resultado óptimo. _Cuidado_: considerar optimizarlo, puesto que hay un límite de tiempo en el corrector automático.
* Ejemplo:
Entrada:
	```
	recorrer_mundo San Diego
	```
Salida:
	```
	(Recorrido con el formato de caminos mínimos)
	Costo: costo del recorrido
	```
Debido a que este comando puede demorar mucho tiempo, se recomienda realizar pruebas con el set
de aeropuertos y vuelos inventados antes de hacer la prueba sobre el set de datos real. Ejemplo:
Entrada:
	```
	recorrer_mundo Gotica
	```
Salida:
	```
	BAT -> LAN -> ASH -> BH6 -> JFK -> ATL -> NAR -> SHE -> RIV -> WAC
	Costo: 2580
	```
_Aclaración_: pueden ser otros los caminos, siempre y cuando sean válidos y se trate de un costo
mínimo.

### Recorrer el mundo, de forma aproximada (★)
* Comando: `recorrer_mundo_aprox`
* Parámetros: `origen`, ciudad desde la que se parte para comenzar el recorrido.
* Utilidad: nos devuelve una lista en orden de cómo debemos movernos por el mundo para visitar todas
**las ciudades** del mundo, demorando **aproximadamente** lo menos posible. Podemos volver a usar un
aeropuerto ya usado, u otro de alguna ciudad ya visitada, si eso mejora la duración de nuestro viaje.
* Complejidad: idealmente, que sea un algoritmo cuanto mucho cuadrático.
* Ejemplo:
Entrada:
	```
	recorrer_mundo_aprox Kansas City
	```
Salida:
	```
	MCI -> DEN -> MMH -> SFO -> SLC -> DFW -> GPT -> DFW -> OMA -> MSP -> HIB -> MSP -> PIT -> ORD -> SPI -> DFW -> GCK -> DFW -> OGG -> KOA -> OGG -> ORD -> AVP -> EWR -> PVD -> DTW -> SEA -> SFO -> SBP -> PHX -> ATL -> MYR -> PBG -> MYR -> DFW -> GGG -> DFW -> DEN -> MOT -> MSP -> BOS -> ACK -> BOS -> SLC -> BTM -> SLC -> MSO -> SFO -> CEC -> SFO -> FLL -> STT -> ORD -> BIL -> DEN -> BNA -> DCA -> SYR -> ORD -> STC -> ORD -> DEN -> CPR -> DEN -> RDU -> DFW -> ACT -> DFW -> DTW -> BUF -> BOS -> ACY -> DTW -> SLC -> PIH -> SLC -> ORD -> FWA -> ORD -> PIA -> DEN -> EUG -> SLC -> HOU -> CRP -> HOU -> JFK -> DFW -> BRO -> IAH -> IAD -> UST -> IAD -> ORD -> CWA -> ORD -> ATL -> MLB -> ATL -> ORD -> CMI -> ORD -> AZO -> ORD -> DEN -> LAR -> DEN -> ICT -> DEN -> RNO -> DEN -> PUB -> DEN -> DTW -> APN -> DTW -> CLT -> ILM -> ATL -> ECP -> ATL -> MYR -> LBE -> ORD -> LAN -> ORD -> OKC -> SLC -> PSC -> DEN -> SDF -> DEN -> JAC -> ATL -> GSP -> MDW -> SEA -> SIT -> SEA -> DEN -> FSD -> DEN -> BOI -> PDX -> ANC -> OTZ -> ANC -> DEN -> MAF -> DEN -> SLC -> VEL -> SLC -> AUS -> DTW -> ELM -> DTW -> CID -> DEN -> LAX -> SMX -> LAX -> HOU -> JAX -> DFW -> LAW -> DFW -> ORD -> TVC -> ORD -> EAU -> ORD -> DSM -> ATL -> TLH -> ATL -> GRR -> ORD -> LNK -> DEN -> RDM -> SLC -> ATL -> SAV -> ATL -> ROA -> ORD -> ANC -> SCC -> ANC -> SFO -> ACV -> SFO -> DEN -> BMI -> DEN -> BUR -> DEN -> DVL -> DEN -> ATL -> DHN -> ATL -> LAS -> SLC -> CNY -> SLC -> DFW -> JLN -> DFW -> CMH -> MSP -> ISN -> MSP -> FAI -> BRW -> ANC -> OME -> ANC -> MSP -> BWI -> MCO -> MSP -> ABR -> MSP -> HNL -> GUM -> HNL -> DFW -> ROW -> DFW -> SLC -> CDC -> SLC -> DEN -> DAY -> DTW -> MQT -> ORD -> GRB -> MSP -> DEN -> SAF -> LAX -> MRY -> SFO -> ORD -> ALO -> ORD -> COS -> ORD -> DBQ -> ORD -> SUX -> ORD -> ANC -> BET -> ANC -> DFW -> FSM -> DFW -> ANC -> CDV -> ANC -> SLC -> RAP -> SLC -> LGB -> OAK -> IAH -> LCH -> IAH -> SBN -> DTW -> MYR -> IAG -> MYR -> ATL -> SLC -> LWS -> SLC -> HNL -> PPG -> HNL -> DEN -> MLI -> ORD -> BWI -> ISP -> BWI -> MDW -> TUS -> DEN -> ASE -> DEN -> PHL -> BWI -> MKE -> ORD -> MKG -> ORD -> LAX -> CLD -> LAX -> DFW -> SPS -> DFW -> ORD -> ATW -> ORD -> CHO -> ORD -> SFO -> RDD -> SFO -> SEA -> JNU -> GST -> JNU -> SEA -> ATL -> GTR -> ATL -> PHX -> FLG -> PHX -> LAS -> LBB -> DAL -> TUL -> ATL -> GSO -> DTW -> CAK -> DTW -> SEA -> JNU -> YAK -> JNU -> SEA -> DFW -> BPT -> DFW -> PHX -> YUM -> PHX -> JFK -> HYA -> JFK -> ORD -> COU -> DFW -> SLC -> SUN -> SLC -> ANC -> ADQ -> ANC -> DFW -> MFE -> IAH -> BZN -> SEA -> KTN -> WRG -> KTN -> SEA -> SLC -> EKO -> SLC -> MSP -> BRD -> MSP -> ORD -> CMX -> ORD -> MSP -> GEG -> DEN -> ATL -> FAY -> ATL -> IAH -> LRD -> IAH -> GRK -> DFW -> SHV -> ATL -> LGA -> BGR -> DTW -> LEX -> MSP -> ANC -> DLG -> ANC -> DFW -> ABI -> DFW -> CLE -> BDL -> DCA -> BTR -> DFW -> DEN -> IDA -> DEN -> DFW -> TXK -> DFW -> ANC -> AKN -> ANC -> DFW -> LFT -> IAH -> MEM -> DEN -> GCC -> DEN -> SBA -> PHX -> ATL -> SRQ -> ATL -> HSV -> ATL -> MOB -> ATL -> VLD -> ATL -> MGM -> ATL -> EWN -> ATL -> MIA -> DFW -> SJT -> DFW -> OGG -> LIH -> DEN -> PHF -> DEN -> MFR -> SLC -> HOU -> PNS -> ATL -> AGS -> ATL -> XNA -> ATL -> CRW -> ATL -> TYS -> DTW -> BGM -> DTW -> MDT -> ATL -> MLU -> ATL -> VPS -> DFW -> DEN -> COD -> ORD -> SCE -> ATL -> ABY -> ATL -> BHM -> ATL -> STL -> MSP -> RHI -> MSP -> BJI -> MSP -> HLN -> DEN -> DFW -> GRI -> DFW -> MHK -> ORD -> CVG -> DEN -> DRO -> DFW -> PBI -> MIA -> MCO -> PSE -> MCO -> ORD -> TOL -> ORD -> EVV -> DTW -> CIU -> DTW -> ORD -> LSE -> ORD -> AVL -> ATL -> RIC -> MCO -> ORH -> MCO -> LAS -> SJC -> MSP -> MBS -> ORD -> DFW -> PIB -> DFW -> TPA -> DTW -> ESC -> DTW -> DEN -> RKS -> DEN -> MSP -> RST -> DTW -> ABE -> ATL -> RSW -> DEN -> JMS -> DEN -> DTW -> BTV -> DTW -> HPN -> DTW -> PLN -> DTW -> MSP -> GFK -> MSP -> FAR -> DFW -> TYR -> IAH -> ATL -> BQK -> ATL -> ABQ -> ATL -> GNV -> ATL -> SLC -> TWF -> SLC -> DTW -> SWF -> DTW -> ATL -> TRI -> ATL -> PHX -> BFL -> IAH -> AEX -> DFW -> DEN -> SGU -> SLC -> SEA -> KTN -> WRG -> PSG -> JNU -> ANC -> OGG -> ITO -> LAX -> IND -> ORD -> MSN -> DEN -> ONT -> DEN -> GUC -> IAH -> SJU -> STX -> ATL -> DEN -> HYS -> DEN -> ORD -> PAH -> ORD -> CHA -> ATL -> SEA -> BLI -> SEA -> DTW -> ITH -> DTW -> ORD -> FNT -> MSP -> GTF -> DEN -> ELP -> SAT -> DEN -> BIS -> MSP -> ORF -> MSP -> ANC -> ADK -> ANC -> ATL -> DAB -> ATL -> DFW -> MEI -> DFW -> SLC -> WYS -> SLC -> SMF -> MSP -> DLH -> MSP -> BOS -> MVY -> BOS -> MSP -> DIK -> MSP -> IMT -> MSP -> DTW -> ERI -> DTW -> DEN -> GJT -> DEN -> MSP -> INL -> MSP -> DEN -> AMA -> DEN -> HDN -> DEN -> LIT -> BWI -> MHT -> ATL -> EYW -> ATL -> MTJ -> ORD -> TTN -> ORD -> EGE -> IAH -> HRL -> IAH -> HOB -> IAH -> FLL -> BQN -> FLL -> MSY -> SAN -> FAT -> SFO -> OTH -> SFO -> SNA -> SLC -> FCA -> SLC -> PSP -> DFW -> CLL
	Costo: 80387
	```
Con el set de datos de pruebas:
Entrada:
	```
	recorrer_mundo_aprox Gotica
	```
Salida:
	```
	BAT -> LAN -> JFK -> ATL -> WAC -> NAR -> ASH -> WAC -> RIV -> SHE -> ASH -> BH6
	Costo: 3765
	```

### Viaje de N lugares (★★★)
* Comando: `vacaciones`
* Parámetros: `origen`, y `n`.
* Utilidad: Obtener algún recorrido que comience en `origen` y que termine en `origen` también, de largo `n` (sin contar la última vuelta al `origen`). No debe pasarse por un aeropuerto más de una vez (salvo el
`origen`, cuando volvemos a éste). En caso de no encontrar un recorrido de dicho largo que vuelva
luego al origen, imprimir `"No se encontro recorrido"`.
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

### Itinerario cultural (★★)

* Comando: `itinerario`
* Parámetros: `ruta`, la ruta el archivo del itinerario.
* Utilidad: El archivo de `ruta` tiene el formato:
	```
	ciudad_1,ciudad_2,ciudad_3, ...,ciudad_N
	ciudad_i,ciudad_j
	```
	La primera línea indica las ciudades que se desean visitar. Las siguientes indican que la
	`ciudad_i` debe visitarse **sí o sí** antes que la `ciudad_j`.
	Se debe:
1. Imprimir el orden en el que deben visitarse dichas ciudades.
1. Imprimir el camino mínimo en tiempo o escalas (según lo que se haya implementado en ese caso)
a realizar.
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
Si bien en este ejemplo no llega a notarse, no tiene por qué ser el mismo aeropuerto el de llegada
que el de salida (si deben ser aeropuertos de la ciudad en la cual se está parando).

### Exportar a archivo KML (★)

* Comando: `exportar_kml`.
* Parámetros: `archivo`.
* Utilidad: exporta el archivo KML con la ruta del último comando ejecutado (que incluya algún camino,
o rutas áereas). Esto aplica para todos los comandos salvo el de estadísticas, u obtención de los
aeropuertos más centrales. Contamos con un [apunte sobre cómo crear, usar y visualizar archivos KML](/algo2/material/apuntes/kml).
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

## Entrega

Adicionalmente a los archivos propios del trabajo práctico debe agregarse un archivo `entrega.mk` que contenga la regla `flycombi` para generar el ejecutable de dicho programa (sea compilando o los comandos que fueren necesarios). Por ejemplo, teniendo un TP elaborado en Python, podría ser:

``` makefile
flycombi: flycombi.py grafo.py biblioteca.py
	cp flycombi.py flycombi
	chmod +x flycombi
```

**Importante**: En caso de recibir un error `FileNotFoundError: [Errno 2] No such file or directory: './flycombi': './flycombi'`, tener en cuenta que para el caso de enviar código escrito en Python es necesario además indicar la ruta del intérprete. Esto puede hacerse agregando como primera línea del archivo principal (en el ejemplo, sería `flycombi.py`) la línea: `#!/usr/bin/python3`.

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

