---
title: "TP2 – analog: análisis de logs"
---

Trabajo Práctico 2
==================
{:.no_toc}

El Trabajo Práctico número 2 es de elaboración grupal, y tiene fecha de entrega
para el **lunes 13/11**.

Contenido
---------
{:.no_toc}

* Contenido
{:toc}


Introducción
------------

<p style="text-align: center;">
    <img src="{{ 'assets/tps/2017_2/tp2/uma1.png' | relative_url }}" width="200">
    <img src="{{ 'assets/tps/2017_2/tp2/uma2.png' | relative_url }}" width="250">
</p>


Una cierta materia de una prestigiosa Universidad de Música ha puesto a
disposición un corrector automático de partituras. Puesto que los docentes a
cargo del curso no tienen demasiada experiencia en programación de sistemas web,
la decenas de visitas diarias al sitio han hecho que los servidores se caigan.

Como cada acceso al sistema queda registrado, los músicos han buscado ayuda a
estudiantes de Algoritmos y Programación II con mucha experiencia en manejo de
archivos y entrada estándar en C.

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

- `agregar_archivo <nombre_archivo>`: procesa de forma completa un archivo de
log.
- `ver_visitantes <desde> <hasta>`: muestra todas las IPs que solicitaron algún
recurso en el servidor, dentro del rango de IPs determinado.
- `ver_mas_visitados <n>`: muestra los _n_ recursos más solicitados.

Si un comando es válido deberá imprimir `OK` por salida estándar después de ser
ejecutado.
Si un comando no pertenece a los listados previamente o tiene un error, se
imprime `Error en comando <comando>` por `stderr` y se finaliza la ejecución.

El programa no tendrá un comando para terminar. Este finaliza cuando no quedan
más líneas para procesar por entrada estándar. Al finalizar, es importante que
libere toda la memoria dinámica utilizada, y cierre correctamente todos los
archivos procesados.

### Agregar archivo

El comando se acompaña del nombre de un archivo de log, accesible desde el mismo
directorio donde se ejecuta el programa.

*Ejemplo:* `agregar_archivo 20171025.log`

Al ejecutarse deberán procesar el archivo, y detectar posibles casos de ataques
de denegación de servicio. Si se detecta que una dirección IP realizó cinco o más
peticiones en menos de dos segundos, el comando debe alertarlo por salida
estándar como sospechosa de intento de DoS.

A la hora de detectar denegaciones de servicio, varios archivos se consideran
independientes ente sí, por lo que no se deberán memorizar entradas entre dos
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

Notar que la salida _contiene_ el texto "`Visitantes:`" y luego lista las IPs,
en orden, precedidas por un caracter de tabulación (`\t`), una por línea.

### Ver más visitados

Este comando mostrará los _n_ recursos más solicitados. Esta información suele
ser útil para analizar cuales son las páginas más visitadas a nivel global.

*Ejemplo:* `ver_mas_visitados 10` mostrará los 10 recursos más solicitados, para
todos los logs analizados. Los sitios se muestran ordenados comenzando por el de
mayor cantidad de solicitudes, separado con un guión a la cantidad. En caso de
empate se pueden mostrar en cualquier orden.

*Ejemplo de salida:*

```
Sitios más visitados:
	/algo2/tps/2017_2/tp1 - 57
	/algo2/faq/ - 35
	/algo2/guias/grafos - 25
OK
```

Notar que la salida _contiene_ el texto "`Sitios más visitados:`" y luego lista
los recursos, en orden según visitas, precedidas por un caracter de tabulación
(`\t`), uno por línea junto con la cantidad.


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

Se provee una colección de logs de ejemplo
[aquí](https://drive.google.com/drive/folders/0B0x0VPz_v-f_UENLUnVCMlBiWUE?usp=sharing).


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

``` cpp
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
    - La búsqueda de DoS debe ser en _O(n)_ siendo _n_ la cantidad de líneas del
      log.
    - El mantenimiento para actualizar los sitios más visitados también debe ser
      _O(n)_.
    - El mantenimiento para actualizar los visitantes debe ser _O(n log V)_
      siendo _V_ la cantidad de visitantes en toda la historia del programa.
- Ver más visitados: debe ser _O(S log k)_ siendo _S_ la cantidad diferentes de
  sitios en toda la historia y _k_ el parámetro
- Ver visitantes: debe ser _O(V)_ en el peor caso (en el que se tenga que
  mostrar todos los visitantes), _O(log V)_ en un caso promedio (en el caso en
  el que no se pidan mostrar demasiados visitantes). _V_ nuevamente es la
  cantidad histórica de visitantes.


Ejemplos
--------

Se proveen ejemplos completos para mostrar la salida esperada en cada
instrucción.

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

### Ver más visitados

Para la siguiente entrada:

    agregar_archivo access001.log
    agregar_archivo access004.log
    ver_mas_visitados 3

Se espera una salida como la siguiente:

    OK
    OK
    Sitios más visitados:
    	/favicon.ico - 144
    	/ - 129
    	/style2.css - 116
    OK

Notar que:

- de haberse detectado posibles DoS, deberían haberse reportado antes de los
`OK` de `agregar_archivo`.
- los sitios más visitados se totalizan sumando los dos archivos agregados hasta
el momento.
- los sitios más visitados son reportados en orden según su frecuencia.

### Ver vistantes

Para la siguiente entrada:

    agregar_archivo access001.log
    agregar_archivo access004.log
    ver_visitantes 200.49.0.0 201.30.0.0

Se espera una salida como la siguiente:

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

El corrector automático va a interpretar ese archivos de dependencias y va a
compilar todos los `.o` especificados a partir de los `.h` y `.c` que deberán
enviar, con los siguientes flags de GCC:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. en forma digital a través del [sistema de entregas](http://entregas.algoritmos7541-rw.tk),
con todos los archivos mencionados en un único archivo ZIP.
2. en papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, informe ni carátula**. No es necesario
reimprimir el código de los TDA ni de `strutil`.
