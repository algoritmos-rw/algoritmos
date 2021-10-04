---
math: true
---

{% assign tp = site.data.trabajos.TP1 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

# TP1: Manejo de archivos
{:.no_toc}

El trabajo práctico número 1 tiene fecha de entrega para el día **{{fecha}}**.
El objetivo de este trabajo práctico es implementar un programa sencillo, utilizando archivos, 
flujos y demostrando saber modularizar un programa. 

## fixcol

Se pide implementar una utilidad llamada `fixcol`, que dado un tamaño `n` en bytes y el nombre de un archivo, divida todas las líneas del archivo en columnas de hasta `n` columnas y las imprima por salida estándar. Por ejemplo:

    $ cat lorem.txt
    Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi aliquip ex ea commodo consequat.
    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.

El programa deberá producir la siguiente salida (por salida estándar) al ser invocado:

    $ ./fixcol 75 lorem.txt
    Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod te
    mpor incididunt ut labore et dolore magna aliqua.
    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ali
    quip ex ea commodo consequat.
    Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolor
    e eu fugiat nulla pariatur.

En caso que no se indique el parámetro del nombre del archivo, el archivo a separar será la entrada estándar.
por lo tanto, los resultados de las siguientes operaciones deben ser equivalentes: 

	$ ./fixcol 75 lorem.txt > fixed.txt
	$ ./fixcol 75 < lorem.txt > fixed2.txt
	# ambas salidas son iguales:
	$ diff fixed.txt fixed2.txt | wc
	       0       0       0

Con las siguientes consideraciones:

  - Se deberá validar que la cantidad de parámetros en la invocación sea exactamente uno o dos.
  - En caso de error en los parámetros (sea por cantidad de parámetros, o porque el primer
    parámetro no es un número) se deberá imprimir por salida de error estándar `Error: Cantidad erronea de parametros`.
  - En caso de contar con parámetro para el archivo, en caso que hubiera un error para usar el archivo
    para lectura (no existe, no hay permisos, etc...), se deberá escribir por salida de error estándar
    `Error: Error: archivo fuente inaccesible`.
  - No se podrá considerar que entra todo el archivo a dividir en memoria.
  

## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

  - el código de `fixcol` en _fixcol.c_.

  - un archivo _deps.mk_ que exprese las dependencias del proyecto en formato
    makefile. Este archivo deberá contener solamente una línea que indiquen,
    para cada programa, de qué _objetos_ depende su ejecutable; por ejemplo:

    ```
    # Ejemplo de archivo deps.mk para el TP1
    fixcol: fixcol.o pila.o cola.o
    ```

La entrega se realiza únicamente en forma digital a través del [sistema de
entregas]({{site.entregas}}), con todos los archivos mencionados en un único
archivo ZIP.
