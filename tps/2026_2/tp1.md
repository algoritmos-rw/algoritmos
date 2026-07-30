---
math: true
---

{% assign tp = site.data.trabajos.TP1 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

# TP1: Camino más corto en un laberinto
{:.no_toc}

El trabajo práctico número 1 tiene fecha de entrega para el día **{{fecha}}**.


## Contenido
{:.no_toc}

* Contenido
{:toc}

## Previo al enunciado

Como se ha indicado en clase, esperamos para la elaboración de este trabajo práctico que ya tengan conocimiento pleno del uso de Go, lo cual incluye todo lo visto en clase y lo explicado en [los videos sobre el lenguaje](https://youtube.com/playlist?list=PLLfC2vEod54L8O2mqE2C7cFiqmsj3rsGi). Si no se ha visto alguno de los videos, es necesario que primero lo revisen porque este enunciado asume que esto es sabido.

También, recomendamos volver a revisar [el video sobre cómo armar los módulos en Go](https://youtu.be/IZrQt-vR3E4?t=585), en particular para los TPs.


## Introducción
{: #maze}

Un _laberinto_ es una cuadrícula rectangular en la cual algunas celdas son paredes (intransitables) y otras son pasillos (transitables). Dado un laberinto con una celda de partida y una celda de llegada, el problema consiste en determinar la **mínima cantidad de pasos** necesarios para ir desde el inicio hasta el final, moviéndose únicamente entre celdas transitables y solamente en las cuatro direcciones cardinales (arriba, abajo, izquierda, derecha): no se permite el movimiento diagonal.

La estrategia que se utilizará para resolver el problema es la siguiente: se recorre el laberinto en _olas concéntricas_ a partir de la celda inicial. Es decir, se visitan primero todas las celdas alcanzables en un paso, luego todas las alcanzables en dos pasos, luego en tres, y así sucesivamente, hasta llegar a la celda final (o concluir que no es alcanzable). Para implementar este recorrido se usará una **cola** de celdas pendientes a visitar: a medida que se desencola una celda, se encolan sus vecinas transitables que aún no fueron visitadas.

Este es un buen ejercicio para apreciar el uso natural de la cola: se garantiza que la primera vez que se llega a la celda final se hace por un camino de longitud mínima.


## Resolución de laberintos

Se desea implementar un programa que reciba uno o más laberintos por entrada estándar y, para cada uno, imprima por salida estándar la longitud del camino más corto entre el inicio y el final, o `ERROR` si no existe tal camino. Ejemplo:

```Console
$ cat lab.txt
5 5
#####
#S..#
#.#.#
#..E#
#####
3 7
#######
#S#..E#
#...#.#
#######
4 4
####
#SE#
#..#
####
3 5
#####
#S#E#
#####

$ ./maze < lab.txt
5
9
1
ERROR
```


### Formato de entrada

La entrada estándar contiene una secuencia de laberintos, uno a continuación del otro. Cada laberinto se describe de la siguiente forma:

- Una primera línea con dos números enteros positivos $$F$$ y $$C$$, separados por un espacio, que indican respectivamente la cantidad de filas y columnas del laberinto.

- A continuación, $$F$$ líneas de exactamente $$C$$ caracteres cada una, donde cada caracter puede ser:

    - `#` — pared (celda intransitable),
    - `.` — pasillo (celda transitable),
    - `S` — celda de partida (transitable),
    - `E` — celda de llegada (transitable).

Se garantiza que en cada laberinto hay exactamente una celda `S` y exactamente una celda `E`. No se garantiza que el laberinto esté rodeado de paredes; el borde puede contener cualquier tipo de celda.

Tras finalizar un laberinto, puede comenzar otro inmediatamente con su correspondiente línea de dimensiones, o no. La entrada termina con el fin de archivo (EOF).


### Formato de salida

Para cada laberinto, se debe imprimir una línea por salida estándar (_stdout_) con uno de los siguientes contenidos:

- Una primera línea con un número entero no negativo, indicando la cantidad mínima de pasos necesaria para ir desde `S` hasta `E`. La celda `S` está a distancia 0 de sí misma; cada movimiento a una celda vecina cuenta como un paso. Una siguiente línea con los pasos a seguir (deberán ser la cantidad indicada anteriormente), que deben indicarse con `IZQUIERDA`, `DERECHA`, `ABAJO`, `ARRIBA` según corresponda. 

- La cadena `ERROR` si no existe ningún camino entre `S` y `E`.


### Sobre la implementación

Se pide implementar el recorrido por olas concéntricas mencionado en la introducción usando la **cola** desarrollada como TDA en clase. No se permite el uso de recursión para realizar este recorrido. El algoritmo debería funcionar en $\mathcal{O}(F * C)$. Notar que $F * C$ es igual a la cantidad de celdas, por lo que se puede ver como lineal en la cantidad de celdas de la matriz. 


### Pruebas

El curso provee pruebas que pueden descargar del sitio de descargas.
Adicionalmente, [aquí tienen un video](https://www.youtube.com/watch?v=LMYjnMB4Lj0) que explica cómo se deben ejecutar. El video hace mención a pruebas de otro trabajo práctico, pero la forma de ejecutarlas es exactamente la misma.


## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores.

La entrega incluye, obligatoriamente, todos los archivos involucrados en la realización del TP (es decir, el módulo del trabajo en sí, cuyo directorio debe llamarse si o si `tp1`, aunque el módulo en sí debería llamarse `maze`), así como el módulo `tdas` con la implementación de la cola utilizada.

La entrega se realiza únicamente en forma digital a través del [sistema de entregas]({{site.entregas}}), con todos los archivos mencionados en un único archivo ZIP.
