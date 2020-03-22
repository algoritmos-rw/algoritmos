---
title: TP1 – Wachencoin
---

Trabajo Práctico 1
==================
{:.no_toc}

Contenido
---------
{:.no_toc}

* Contenido
{:toc}

El Trabajo Práctico número 1 tiene fecha de entrega para el **viernes 13/10**, y
está divido en dos partes, si bien están relacionadas:
* implementación de funciones auxiliares para cadenas (`strutil`)
* implementación de un sistema similar a Bitcoin (*Wachencoin*)


strutil
-------
Se pide implementar las funciones del archivo
[strutil.h]({{ 'assets/tps/2017_2/tp1/strutil.h' | relative_url }}) que
se describen a continuación. Para la implementación de estas funciones no se
puede hacer uso de TDAs:

### split()

La función `split()` divide una cadena en subcadenas en cada ocurrencia de un
caracter de separación determinado. Por ejemplo, separando por comas:

``` cpp
split("abc,def,ghi", ',')  →  ["abc", "def", "ghi"]
```

En C, devolveremos el resultado como un arreglo dinámico de cadenas dinámicas
terminado en `NULL`. Esto es:

``` cpp
// Ejemplo de arreglo dinámico de cadenas
char **strv = malloc(sizeof(char*) * 4);
strv[0] = strdup("abc");
strv[1] = strdup("def");
strv[2] = strdup("ghi");
strv[3] = NULL;
```

El prototipo y la documentación de `split()` queda en:

``` cpp
/*
 * Devuelve en un arreglo dinámico terminado en NULL con todos los subsegmentos
 * de 'str' separados por el carácter 'sep'. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinámicamente.
 *
 * Quien llama a la función toma responsabilidad de la memoria dinámica del
 * arreglo devuelto. La función devuelve NULL si falló alguna llamada a
 * malloc(), o si 'sep' es '\0'.
 */
char** split(const char* str, char sep);
```

Considerar los siguientes casos borde:

``` cpp
split("abc,,def", ',')  →  ["abc", "", "def"]
split("abc,def,", ',')  →  ["abc", "def", ""]
split(",abc,def", ',')  →  ["", "abc", "def"]

split("", ',')  →  [""]
split(",", ',') →  ["", ""]
```

### free_strv()

`free_strv()` libera la memoria asociada con un arreglo dinámico de cadenas dinámicas:

``` cpp
/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char *strv[]);
```


Interludio: Bitcoin
-------------------
**Bitcoin** es un sistema de pagos digital descentralizado que no requiere un
respaldo externo (en billetes, por ejemplo) del dinero que utiliza.

