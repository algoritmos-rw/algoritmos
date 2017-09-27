---
layout: page
title: TP1 – Wachencoin
permalink: '/tps/2017_2/tp1'
---

Trabajo práctico 1
================
{:.no_toc}

Contenido
---------
{:.no_toc}

* Contenido
{:toc}

El trabajo práctico está divido en dos partes, si bien están relacionadas:
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
entrada estándar los siguientes comandos:       

* `agregar_pago <id_pago> <monto> <código>`, que agregará a la cola de 
procesamiento la transacción. El código se manifiesta en una sola línea, 
separando las distintas instrucciones con el caracter punto y coma (`;`). 
* `pagos_pendientes`: devuelve la cantidad y monto total de los pagos sin 
procesar. 
* `procesar <numero>`: procesa hasta un número de pagos pendientes. 
* `guardar_cuentas <archivo>`: guarda en un archivo el estado *actual* de las
cuentas. 
* `finalizar`: finaliza el programa (si quedan pagos sin procesar, no se 
procesan).

### Código de pago

Como Bitcoin, en Wachencoin los códigos de pago se escriben utilizando un 
lenguaje de pila¹ de la siguiente forma:

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

(**nota**: arriba está escrito en varias líneas por claridad; en realidad
el código se escribe en una sola línea separada por el caracter `;` -- ver
ejemplos abajo.)  

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

Además, cada instrucción puede **terminar** la ejecución del programa si 
devuelve algún error. Esto es particularmente importante para las funciones
de validación; si algún chequeo no se cumple, entonces se termina el 
programa y no se realiza el pago.   


**Restricciones sobre la complejidad**: todas las operaciones del lenguaje de 
pila deben ser _O(1)_. La operación de agregar un pago debe ser _O(1)_, la de
pagos pendientes _O(P)_ siendo P la cantidad de transacciones sin procesar, 
y la de guardar cuentas debe ser _O(C)_ (con C la cantidad de cuentas).   


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

El siguiente es un ejemplo de una ejecución bien formada:

```
agregar_pago 1 10.00 1;916f4c31aaa;validar_usuario;1;10.00;validar_pago;10.00;0;1;pagar
procesar 1
guardar_cuentas cuentas_out.csv
finalizar
```

Con un archivo de cuentas inicial como el siguiente:

```
0,13.37,14f6c9dae22
1,21.12,916f4c31aaa
```

El programa:

1. Agrega un pago pendiente del usuario 1 al usuario 0 por el monto de 10
rositas.
2. Procesa el pago.
3. Guarda el estado de las cuentas en el archivo `cuentas_out.csv`.
4. Finaliza la ejecución.


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


-----

¹ el atento lector se habrá dado cuenta de que no es necesario utilizar un
lenguaje de pila para realizar los pagos. Sin embargo, el propósito del TP
es *implementar* ese lenguaje de pila, y utilizarlo para realizar pagos 
-- no al revés.
