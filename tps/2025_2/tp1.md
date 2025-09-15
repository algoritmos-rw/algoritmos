---
math: true
---

{% assign tp = site.data.trabajos.TP1 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

# TP1: Conversión de notación infija a posfija
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
{: #dc}

Nuestra forma _usual_ de escribir operaciones matemáticas (_operador operando operador_, ejemplo 3 + 2) se llama _notación infija_. Otro tipo de notación puede ser la [notación polaca inversa][rpn-es] (también llamada _notación posfija_, en inglés [_reverse Polish notation_][rpn-en]).
Esta notación se utiliza, por ejemplo, en calculadoras financieras, especialmente de hace algunas décadas. 

Mostramos algunos ejemplos de pasaje de notación infija a posfija: 
```
3 + 2         → 3 2 +
20 / -3       → 20 -3 /
20^10         → 20 10 ^
20 * 10^5 - 2 → 20 10 5 ^ * 2 -
```

[rpn-en]: https://en.wikipedia.org/wiki/Reverse_Polish_notation
[rpn-es]: https://es.wikipedia.org/wiki/Notaci%C3%B3n_polaca_inversa

## Conversor desde notación infija


Se desea implementar un conversor de notación infija a notación posfija. El programa debe leer por entrada estándar operaciones en notación infija (una por línea), e imprimirá por salida estándar la representación en postfijo de la misma operación. Ejemplo:

```
$ cat arith.txt
3 + 5
5 - 3
8 / 2 + 1
9 - 2 * 4
(9-2) * 4
5 + 4 ^ 3 ^ 2

$ ./infix < arith.txt
3 5 +
5 3 -
8 2 / 1 +
9 2 4 * -
9 2 - 4 *
5 4 3 2 ^ ^ +
```

Como referencia bibliográfica, la conversión se puede realizar mediante el algoritmo _shunting yard_ (ver página de Wikipedia [en castellano][syard-es] o [en inglés][syard-en]).

[syard-es]: https://es.wikipedia.org/wiki/Algoritmo_shunting_yard
[syard-en]: https://en.wikipedia.org/wiki/Shunting-yard_algorithm


### Formato de entrada

Cada línea de la entrada consistirá de una secuencia de _tokens_; cada uno de ellos podrá ser:

  - uno de los cinco operadores aritméticos `+` `-` `*` `/` `^`
  - un paréntesis de apertura, `(`; o de cierre, `)`
  - un número entero, no negativo y en base decimal

Se debe aceptar espacios en blanco en cualquier punto de la expresión, excepto entre los dígitos de un valor numérico.

**Se garantiza, por último, que todas las expresiones de entrada estarán bien formadas:** paréntesis balanceados, cantidad de operadores correctos, etc.

### Asociatividad y precedencia

Todos los operadores asocian por la izquierda, excepto la exponenciación, `^`, que asocia por la derecha.

Por otra parte, `^` es el operador de mayor precedencia, seguido de `*` y `/` (ambos al mismo nivel); `+` y `-` son, ambos, los operadores de menor precedencia.


## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones de la consigna. Debe compilar sin advertencias y correr sin errores.

La entrega incluye, obligatoriamente, todos los archivos involucrados en la realización del TP (es decir, el módulo del trabajo en sí, que debe llamarse `infix`), así como el módulo `tdas` en caso de haber utilizado al menos alguno de los tipos de datos implementados anteriormente.

La entrega se realiza únicamente en forma digital a través del [sistema de entregas]({{site.entregas}}), con todos los archivos mencionados en un único archivo ZIP.
