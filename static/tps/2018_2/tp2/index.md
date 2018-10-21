---
layout: page
title: "TP2 – analog: análisis de logs"
permalink: '/tps/2018_2/tp2'
math: true
---

Trabajo Práctico 2
================
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

El aeropuerto de Algueiza opera la entrada y salida de aviones, los operarios 
de dicho aeropuerto nos han pedido que implementemos un sistema de consulta 
de vuelos para que ellos puedan ordenar, filtrar, analizar y obtener información de 
los distintos vuelos.


### Archivos

El sistema que actualmente tiene Algeiza genera continuamente archivos formato `.csv` 
que contienen la información de cada vuelo. Nuestro sistema tendrá que ser capaz
de procesar estos archivo, y ser capaz de responder las consultas que los operarios 
necesiten realizar.  
El sistema tiene que ser capaz de recibir en cualquier momento un nuevo archivo
conteniendo vuelos (nuevos o viejos) y actualizar sus datos.

### Tablero de llegadas y salidas

El primer requerimiento que mencionaron los operarios fue que nuestro sistema sea 
capaz de ordenar los registros de llegada/salida por fecha. Con la opción de pedir 
de forma ascendente o descendete. Adicionalemente nos dijieron que no quieren ver
todo el listado, por lo que tambíen hay que permitirles a ellos puedan ingresar un
intervalo de horario (min / max) de los vuelos que quieren ver.

### Informacion de un vuelo

Hay veces que los operarios necesitan ver información de un vuelo particular. Para 
ello ellos quieren que ingresando el codigo de vuelo, el sistema les devuelva toda
la información posible del mismo.


### Prioridad de los vuelos

Algueiza tiene un sistema de prioridades de los vuelos que necesitan atención especial,
los operarios quieren saber cuales son esos vuelos. Nuestor sistema tendra que tener la 
capaciad de devolver los K vuelos que tienen prioridad mas importante.

### Borrar datos de vuelos

Finalmente nuestro sistema tiene que ser capaz de eliminar informacion que los
operarios consideren que ya no es de importancia para ellos, por lo cual hay que 
tener una funcionaliad que permir borrar la informacion de vuelos que estén entre 
dos rangos de fechas a borrar.

Interfaz
-------- 

Es necesario implementar una interfaz del programa, que leerá por entrada
estándar los siguientes comandos:

- `agregar_archivo <nombre_archivo>`: procesa de forma completa un archivo de
csv con nuevos vuelos.

- `ver_tablero <K cantidad vuelos> <modo: asc/desc> <desde> <hasta>`: muestra los K 
vuelos ordenados por fecha de forma ascendente (asc) o descendente (desc), cuya 
fecha de despegue esté dentro de el intervalo `<desde>` `<hasta>`.

- `info_vuelo <codigo vuelo>`: muestra toda la informacion posible en sobre el vuelo que 
tiene el codigo pasado por parametro.

- `prioridad_vuelos <K cantidad vuelos>`: muestra los codigos de los K vuelos que tienen
mayor prioridad.

- `borrar <desde> <hasta>`: borra todos los vuelos cuya fecha de despegue 
estén dentro de el intervalo `<desde>` `<hasta>` .

Si un comando es válido deberá imprimir `OK` por salida estándar después de ser
ejecutado.
Si un comando no pertenece a los listados previamente o tiene un error, se
imprime `Error en comando <comando>` por `stderr` y se finaliza la ejecución.

El programa no tendrá un comando para terminar. Este finaliza cuando no quedan
más líneas para procesar por entrada estándar. Al finalizar, es importante que
libere toda la memoria dinámica utilizada, y cierre correctamente todos los
archivos procesados.

### Agregar_archivo

El comando se acompaña del nombre de un archivo `csv`, accesible desde el mismo
directorio donde se ejecuta el programa.

*Ejemplo:* `agregar_archivo vuelos-algueiza-parte01.csv`


