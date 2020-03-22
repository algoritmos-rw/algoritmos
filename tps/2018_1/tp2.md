---
title: "TP2 – analog: análisis de logs"
math: true
---

Trabajo Práctico 2
==================
{:.no_toc}

El Trabajo Práctico número 2 es de elaboración grupal, y tiene fecha de entrega
para el **viernes 15 de junio**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}


Introducción
------------

<!--p style="text-align: center;">
    Anita me dijo que el martes después de rendir agrega una imagen
    <img src="{{ 'assets/tps/2018_1/tp2/uma2.png' | relative_url }}" width="200">
</p-->


Una cierta materia de una prestigiosa Universidad de Danza clásica ha puesto a
disposición un corrector automático de coreografías. Puesto que los docentes a
cargo del curso no tienen demasiada experiencia en programación de sistemas web,
la decenas de visitas diarias al sitio han hecho que los servidores se caigan.

Se les suma el problema de que, como los servidores estaban muy mal configurados,
las entradas en dichos archivos están completamente desordenados.

Como cada acceso al sistema queda registrado, los bailarines han buscado ayuda a
estudiantes de Algoritmos y Programación II con mucha experiencia en manejo de
archivos, ordenamientos y entrada estándar en C.


### Servidores y archivos de log

En algunas situaciones es preferible que una página web no esté habilitada en un
solo servidor web, sino en varios, y si es posible en lugares físicos del
planeta alejados entre sí.

Esto se hace para evitar que un problema regional afecte la disponibilidad de la
página web a nivel global. También sirve para optimizar el tráfico, conectando
un usuario directamente con el servidor más cercano a su ubicación.
Como cada servidor corre de manera independiente, también tendrá su archivo de
log independiente.

