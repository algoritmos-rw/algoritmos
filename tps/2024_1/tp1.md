---
math: true
---

{% assign tp = site.data.trabajos.TP1 %}
{% capture fecha %}{{tp.entrega | date: "%e/%m"}}{% endcapture %}

# TP1: Calculadora Polaca Inversa
{:.no_toc}

El trabajo práctico número 1 tiene fecha de entrega para el día **{{fecha}}**.


## Contenido
{:.no_toc}

* Contenido
{:toc}


## Calculadora en notación posfija
{: #dc}

Se pide implementar un programa `dc` que permita realizar operaciones matemáticas. La calculadora leerá exclusivamente de **entrada estándar** (no toma argumentos por línea de comantos), interpretando cada línea como una operación en [notación polaca inversa][rpn-es] (también llamada _notación posfija_, en inglés [_reverse Polish notation_][rpn-en]); para cada línea, se imprimirá por salida estándar el resultado del cálculo.

Ejemplo de varias operaciones, y su resultado:

```
$ cat oper.txt
5 3 +
5 3 -
5 3 /
3 5 8 + +
3 5 8 + -
3 5 - 8 +
2 2 + +
0 1 ?
1 -1 0 ?
5 sqrt

$ ./dc < oper.txt
8
2
1
16
-10
6
ERROR
ERROR
-1
2
```

[rpn-en]: https://en.wikipedia.org/wiki/Reverse_Polish_notation
[rpn-es]: https://es.wikipedia.org/wiki/Notaci%C3%B3n_polaca_inversa


### Funcionamiento

- Todas las operaciones trabajarán con números enteros, y devolverán números enteros. Se recomienda usar el tipo de Go `int64` para permitir operaciones de más de 32 bits (p.ej. $$3^{3^3}$$).


- El conjunto de operadores posibles es: suma(`+`), resta(`-`), multiplicación(`*`), división entera(`/`), raíz cuadrada (`sqrt`), exponenciación(`^`), logaritmo (`log`) en base arbitraria, y operador ternario(`?`).

  - <!-- https://github.com/gettalong/kramdown/issues/486 -->

    Todos los operadores funcionan con dos operandos, excepto `sqrt` (toma un solo argumento) y el operador ternario (toma tres).

- Tal y como se describe en la bibliografía enlazada, cualquier operación aritmética _a op b_ se escribe en postfijo como `a b op`{:.nowrap} (por ejemplo, `3 - 2` se escribe en postfijo como `3 2 -`{:.nowrap}).

  - <!-- gettalong/kramdown#486 -->

    Para operaciones con un solo operando, el formato es obviamente `a op`{:.nowrap} (por ejemplo, `5 sqrt`{:.nowrap}). Por su parte, para el operador ternario, el ordenamiento de los argumentos seguiría el mismo principio, transformándose `a ? b : c`{:.nowrap} en `a b c ?`{:.nowrap}. Este operador ternario devuelve, si `a` es distinto a 0, el valor de `b`, y si es 0 el valor de `c`.

- Ejemplos (nótese que toda la aritmética es entera, y el resultado siempre se trunca):

  - `20 11 -` → `20-11 = 9`
  - `20 -3 /` → `20/-3 = -6`
  - `20 10 ^` → `20^10 = 10240000000000`
  - `60 sqrt` → `√60 = 7`
  - `256 4 ^ 2 log` → `log₂(256⁴) = 32`
  - `1 -1 0 ?` → `1 ? -1 : 0 = -1` (funciona [como en C][ternref])

[ternref]: https://syntaxdb.com/ref/c/ternary


### Formato de entrada

- Cada línea de la entrada estándar representa una operación en su totalidad (produce un único resultado); y cada una de estas operaciones operación es independiente de las demás.

- Los símbolos en la expresión pueden ser números, u operadores. Todos ellos estarán siempre separados por uno o más espacios; la presencia de múltiples espacios debe tenerse en cuenta a la hora de realizar la separación en tokens.

  - <!-- gettalong/kramdown#486 -->
    Nota adicional: puede haber también múltiples espacios al comienzo de la línea, antes del primer token; por otra parte, no necesariamente habrá un espacio entre el último token y el caracter salto de línea que le sigue.

- El resultado final de cada operación debe imprimirse en una sola línea por salida estándar (_stdout_). En caso de error, debe imprimirse —para esa operación— la cadena `ERROR`, _también_ por salida estándar, y sin ningún tipo de resultado parcial. Tras cualquier error en una operación, el programa continuará procesando el resto de líneas con normalidad.

- Está permitido, para el cálculo de potencias, raíces y logaritmos, el uso de las funciónes de la biblioteca estándar `math`.


### Condiciones de error

El mensaje `ERROR` debe imprimirse como resultado en cualquiera de las siguientes situaciones:

1.  Cantidad de operandos insuficiente (`1 +`).

1.  Al finalizar la evaluación, queda más de un valor resultante. Es decir, no se realizaron suficientes operaciones para terminar que quede un único resultado (por ejemplo `1 2 3 +`, o `+ 2 3 -`).

1.  **Errores propios de cada operación matemática**, descritos a continuación:

    - división por 0
    - raíz de un número negativo
    - base del logaritmo menor a 2
    - potencia con exponente negativo


## Criterios de aprobación

El código entregado debe ser claro y legible y ajustarse a las especificaciones
de la consigna. Debe compilar sin advertencias y correr sin errores.

La entrega incluye, obligatoriamente, todos los archivos involucrados en la realización
del tp (es decir, el módulo del trabajo en sí, que debe llamarse `dc`), así como el
módulo `tdas` en caso de haber utilizado al menos alguno de los tipos de datos implementados 
anteriormente. 

La entrega se realiza únicamente en forma digital a través del [sistema de entregas]({{site.entregas}}), 
con todos los archivos mencionados en un único archivo ZIP.