Al ejecutarse, el programa deberá leer el archivo, parsear cada linea sabiendo que tiene el formato
[csv](https://es.wikipedia.org/wiki/Valores_separados_por_comas) y guardar cada linea en la/las 
estructuras auxiliares correspondientes para ser capaz de ejecutar los otros comandos. En caso que 
dos lineas tengan el mismo codigo de vuelo, el sistema se deberá quedar solamente con la información
de la ultima aparición.  
Este comando se puede ejecutar más de una vez durante el ciclo de uso de nuestro programa, y por lo
tanto puede recibir nuevos archivos. Si un nuevo archivo procesado contiene un codigo de vuelo que 
ya se encuentra en nuestro sistema, nuestro programa deberá quedarse solamente con la información
de la ultima aparición.  


### Ver_tablero 

El comando recibe varios parametros:
- K cantidad vuelos: Numero entero mayor a 0, que indica la cantidad K de vuelos a mostrar
- modo: asc/desc : cadena con "asc" o "desc" con unicos posibles valores, indican el orden a elegir 
  utilizando el campo `fecha de despegue` 
- desde : cadena en formato aaaa-mm-dd-hhmm que indica el tiempo desde que se tienen que mostrar 
  los vuelos, los vuelos con una fecha de despegue anteriores al tiempo ingresado no se tienen que mostrar.
- hasta : cadena en formato aaaa-mm-dd-hhmm que indica el tiempo hasta que se tienen que mostrar 
  los vuelos, los vuelos con una fecha de despegue posteriores al tiempo ingresado no se tienen que mostrar.


*Ejemplo:* `ver_tablero 5 asc 2018-10-10-0001 2018-10-11-0012`

Al ejecutarse deberán imprimir por salida estandar los codigos de los vuelos que cumplan con la logica anteriomente 
mencionada, cada vuelo se imprime en una nueva linea.


*Ejemplo de salida:*

```
1234
55234
453
111223
98123
OK
```

Casos el los que el sistema tiene que devolver error (con el formato anteriormente mencionado): 
- recibir un K igual o menor a 0
- recibir un modo que no sea asc o desc
- recibir una fecha `hasta` que sea anterior a la fecha `desde`

### Info_vuelo

Este comando debe mostrar toda la informacion del vuelo cuyo codigo de vuelo coincida con el que fue pasado por 
parametro, el formato que tiene que mostrar de la informacion es exactamente igual a la linea leida del archivo
original.

*Ejemplo:* `info_vuelo 1234`

*Ejemplo de salida:*

```
TODO: ACA PONER UNA LINEA DEL ARCHIVO 
OK
```

En caso que se pase un codigo de vuelo que no exista dentro de los codigos procesados, se deberá devolver un mensaje de 
error con el formato anteriormente mencionado.

### Prioridad_vuelos
TODO: elaborar comando

### Borrar
TODO: elaborar comando


Consideraciones adicionales
---------------------------

### Archivos entrantes

Cada línea de los archivos entrantes `.csv` tienen la siguiente estructura:

TODO: Poner estructura (y pequeña explicacion) de cada campo del archivo
- Campo1: .
- Campo2.
- etc.

Cada dato de una línea de log está separado por una coma.

Ejemplo:

```
TODO: PONER UN EJEMPLO DE UNA LINEA
```


Se provee una [colección de archivos de ejemplo]() TODO: armar ejemplos y subirlos al drive.

### Fecha y hora

La fecha y hora estarán brindadas en formato
[ISO-8601](https://www.iso.org/iso-8601-date-and-time-format.html),<sup>[2](https://xkcd.com/1179/)</sup>
que consiste de año, mes, día, T mayúscula como separador, hora, minutos,
segundos y zona horaria:

- año = 4 dígitos
- mes = 3 letras
- día = 2 dígitos
- hora = 2 dígitos
- minutos = 2 dígitos
- segundos = 2 dígitos
- zona = +/- 4 dígitos.

Para interpretar la sección de la fecha en C pueden utilizar el siguiente
fragmento de código, que devuelve un tipo `time_t` dado una cadena con el
formato indicado:

``` c
#define _XOPEN_SOURCE

#include <time.h>

#define TIME_FORMAT "%FT%T%z"

/*
    Dada una cadena en formato ISO-8601 devuelve una variable de tipo time_t
    que representa un instante en el tiempo.
*/
time_t iso8601_to_time(const char* iso8601)
{
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}
```

Esta variable de tipo `time_t` puede ser usada junto con la función `timediff`
([info](http://man7.org/linux/man-pages/man3/difftime.3.html))
para calcular la diferencia en segundos entre dos fechas.

### Tiempos de ejecución

- Agregar_archivo:
    - La búsqueda de DoS debe ser en  $$\mathcal{O}(n)$$ siendo $$n$$ la cantidad de líneas del
      log.
    - El mantenimiento para actualizar los visitantes debe ser  $$\mathcal{O}(n \log v)$$
      siendo $$v$$ la cantidad de visitantes en toda la historia del programa.
- Ver_tablero: debe ser  $$\mathcal{O}(v)$$ en el peor caso (en el que se tenga que
  mostrar todos los visitantes),  $$\mathcal{O}(\log v)$$ en un caso promedio (en el caso en
  el que no se pidan mostrar demasiados visitantes). $$v$$ nuevamente es la cantidad histórica de 
  visitantes. 
- Info_vuelo: debe ser  $$\mathcal{O}(1)$$.
- Prioridad_vuelos:  debe ser  $$\mathcal{O}(K \ log n)$$
- Borrar: debe ser  $$\mathcal{O}(K \ log n)$$


Ejemplos
--------

Se proveen ejemplos completos para mostrar la salida esperada en cada
instrucción.

### Agregar_archivo

TODO: poner ejemplos

### Ver_tablero

TODO: poner ejemplos

### Info_vuelo

TODO: poner ejemplos

### Prioridad_vuelos

TODO: poner ejemplos

### Borrar

TODO: poner ejemplos

Criterios de aprobación
------------------------

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- el código de la solución del TP.
- el código de los TDAs programados en la cursada que se requieran, con las
modificaciones que sean necesarias.
- un archivo `deps.mk` con las dependencias del proyecto en formato make. Este
deberá contener sólamente una línea que indique qué _objetos_ necesita para
compilar el ejecutable `analog`, por ejemplo:

``` makefile
algueiza: tp2.c hash.o abb.o heap.o strutil.o timeutils.o
```

El corrector automático va a interpretar ese archivo de dependencias y va a
compilar todos los `.o` especificados a partir de los `.h` y `.c` que deberán
enviar, con los siguientes flags de GCC:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. en forma digital a través del [sistema de entregas]({{site.entregas}}),
con todos los archivos mencionados en un único archivo ZIP.
2. en papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, informe ni carátula**. No es necesario
reimprimir el código de los TDA ni de `strutil`.