En Bitcoin y sus derivados, los pagos son en realidad programas (*scripts*)
que se escriben en un *lenguaje de pila*.
Un lenguaje de pila opera básicamente de dos formas: apilando y desapilando
datos del stack, para poder usar funciones sobre ellos. Un ejemplo puede ser
la [notación polaca inversa](http://www-stone.ch.cam.ac.uk/documentation/rrf/rpn.html)
que se utilizaba en las antiguas calculadoras digitales.

**¡A no desesperar!** Aunque Bitcoin tiene muchas decisiones de diseño
para garantizar transferencias seguras y válidas entre los miembros de
la red, en este TP sólo nos interesan las estructuras de datos que
pueden ser útiles en un sistema de este estilo.

Wachencoin
----------

<p style="text-align: center;">
    <img src="{{ 'assets/tps/2017_2/tp1/logo.png' | relative_url }}">
</p>

Implementaremos un programa que permita realizar pagos entre los usuarios
de la red y mantenga el estado de los saldos de sus billeteras. Cada
usuario será identificado unívocamente por un identificador numérico y tendrá
asociada una coordenada que hará las funciones de contraseña.

*Curiosidad*: la unidad más pequeña del sistema Bitcoin se llama *satoshi*, por
su creador. Parece justo, entonces, llamar a la unidad de Wachencoin un
*rosita*.

La ejecución de la aplicación recibe como parámetro el nombre de un archivo
[csv](https://en.wikipedia.org/wiki/Comma-separated_values)
con el estado inicial de las cuentas (número, saldo, coordenadas), que tiene el
siguiente formato:

```
0,13.37,14f6c9dae22
1,58.92,916f4c31aaa
2,9301.92,e9a7f54270d
(...)
```

Los números de cuenta son consecutivos empezando desde 0.

### Interfaz

Es necesario implementar una **interfaz** del programa, que leerá por entrada
estándar los siguientes comandos:

* `agregar_pago <id_pago> <monto> -código de pago-`, que agregará a la cola de
procesamiento la transacción. El monto es siempre positivo. El formato del
código de pago se detalla debajo.
* `pagos_pendientes`: imprime por `stdout` la cantidad y el monto total de los
pagos pendientes, separados por una coma.
* `procesar <numero>`: procesa hasta un número no negativo de pagos pendientes.
* `guardar_cuentas <archivo>`: guarda en un archivo el estado *actual* de las
cuentas. Si no existe lo debe crear, y si existe lo sobreescribe.
* `finalizar`: finaliza el programa (si quedan pagos sin procesar, no se
procesan).

*Nota*: recomendamos usar el siguiente formato para la impresión de números
decimales en C: `%.3f`, que imprime el número redondeado a tres decimales.

### Código de pago

Como Bitcoin, en Wachencoin los códigos de pago (también llamados _scripts_) se
escriben utilizando un lenguaje de pila¹ como el siguiente:

```
<id_usuario_1>
<coordenadas_usuario_1>
validar_usuario
<id_usuario_1>
<monto>
validar_pago
<monto>
<id_usuario_2>
<id_usuario_1>
pagar
```

Las distintas instrucciones del código de pago se ingresan en **una línea**
separadas por `;`, por ejemplo:

```
0;14f6c9dae22;validar_usuario;0;5.00;validar_pago;5.00;3;0;pagar
```

Que corresponde a un pago del usuario 0 de coordenadas 14f6c9dae22
de 5 rositas para el usuario 3.

Para clarificar, marcamos las siguientes operaciones:

* `validar_usuario`: desapila dos elementos y revisa que las coordenadas
sean apropiadas para el usuario.
* `validar_pago`: desapila dos elementos y revisa que el usuario tenga
fondos suficientes para hacer la operación.
* `pagar`: desapila tres elementos y hace el movimiento de fondos.
* por defecto: empuja un dato al stack.

**Atención**: Si bien la de arriba es una transacción bien escrita, no es
la *única* posible. También habrá transacciones que hacen pagos a múltiples
personas; o de varias personas a una sola.

**Restricciones sobre la complejidad**: todas las operaciones del lenguaje de
pila deben ser _O(1)_. La operación de agregar un pago debe ser _O(1)_, la de
pagos pendientes _O(P)_ siendo P la cantidad de transacciones sin procesar,
y la de guardar cuentas debe ser _O(C)_ (con C la cantidad de cuentas).

### Manejo de errores y precondiciones

Para este Trabajo Práctico se podrá considerar:

- Que el monto total de un comando `agregar_pago` es correcto. Es decir: que
correctamente simboliza la suma de las transacciones que se van a realizar en el
código.
- Que todos los montos son flotantes positivos.

La implementación deberá manejar correctamente los siguientes casos de error:

- Error 1: cuando un código de pila tiene un error. Por ejemplo:
    - Id de usuario inexistente.
    - Las coordenadas de un usuario son inválidas.
    - El usuario no tiene saldo suficiente.
- Error 2: cuando un comando es inválido. Por ejemplo:
    - Se encuentra una cadena de texto cuando se espera un número entero.
    - Hay parámetros de más.
    - Faltan parámetros.
    - El comando no existe.

En caso de error 1, el programa deberá imprimir por `stderr`: `Error en pago <id>`
con el id de pago inválido. Queda a elección de ustedes decidir si el resto de
los pagos del código se procesaran o no.

En caso de error 2, el programa deberá imprimir por `stderr`: `Error en comando <nombre>`
con el nombre del comando que falló. Un error de tipo 2 hará que termine la
ejecución del programa.

En caso de que un comando no tenga errores de tipo 2 deberá imprimir `OK` por
`stdout`. Esta cadena deberá ser lo último impreso por la aplicación en caso de
error.

### Diseño

Se recomienda usar las siguientes estructuras para almacenar los usuarios y los
pagos:

``` cpp
typedef struct usuario {
	size_t id;
	char* coordenadas;
	double saldo;
} usuario_t;
```

``` cpp
typedef struct pago {
	size_t id;
	char* codigo;
	double monto;
} pago_t;
```

### Ejemplos

Los siguientes ejemplos son tomados a partir de un archivo de cuentas inicial
como el siguiente:

```
0,23.37,14f6c9dae22
1,5.12,916f4c31aaa
2,5.14,c353bcb74b3
```

#### Con una transacción con un pago

El siguiente es un ejemplo de una ejecución bien formada:

```
agregar_pago 1 5.00 1;916f4c31aaa;validar_usuario;1;5.00;validar_pago;5.00;0;1;pagar
procesar 1
guardar_cuentas cuentas_out.csv
finalizar
```

El programa:

1. Agrega un pago pendiente del usuario 1 al usuario 0 por el monto de 5
rositas.
2. Procesa el pago.
3. Guarda el estado de las cuentas en el archivo `cuentas_out.csv`.
4. Finaliza la ejecución.

Al finalizar esta ejecución se espera que por salida estándar se imprima:

```
OK
OK
OK
OK
```

#### Con una transacción con dos pagos

El siguiente ejemplo realiza dos transacciones en un mismo código de pago:

```
agregar_pago 1 10.02 0;14f6c9dae22;validar_usuario;1;916f4c31aaa;validar_usuario;0;5.22;validar_pago;1;4.80;validar_pago;5.22;2;0;pagar;4.80;2;1;pagar
procesar 1
guardar_cuentas cuentas_out.csv
finalizar
```

El programa:

1. Agrega un pago pendiente del usuario 0 al usuario 2 por el monto de 5,22
rositas; y un pago pendiente de 4,80 rositas del usuario 1 al usuario 2.
2. Procesa el pago (que ejecutará las dos transacciones).
3. Guarda el estado de las cuentas en el archivo `cuentas_out.csv`.
4. Finaliza la ejecución.

La salida esperada en este caso es:

```
OK
OK
OK
OK
```

#### Con un código de pago inválido

El siguiente ejemplo es inválido por tener mal las coordenadas del usuario 1:

```
agregar_pago 1 10.00 1;fd36fbf2562;validar_usuario;1;10.00;validar_pago;10.00;0;1;pagar
procesar 1
finalizar
```

Deberá producir la siguiente salida (teniendo en cuenta lo mostrado por `stdout`
y por `stderr`):

```
OK
Error en pago 1
OK
OK
```

#### Con un comando inválido

El siguiente ejemplo es inválido por faltarle un parámetro al comando
`procesar`:

```
agregar_pago 1 5.00 1;916f4c31aaa;validar_usuario;1;5.00;validar_pago;5.00;0;1;pagar
procesar
guardar_cuentas cuentas_out.csv
finalizar
```

Deberá producir la siguiente salida (teniendo en cuenta lo mostrado por `stdout`
y por `stderr`)::

```
OK
Error en comando procesar
```

Y deberá terminar la ejecución sin ejecutar los últimos dos comandos.

#### Con un comando inexistente

La siguiente serie de comandos incluye uno que es inexistente:

```
agregar_pago 1 5.00 1;916f4c31aaa;validar_usuario;1;5.00;validar_pago;5.00;0;1;pagar
imprimir_deudas 4
procesar 2
finalizar
```

Deberá producir la siguiente salida (teniendo en cuenta lo impreso por `stdout`
y `stderr`):

```
OK
Error en comando imprimir_deudas
```

Y deberá terminar la ejecución sin ejecutar los últimos dos comandos.

#### Con impresión de pagos pendientes

La siguiente serie de comandos:

```
agregar_pago 1 10.02 0;14f6c9dae22;validar_usuario;1;916f4c31aaa;validar_usuario;0;5.22;validar_pago;1;4.80;validar_pago;5.22;2;0;pagar;4.80;2;1;pagar
pagos_pendientes
finalizar
```

Deberá producir la siguiente salida:

```
OK
1,10.02
OK
OK
```

Anexo: más información y links
------------------------

Esta implementación de *Wachencoin* es bastante sencilla pero introduce
algunos conceptos fundamentales de criptomonedas. A continuación se enumeran
recursos que permiten entender otros conceptos involucrados no incluídos en
el TP y para nada necesarios para su resolución:

* [Double spending problem](https://en.wikipedia.org/wiki/Double-spending)
* [Funciones de hash SHA](https://es.wikipedia.org/wiki/SHA-2)
* [Arbol de Merkle](https://en.wikipedia.org/wiki/Merkle_tree)
* [Criptografía de clave pública](https://www.youtube.com/watch?v=GSIDS_lvRv4)
* [Criptografía con RSA](http://pub.gajendra.net/2012/09/an_explanation_of_the_rsa_cryptosystem)
* [Majority Rule](http://hackingdistributed.com/2014/06/19/bitcoin-and-voting-power/)
* [Ejemplos de programas en Bitcoin Scripting Language](https://en.bitcoin.it/wiki/Transaction#Pay-to-PubkeyHash)


Criterios de aprobación
------------------------

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores de memoria.

La entrega incluye, obligatoriamente, los siguientes archivos de código:

- `strutil.c` con las implementaciones de las funciones `split` y `free_strv`.
- el código de la solución de wachencoin.
- el código de los TDAs programados en la cursada que se requieran, con las
modificaciones que sean necesarias.
- un archivo `deps.mk` con las dependencias del proyecto en formato make. Este
deberá contener sólamente una línea que indique qué _objetos_ necesita para
compilar el ejecutable wachencoin, por ejemplo:

``` makefile
wachencoin: tp1.c vector.o pila.o lista.o strutil.o
```

El corrector automático va a interpretar ese archivos de dependencias y va a
compilar todos los `.o` especificados a partir de los `.h` y `.c` que deberán
enviar, con los siguientes flags de GCC:

```
-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
```

La entrega se realiza:

1. en forma digital a través del [sistema de entregas](http://entregas.algoritmos7541-rw.tk):
todos los archivos mencionados en un único archivo ZIP.
2. en papel durante la clase (si su ayudante lo requiere) el código del Trabajo
en hoja A4 **abrochadas, sin folio, informe ni carátula**. No es necesario
reimprimir el código de los TDA.


-----

¹ el atento lector se habrá dado cuenta de que no es necesario utilizar un
lenguaje de pila para realizar los pagos. Sin embargo, el propósito del TP
es *implementar* ese lenguaje de pila, y utilizarlo para realizar pagos
-- no al revés.
