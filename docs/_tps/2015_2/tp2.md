---
title: Trabajo práctico n.º 2
cursada: 2015/2
deadline: 2015-11-13
---

Introducción
============

En Suiza, la clínica _Zyxcba Inc._{: style="font-variant: small-caps"} utiliza
un mecanismo de contribuciones para organizar sus listas de espera. Así, dentro
de cada especialidad se da prioridad a aquellos pacientes que, además de sus
cuotas mensuales, más “donativos voluntarios” realizaron a las arcas de la
clínica.

Para celebrar el 70 aniversario de la clínica, _Zyxcba Inc._{:
style="font-variant: small-caps"} utiliza ha decidido remplazar la
implementación actual del sistema de gestión en COBOL por una más moderna en C.


Funcionamiento de la clínica
============================

Existe un listado de todos los pacientes de la clínica en formato CSV; este
listado incluye el monto de las contribuciones monetarias de cada uno.

Asimismo, existe otro listado CSV de todos los doctores, y la especialidad de
cada uno.

Los pacientes pueden pedir turno para una determinada especialidad, y el
sistema los añade a la lista de espera correspondiente a esa especialidad.

Cuando un doctor queda libre, atiende al paciente con mayor monto de
contribuciones de entre todos los que están en espera para su especialidad.


Consigna
========

Se pide implementar el sistema de gestión de turnos y generación de informes de
la clínica.

Cuando el sistema arranca, carga en memoria la lista de pacientes y la lista de
doctores. A partir de ese momento, lee de entrada estándar las operaciones a
realizar, tal y como se detalla a continuación.

Tras cada operación, el sistema siempre imprime por pantalla un mensaje,
informando de los resultados, o cualquier error que haya ocurrido.


Entradas al programa
--------------------

El programa recibe como argumentos (CLA) el nombre de **dos archivos en formato
CSV**:

1.  Archivo CSV con la lista de doctores. Tiene dos columnas: el nombre y la
    especialidad. Así:

        nombre_doctor1,nombre_especialidad_A
        nombre_doctor2,nombre_especialidad_B
        nombre_doctor3,nombre_especialidad_A

    Como se ve, cada doctor tiene solo una especialidad, pero una especialidad
    puede tener varios doctores.

2.  Archivo CSV con la lista de pacientes. Tiene también dos columnas: el
    nombre y el monto de contribuciones. Así:

        nombre_paciente1,total_contribuciones
        nombre_paciente2,total_contribuciones


Garantías (pre-condiciones):

  - no hay nombres duplicados dentro de cada archivo (aunque un doctor y un
    paciente sí podrían llamarse igual).

  - los nombres de doctor, nombre y especialidad no contienen ninguno de los
    siguientes caracteres: coma `','`, dos puntos `':'`, salto de línea `'\n'`,
    carácter nulo `'\0'`.

  - los montos de contribuciones son números enteros positivos en base 10, y
    ningún paciente contribuyó más de $$2^{64} - 1$$ pesos.


Interacción
-----------

Una vez en marcha, el sistema queda a la espera de instrucciones, que le llegan
por entrada estándar.

Una instrucción se compone de un comando y sus parámetros. El formato siempre
es: nombre del comando, carácter dos puntos `':'` y parámetros del comando. Así:

	CMD1:ARG_A
	CMD2:ARG_B,ARG_C

Como se ve, un comando puede tener más de un parámetro, separados por comas.

Una vez procesada la operación, el sistema imprimirá el resultado, o bien un
mensaje de error si no la pudo completar. Tanto el resultado como los mensajes
de error se imprimen siempre por salida estándar.[^1]

Mensajes de error:

  - Si una instrucción no sigue el formato `NOMBRE_COMANDO:PARAMETROS`, el
    sistema imprime el siguiente mensaje de error:

	ERROR: formato de comando incorrecto

  - Si el formato es correcto pero no existe el comando, el sistema imprime:

	ERROR: no existe el comando 'NOMBRE_CMD:PARAMETROS'

[^1]: El programador puede por tanto utilizar la salida de error estándar para
      mensajes de depurado o _debugging_. Estos mensajes, no obstante, no deben
      quedar en el programa final.


Comandos
--------

El sistema implementa los tres comandos que se detallan a continuación.


### 1. Pedir turno

Se recibe el nombre de un paciente y el nombre de una especialidad, y el
sistema añade al paciente a la lista de espera de la especialidad
correspondiente.

Formato:

	PEDIR_TURNO:NOMBRE_PACIENTE,NOMBRE_ESPECIALIDAD

Salida (dos líneas):

	Paciente NOMBRE_PACIENTE encolado
	N paciente(s) en espera para NOMBRE_ESPECIALIDAD

Mensajes de error, cuando corresponda:

	ERROR: no existe el paciente 'NOMBRE_PACIENTE'
	ERROR: no existe la especialidad 'NOMBRE_ESPECIALIDAD'

Garantías (pre-condiciones):

  - un paciente nunca solicitará turno para una especialidad si ya está en la
    lista de espera de la misma. No obstante, puede estar simultáneamente en la
    lista de espera de dos o más especialidades distintas.


