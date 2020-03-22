---
title: "TP2 – analog: análisis de logs"
math: true
---

Trabajo Práctico 2
==================
{:.no_toc}

El Trabajo Práctico número 2 es de elaboración grupal, y tiene fecha de entrega
para el **viernes 16 de noviembre**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}


Introducción
------------

<!--p style="text-align: center;">
    <img src="{{ 'assets/tps/2018_1/tp2/uma2.png' | relative_url }}" width="200">
</p-->

El aeropuerto de algueiza opera la entrada y salida de aviones, los operarios
de dicho aeropuerto nos han pedido que implementemos un sistema de consulta
de vuelos que les permita: ordenar, filtrar, analizar y obtener información de
los distintos vuelos.


### Archivos

El sistema que actualmente tiene algueiza genera continuamente archivos en formato `.csv`
que contienen la información de cada vuelo. Nuestro sistema deberá procesar estos archivos
y responder a las consultas que los operarios necesiten realizar.
El sistema tiene que ser capaz de recibir en cualquier momento un nuevo archivo
conteniendo el detalle de vuelos (nuevos o viejos) y actualizar sus datos.

### Tablero de despegues

El primer requerimiento que mencionaron los operarios fue que nuestro sistema permita
ordenar los registros de despegues por fecha. Esto debe realizarse de forma ascendente o
descendente según el criterio del usuario. Adicionalmente nos mencionaron que no están
interesados en visualizar todo el listado, por lo que también es necesario que puedan ingresar un
intervalo de fechas de despegue (min / max) y una cantidad de vuelos a listar.

### Informacion de un vuelo

Existen ocasiones en las cuales un operario necesita ver información detallada de un vuelo.
Por este motivo es necesario que ingresando el código de vuelo, el sistema devuelva toda la
información posible asociada al mismo.


### Prioridad de los vuelos

algueiza tiene un sistema de prioridades sobre los vuelos que necesitan atención especial,
los operarios necesitan saber cuales son esos vuelos.
Nuestro sistema deberá ser capaz de devolver los K vuelos que tienen prioridad más importante.


### Borrar datos de vuelos

Finalmente los operarios nos mencionaron que la información que maneja el sistema pierde
validez con el paso del tiempo. Esta información carece de importancia y debe ser eliminada
del sistema.

Con este fin se debe incorporar la posibilidad de eliminar información de vuelos que estén en un
rango de fechas de despegue (min / max).

Interfaz
--------

Es necesario implementar una interfaz del programa, que leerá por entrada
estándar los siguientes comandos:

- `agregar_archivo <nombre_archivo>`: procesa de forma completa un archivo de
`.csv` que contiene datos de vuelos.

- `ver_tablero <K cantidad vuelos> <modo: asc/desc> <desde> <hasta>`: muestra los K
vuelos ordenados por fecha de forma ascendente (asc) o descendente (desc), cuya
fecha de despegue esté dentro de el intervalo `<desde>` `<hasta>`.

- `info_vuelo <código vuelo>`: muestra toda la información posible en sobre el vuelo que
tiene el código pasado por parámetro.

- `prioridad_vuelos <K cantidad vuelos>`: muestra los códigos de los K vuelos que tienen
mayor prioridad.

- `borrar <desde> <hasta>`: borra todos los vuelos cuya fecha de despegue
estén dentro del intervalo `<desde>` `<hasta>` .

Si un comando es válido deberá imprimir `OK` por salida estándar después de ser
ejecutado.
Si un comando no pertenece a los listados previamente o tiene un error, se
imprime `Error en comando <comando>` por `stderr` y continua la ejecución.

El programa no tendrá un comando para terminar. Este finaliza cuando no quedan
más líneas para procesar por entrada estándar. Al finalizar, es importante que
libere toda la memoria dinámica utilizada, y cierre correctamente todos los
archivos procesados.

### Agregar_archivo

El comando se acompaña del nombre de un archivo `csv`, accesible desde el mismo
directorio donde se ejecuta el programa.

*Ejemplo:* `agregar_archivo vuelos-algueiza-parte-01.csv`