Para este trabajo, dispondremos de archivos de log de [Apache](https://httpd.apache.org).
Cada archivo de log representa la historia de solicitudes (_requests_) de un
usuario hacia los recursos (_resources_) que provee un servidor en particular.
Estos pueden ser cualquier tipo de archivos, desde páginas web (`.html`) hasta
videos (`.avi`, `.mov`).

### Denegación de servicios

Nuestro interés es detectar situaciones de sobrecarga de solicitudes de un mismo
cliente en un tiempo breve sobre un mismo servidor.
A este tipo de comportamientos se los llama [ataque de denegación de servicio](https://es.wikipedia.org/wiki/Ataque_de_denegación_de_servicio)
(DoS) cuando se realizan de forma malintencionada, con el objetivo de
incrementar el tráfico hasta saturarlo haciendo imposible que otros usuarios
legítimos puedan acceder a los servicios brindados por ese servidor.

### Direcciones IP

Podemos diferenciar de forma unívoca a un cliente que accede a un recurso a
través de un identificador llamado _dirección IP_, o simplemente IP. Estos
quedan registrados en los archivos de logs, y constan de cuatro bloques
numéricos de un byte (es decir, desde 0 a 255). Las direcciones IP usualmente
se escriben separadas por puntos: 192.168.1.1 y 63.255.0.12 son IPs válidas.

Notar que, alfabéticamente, el texto `190.0.0.0` es anterior a `62.0.0.0`, por
ejemplo, aunque la numeración no sigue el mismo orden.
Por lo tanto, en este trabajo, la forma en que se comparen debe tener en cuenta
que se están comparando cuatro grupos de números, y que los números se comparan
por valor.

Interfaz
--------

Es necesario implementar una interfaz del programa, que leerá por entrada
estándar los siguientes comandos:

- `ordenar_archivo <nombre_archivo> <nombre_salida>`: como utilidad, permite ordenar un archivo
de log.
- `agregar_archivo <nombre_archivo>`: procesa de forma completa un archivo de
log.
- `ver_visitantes <desde> <hasta>`: muestra todas las IPs que solicitaron algún
recurso en el servidor, dentro del rango de IPs determinado.

Si un comando es válido deberá imprimir `OK` por salida estándar después de ser
ejecutado.
Si un comando no pertenece a los listados previamente o tiene un error, se
imprime `Error en comando <comando>` por `stderr` y se finaliza la ejecución.

El programa no tendrá un comando para terminar. Este finaliza cuando no quedan
más líneas para procesar por entrada estándar. Al finalizar, es importante que
libere toda la memoria dinámica utilizada, y cierre correctamente todos los
archivos procesados.

Adicionalmente, el programa deberá recibir por parámetro un número entero `M` que indique
la cantidad de memoria (en kilobytes) disponible para realizar el ordenamiento.

### Ordenar Archivo

El comando se acompaña del nombre de un archivo de log, accesible desde el mismo
directorio donde se ejecuta el programa, y otro como salida del comando.

*Ejemplo:* `ordenar_archivo 20171025.log 20171025-ordenado.log`

Al ejecutarse, se deberá ordenar el archivo por el campo de tiempo, y dejar el resultado ordenado
en la ruta especificada como destino (segundo parámetro). En caso de dos líneas que tengan el mismo
timestamp, se debe comparar por IP (de la misma forma que en `ver_visitantes`), y en caso de una
igualdad en este último, por recurso (comparación entre strings). Esto último se pide exclusivamente
para poder realizar comparaciones de forma sencilla en las pruebas automáticas.

El archivo puede no caber en memoria, por lo que deberán utilizar
algún [algoritmo de ordenamiento externo](/algo2/material/apuntes/ordenamientos_externos).
Por simplicidad, el programa recibirá por parámetro la cantidad de memoria que puede utilizarse
para esta tarea. Recordar que es importante eliminar los archivos temporales. En caso de no hacerlo **no
se aprobará la entrega**.

Una forma de probar que el programa efectivamente cumple con la restricción, es usando el comando `ulimit`.
Recomendamos usarlo creando un script (e.g. `limite_memoria.sh`) con el contenido:

        ulimit -v 1000
        ./analog 200

Dado que ese límite es para todo el programa en su totalidad, no solamente lo que pidamos para hacer el ordenamiento,
poner un valor más alto que el pasado por parámetro. Por ejemplo, si piensan trabajar con 100 KB, poner como límite al
menos 400 KB (la unidad del parámetro que recibe ulimit es en KB).

### Agregar archivo

El comando se acompaña del nombre de un archivo de log **ordenado por tiempo**, accesible desde el mismo
directorio donde se ejecuta el programa. Para este comando no es necesario tener en cuenta el parámetro
de memoria pasado al programa, dado que la mayoría de los campos del archivo (especialmente los de mayor longitud)
serán descartados.

*Ejemplo:* `agregar_archivo 20171025.log`

Al ejecutarse deberán procesar el archivo, y detectar posibles casos de ataques
de denegación de servicio. Si se detecta que una dirección IP realizó cinco o más
peticiones en menos de dos segundos, el comando debe alertarlo por salida
estándar como sospechosa de intento de DoS.

A la hora de detectar denegaciones de servicio, varios archivos se consideran
independientes entre sí, por lo que no se deberán memorizar entradas entre dos
ejecuciones diferentes de `agregar_archivo`.

Para alertar una IP, basta con mostrar por salida estándar `DoS: <IP>`.
Una misma dirección no deberá ser reportada más de una vez.
Si varias direcciones son sospechosas, estas deberán ser mostradas en orden
creciente.

*Ejemplo de salida:*

```
DoS: 192.168.1.4
DoS: 200.10.4.2
OK
```

### Ver visitantes

Este comando debe listar en orden a todas las IPs que realizaron alguna
petición. Sólo se mostrarán las IPs que se encuentren dentro de un rango de IPs
dado, con los límites inclusive. Como las direcciones son repartidas entre
regiones, esto puede ser útil para saber desde dónde se accede al sitio.<sup>[1](https://xkcd.com/195/)</sup>

*Ejemplo:* `ver_visitantes 62.0.0.0 62.255.255.255` mostrará todas las IPs que
empiezan con 62.

*Ejemplo de salida:*

```
Visitantes:
	62.0.0.0
	62.9.128.3
	62.10.128.3
	62.10.129.3
	62.10.129.4
	62.62.62.62
	62.255.255.255
OK
```

Notar que la salida _contiene_ el texto "`Visitantes:`" (con salto de línea luego del caracter `:`) y luego lista las IPs,
en orden, precedidas por un caracter de tabulación (`\t`), una por línea.

Consideraciones adicionales
---------------------------

### Archivos de log

Cada línea del archivo tiene la siguiente estructura:

- IP del cliente: es la IP del cliente que quiere acceder a un recurso (como el
archivo de la página principal, o un archivo, por ejemplo).
- Fecha y hora: la fecha y hora en la que se efectuó el pedido.
- El método HTTP usado: puede ser GET, POST, PUT, etc.
- La URL del recurso: es la ruta para ubicar un archivo, relativo a la raíz del
servidor.

Cada dato de una línea de log está separado por una tabulación.

Ejemplo:

```
208.115.111.72	2015-05-17T11:05:15+00:00	GET	/corrector.html
```

Además, todas las entradas en un archivo de log están registradas en orden cronológico.

Se provee una [colección de logs de ejemplo](https://drive.google.com/drive/folders/1CHCUvxaCiuMasKMsg7BfRkOyjzVECkLb).

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

Los archivos de log provistos están dados en la zona horaria UTC, por lo que
el valor del último segmento siempre será +00:00.

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

- Agregar archivo:
    - La búsqueda de DoS debe ser en  $$\mathcal{O}(n)$$ siendo $$n$$ la cantidad de líneas del
      log.
    - El mantenimiento para actualizar los visitantes debe ser  $$\mathcal{O}(n \log v)$$
      siendo $$v$$ la cantidad de visitantes en toda la historia del programa.
- Ver visitantes: debe ser  $$\mathcal{O}(v)$$ en el peor caso (en el que se tenga que
  mostrar todos los visitantes),  $$\mathcal{O}(\log v)$$ en un caso promedio (en el caso en
  el que no se pidan mostrar demasiados visitantes). $$v$$ nuevamente es la cantidad histórica de
  visitantes.
- Ordenar archivo: debe ser  $$\mathcal{O}(n \log n)$$, siendo $$n$$ la cantidad de líneas del log.


Ejemplos
--------

Se proveen ejemplos completos para mostrar la salida esperada en cada
instrucción.

### Ordenar archivo

Para la siguiente entrada:
    ordenar_archivo access001.log access001-ordenado.log

El programa, además de ordenar el archivo, debe imprimir por salida estándar `OK`:

    OK

Se espera que el archivo ordenado sea igual al original (que ya estaba ordenado):

    diff access001.log access001-ordenado.log | wc
    0

El archivo `access010.log` es el archivo `access001.log`, desordenado, así como `access011.log` es igual al archivo `access003.log`, pero desordenado:

    diff access001.log access010-ordenado.log | wc
    0
    diff access003.log access011-ordenado.log | wc
    0

Se recuerda que se pueden generar más ejemplos desordenados utilizando el comando:

    perl -MList::Util -e 'print List::Util::shuffle <>' archivo_original > archivo_desordenado

### Reporte de DoS

Para la siguiente entrada:

    agregar_archivo access001.log
    agregar_archivo access002.log

Se espera una salida como la siguiente:

    OK
    DoS: 50.139.66.106
    DoS: 67.61.65.249
    OK

En esta se reportan dos posibles ataques de DoS en el segundo archivo agregado,
`access002.log`, pero ninguno en el primero.

Notar que:

- de haberse detectado posibles DoS, deberían haberse reportado antes de los
`OK` de `agregar_archivo`.

### Ver vistantes

Para la siguiente entrada:

    ordenar_archivo access010.log access010-ordenado.log
    agregar_archivo access010-ordenado.log
    agregar_archivo access004.log
    ver_visitantes 200.49.0.0 201.30.0.0

Se espera una salida como la siguiente:

    OK
    OK
    OK
    Visitantes:
    	200.49.190.100
    	200.49.190.101
    	201.26.152.202
    OK

Notar que, igual que en el ejemplo anterior, los visitantes son reportados
cuando aparecen en alguno de los archivos agregados hasta ese momento, en orden,
según las direcciones IPs.

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
analog: tp2.c hash.o abb.o heap.o strutil.o timeutils.o
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