### 2. Atender siguiente paciente

Se recibe el nombre del doctor que quedó libre, y este atiende al paciente de
mayor contribución de entre los que esperan para su especialidad.

Formato:

	ATENDER_SIGUIENTE:NOMBRE_DOCTOR

Salida si se atendió a un paciente (dos líneas):

	Se atiende a NOMBRE_PACIENTE
	N paciente(s) en espera para NOMBRE_ESPECIALIDAD

donde _N_ es el número de pacientes que quedaron en espera tras atender al
paciente actual (que puede ser 0).

Salida si no había previamente pacientes en la lista de espera (una línea):

	No hay pacientes en espera

Mensajes de error, cuando corresponda:

	ERROR: no existe el doctor 'NOMBRE_DOCTOR'


### 3. Informe doctores

El sistema imprime la lista de doctores **en orden alfabético**, junto con su
especialidad y el número de pacientes que atendieron desde que arrancó el
sistema.

Formato:

	INFORME:DOCTORES

(Literalmente `“INFORME:DOCTORES”`; en este caso el argumento del comando es
siempre el mismo para este tipo de informe.)

Salida (_N + 1_ líneas, donde _N_ es el número de doctores en el sistema):

	N doctor(es) en el sistema
	1: NOMBRE, especialidad ESPECIALIDAD, X paciente(s) atendido(s)
	2: NOMBRE, especialidad ESPECIALIDAD, Y paciente(s) atendido(s)
	...
	N: NOMBRE, especialidad ESPECIALIDAD, Z paciente(s) atendido(s)


Mensajes de error
-----------------

Para facilitar los mensajes de la aplicación sean _exactamente_ los
especificados, se proporciona un archivo _[mensajes.h]_ que contiene las
definiciones de todos los mensajes, tal que:

	#define PACIENTE_ENCOLADO "Paciente %s encolado\n"
	#define ENOENT_DOCTOR "ERROR: no existe el doctor '%s'\n"
	// etc.

La manera de usarlos, entonces, es:

	#include "mensajes.h"
	#include <stdio.h>

	printf(PACIENTE_ENCOLADO, "Ingeniero Garay");

Si hay alguna discrepancia entre esta consigna y el archivo _mensajes.h_, este
último es la versión canónica.

[mensajes.h]: https://github.com/algoritmos-rw/tps41/blob/2015_2/tp2/mensajes.h


Otras condiciones de error
--------------------------

El sistema aborta con código numérico 1 ante cualquiera de los siguientes
errores **durante la fase de inicialización**:

  - no se recibieron exactamente dos argumentos por la línea de comandos;

  - alguno de los archivos CSV no existe, o no pudo ser leído;

  - algún monto no es un valor numérico.


Funciones auxiliares de la cátedra
----------------------------------

Además del archivo _mensajes.h_ ya mencionado, en el [directorio tp2] del
repositorio se proporcionan dos archivos auxiliares, _csv.h_ y _csv.c_, para
ayudar con la lectura tanto de los archivos CSV, como de los comandos. Su uso
es opcional; el alumno puede emplear sus propias funciones de lectura, o las
proporcionadas por la cátedra en TPs anteriores.

[directorio tp2]: https://github.com/algoritmos-rw/tps41/blob/2015_2/tp2/


Criterios de aprobación
=======================

Los siguientes aspectos son condición necesaria para la aprobación del trabajo
práctico.

Estructuras de datos
--------------------

Es necesario emplear la estructura de datos más apropiada para cada función del
programa, en particular teniendo en cuenta la complejidad temporal.

Todas las estructuras deben estar implementadas de la forma más genérica
posible y correctamente documentadas. En general, pueden emplear sin modificar
los tipos implementados en entregas anteriores en la materia.

Código del programa
-------------------

El código entregado debe:

- ser claro y legible, y estar estructurado en funciones lo más genéricas
  posible, adecuadamente documentadas.

- compilar sin advertencias y correr sin errores de memoria.

- ajustarse a la especificación de la consigna y pasar todas las pruebas
  automáticas.


Informe
=======

El informe deberá consistir de las siguientes partes:

- carátula con los datos personales del grupo y el ayudante asignado.

- análisis y diseño de la solución, en particular: algoritmos y estructuras de
  datos utilizados, y por qué. Orden de ejecución de cada etapa del programa.

- implementación: incluir todo el código fuente utilizado (en formato
  monoespaciado, para facilitar su lectura).


Entrega
=======

El trabajo a entregar consiste en:

- el informe impreso.

- el informe en formato `.pdf`. Para el código fuente utilizar una tipografía
  `monoespacio`.

- una copia de todo el código fuente, en un archivo `.zip`.

Los dos últimos deben enviarse a la dirección `tps.7541rw@gmail.com`, colocando
como asunto:

	TP1 - Padrón 1 - Apellido 1 - Padrón 2 - Apellido 2

Este trabajo práctico se desarrolla en forma grupal. El informe impreso debe
entregarse en clase. El plazo de entrega vence el **viernes 13 de noviembre de
2015**.