Al ejecutarse, el programa deberá leer el archivo, parsear cada línea sabiendo que tiene el formato
[csv](https://es.wikipedia.org/wiki/Valores_separados_por_comas) y guardar cada línea en la/las
estructuras auxiliares correspondientes para ser capaz de ejecutar los otros comandos. En caso que
dos líneas tengan el mismo código de vuelo, el sistema se deberá quedar solamente con la información
de la última aparición.
Este comando se puede ejecutar más de una vez durante el ciclo de uso de nuestro programa, y por lo
tanto puede recibir nuevos archivos. Si un nuevo archivo procesado contiene un código de vuelo que
ya se encuentra en nuestro sistema, nuestro programa deberá quedarse solamente con la información
de la última aparición.


### Ver_tablero

El comando recibe varios parámetros:
- K cantidad vuelos: Numero entero mayor a 0, que indica la cantidad K de vuelos a mostrar
- modo: asc/desc : cadena con "asc" o "desc" como únicos posibles valores, indican el orden a elegir
  utilizando el campo `fecha de despegue`
- desde: cadena en formato YYYY-MM-DDTHH:MM:SS que indica el tiempo desde que se tienen que mostrar
  los vuelos, los vuelos con una fecha de despegue anteriores al tiempo ingresado no se tienen que mostrar.
- hasta: cadena en formato YYYY-MM-DDTHH:MM:SS que indica el tiempo hasta que se tienen que mostrar
  los vuelos, los vuelos con una fecha de despegue posteriores al tiempo ingresado no se tienen que mostrar.


*Ejemplo:* `ver_tablero 5 asc 2018-10-10T00:01:00 2018-10-19T00:12:00`

Al ejecutarse deberán imprimir por salida estandar las fechas de despegue y los códigos de los vuelos que cumplan
con la lógica anteriomente mencionada, cada vuelo se imprime en una nueva línea. El formato de cada línea tiene
que ser `YYYY-MM-DDTHH:MM:SS - <código de vuelo>`.
En el caso que dos vuelos tengan la misma fecha de despegue, se deberá mostrar los vuelos comparando por número de vuelo (tomado como cadena).


*Ejemplo de salida:*

```
2018-10-10T08:51:32 - 1234
2018-10-11T10:20:12 - 11123
2018-10-11T10:20:22 - 9113
2018-10-12T17:20:12 - 991223
2018-10-18T21:32:59 - 98123
OK
```

Casos en los que el sistema tiene que devolver error (con el formato anteriormente mencionado):
- recibir un K igual o menor a 0
- recibir un modo que no sea asc o desc
- recibir una fecha `hasta` que sea anterior a la fecha `desde`

### Info_vuelo

Este comando debe mostrar toda la informacion del vuelo cuyo código de vuelo coincida con el que fue pasado por
parámetro, el formato que tiene que mostrar de la información es exactamente igual a la línea leída del archivo
original, salvo que en vez de comas se tienen espacios.

*Ejemplo:* `info_vuelo 4608`

*Ejemplo de salida:*

```
4608 OO PDX SEA N812SK 08 2018-04-10T23:22:55 05 43 0
OK
```

En caso de ingresar un código de vuelo que no exista dentro de los códigos procesados, se deberá devolver un mensaje de
error con el formato anteriormente mencionado.

### Prioridad_vuelos
Este comando deberá mostrar de mayor a menor, los K vuelos con mayor prioridad que hayan sido cargados en el sistema, de
la forma `<prioridad> - <código de vuelo>`. Si dos vuelos tienen la misma prioridad, se desempatará por el código de
vuelo mostrándolos de menor a mayor (tomado como cadena).

*Ejemplo:* `prioridad_vuelos 3`

*Ejemplo de salida:*

```
10 - 1234
3 - 1624
3 - 325
OK
```

### Borrar
El comando recibe dos argumentos:
- desde: cadena en formato YYYY-MM-DDTHH:MM:SS
- hasta: cadena en formato YYYY-MM-DDTHH:MM:SS

Al ejecutarse, todos los vuelos cuya fecha de despegue sea igual o mayor
a < desde > e igual o menor a < hasta > tienen que
ser borrados del sistema y mostrados por salida estándar.
En caso de que se reciba una fecha < hasta > que sea menor a < desde >, se deberá devolver un mensaje de
error con el formato anteriormente mencionado.


Consideraciones adicionales
---------------------------

### Archivos entrantes

Cada línea de los archivos entrantes `.csv` tienen la siguiente estructura:

- FLIGHT_NUMBER: 4608
- AIRLINE: OO
- ORIGIN_AIRPORT: PDX
- DESTINATION_AIRPORT: SEA
- TAIL_NUMBER: N812SK
- PRIORITY: 08
- DATE: 2018-04-10T23:22:55
- DEPARTURE_DELAY: 05
- AIR_TIME: 43
- CANCELLED: 0

Cada dato de una línea de log está separado por una coma.

Ejemplo:

```
4608,OO,PDX,SEA,N812SK,08,2018-04-10T23:22:55,05,43,0
```


Se provee una [colección de archivos de ejemplo](../../../assets/tps/2018_2/tp2/vuelos-algueiza.zip).


### Tiempos de ejecución

- Agregar_archivo:
  El mantenimiento para actualizar los vuelos debe ser  $$\mathcal{O}(V \log{n})$$ siendo $$V$$ la cantidad de vuelos
  en el nuevo archivo y n la cantidad total de vuelos en el sistema.
- Ver_tablero: debe ser  $$\mathcal{O}(v)$$ en el peor caso (en el que se tenga
  que mostrar todos los vuelos del sistema),
  $$\mathcal{O}(\log{v})$$ en un caso promedio (en el caso en el que no se pidan mostrar demasiados visitantes).
  $$v$$ es la cantidad de vuelos.
- Info_vuelo: debe ser  $$\mathcal{O}(1)$$.
- Prioridad_vuelos:  debe ser  $$\mathcal{O}(n \log{K})$$. Siendo K la cantidad de vuelos a mostrar y n la cantidad de
  vuelos en el sistema.
- Borrar: debe ser  $$\mathcal{O}(K \log{n})$$ . Siendo K la cantidad de vuelos que hay en el rango de fechas ingresado
  y n la cantidad de vuelos en todo el sistema.


Ejemplos
--------

Se proveen ejemplos completos para mostrar la salida esperada en cada instrucción.

### Agregar_archivo

*Ejemplo:* `agregar_archivo vuelos-algueiza-parte-01.csv`

*Salida esperada:*

Si el comando se ejecuta correctamente deberá imprimir `OK` por salida estándar después de ser ejecutado.
Si se produce un error al procesar el archivo se imprime `Error en comando <comando>` por `stderr` y se continua la ejecución.

### Ver_tablero

*Ejemplo:* `ver_tablero 3 asc 2018-04-08T10:00:00 2018-04-21T00:12:00`

*Salida esperada:*

```
2018-04-08T11:15:29 - 6391
2018-04-10T23:22:55 - 4608
2018-04-21T07:41:48 - 5460
OK
```

### Info_vuelo

*Ejemplo:* `info_vuelo 4608`

*Salida esperada:*

```
4608 OO PDX SEA N812SK 08 2018-04-10T23:22:55 05 43 0
OK
```

### Prioridad_vuelos

*Ejemplo:* `prioridad_vuelos 4`

*Ejemplo de salida:*

```
26 - 6391
15 - 1086
12 - 4701
OK
```

### Borrar

*Ejemplo:* `borrar 2018-10-04T02:01:01 2018-11-01T03:00:00`

*Ejemplo de salida:*

```
4701 EV EWR CMH N11150 12 2018-10-04T04:19:24 -10 55 0
2807 MQ SGF DFW N604MQ 00 2018-10-05T13:57:14 00 107 0
OK
```

Criterios de aprobación
------------------------

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin
advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- el código de la solución del TP.
- el código de los TDAs programados en la cursada que se requieran, con las modificaciones que sean necesarias.
- un archivo `deps.mk` con las dependencias del proyecto en formato make. Este deberá contener sólamente una
línea que indique qué _objetos_ necesita para compilar el ejecutable `algueiza`, por ejemplo:

``` makefile
algueiza: tp2.o hash.o abb.o heap.o strutil.o
```

El corrector automático va a interpretar ese archivo de dependencias y va a compilar todos los `.o` especificados a
partir de los `.h` y `.c` que deberán enviar, con los siguientes flags de GCC:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. en forma digital a través del [sistema de entregas]({{site.entregas}}), con todos los archivos mencionados en un
único archivo ZIP.
2. en papel durante la clase (si su ayudante lo requiere) el código del Trabajo en hoja A4 **abrochadas, sin folio,
informe ni carátula**. No es necesario reimprimir el código de los TDA.
