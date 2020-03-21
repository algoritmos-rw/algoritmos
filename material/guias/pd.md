---
math: true
---

# Programación dinámica
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

Dado un número _n_, mostrar la cantidad más económica (con menos términos) de escribirlo como una suma de cuadrados. Indicar el orden del algoritmo implementado.
Nota: siempre es posible escribir a n como suma de _n_ términos de la forma $$1^2$$, por lo que siempre existe solución. Sin embargo, la expresión $$10 = 3^2 + 1^2$$ es una manera más económica de escribirlo para `n = 10`, pues sólo tiene dos términos.

Además, tener en cuenta que no se piden los términos, sino la cantidad mínima de términos cuadráticos necesaria.

Posible ayuda: considerar que para formar el número 0 necesitamos 0 términos; y que $$10 = 9 + 1^2$$, también $$10 = 6 + 2^2$$, y también $$10 = 1 + 3^2$$ ¡Si tan solo supiéramos la cantidad de términos para formar 9, 6 y 1. . . !

### Solución
Primero entendamos el problema: se nos pide escribir un número como una suma de cuadrados perfectos. Ante eso, sabemos que por ejemplo a 74 lo podemos escribir como 74 términos de $$1^2$$, aunque claramente esa no va a ser la solución óptima.
Por fuerza bruta, deberíamos probar cada una de las combinaciones, y simplemente quedarnos con la mejor.

Ahora bien, hay dos formas de resolver este problema.

#### Opción 1

A 74 lo podemos escribir como 73 + 1, también como 72 + 2, también como 71 + 3, etc... Entonces simplemente tenemos que verificar cuántos términos son necesarios para escribir cada número de la pareja (cuidando los cuadrados perfectos). Entonces, la ecuación de recurrencia nos quedaría:

- _opt(n) = 0_ si _n == 0_;
- 1 si _n_ cuadrado perfecto;
- _min(opt(n-i) + opt(i))_, para _i_ en _[1; n-1]_ en otro caso

El código de la resolución recursiva sería:

``` python
def minimos_terminos(n):
    if n == 0:
        return 0
    if es_cuadrado_perfecto(n):
        return 1
    #opcion con todos 1s
    mejor = n
    for i in range(1, n):
        mejor = min(mejor, minimos_terminos(n-i) + minimos_terminos(i))
    return mejor
```

Como vemos, se hacen muchísimos llamados resursivos (para 74 se hacen para 1 y 73, 2 y 72, etc.. y dentro de estos también se hacen muchos). Si ya tuviéramos calculados los términos para todos los valores anteriores, esto podría evitarse. Entonces, simplemente hacemos:

``` python
def minimos_terminos(n):
    #arreglo en el que guardaremos los resultados
    int v[n+1];
    for i in [1.. n]:
        if es_cuadrado_perfecto(i):
            v[i] = 1
            continue
        #inicialmente ponemos la solución que seguro existe
        v[i] = i
        #Podria iterarse solo hasta la mitad, porque vamos a repetir combinaciones:
        for j in [1.. i-1]:
            v[i] = min(v[i], v[i-j] + v[j])
    return v[n]
```

Claramente esta solución es mucho mejor que la anterior. En espacio es muy fácil de ver que es $$\mathcal{O}(n)$$, dado el arreglo auxiliar que estamos utilizando, mientras que en tiempo podríamos decir que es:
$$\mathcal{O}(n * (n + \mathcal{O}(es\_cuadrado\_perfecto)))$$. La función `es_cuadrado_perfecto` se puede implementar trivialmente con un orden $$\mathcal{O}(\sqrt{n})$$, aunque también se podría hacer en $$\mathcal{O}(\log n)$$. En cualquier caso, es claramente despreciable al lado del $$\mathcal{O}(n)$$ de la segunda iteración, por lo que el algoritmo será finalmente $$\mathcal{O}(n^2)$$.


#### Opción 2

Una mejora importante es simplemente restar los cuadrados perfectos. Si yo sé que $$10 = 9 + 1^2 = 6 + 2^2 = 1 + 3^2$$, sabemos que el segundo término de cada igualdad es ya de por sí un término cuadrático (por ende, se escribe con un solo término). Si supiéramos la cantidad óptima para 9, para la primera opción solo tendríamos que decir `opt1(10) = opt(9) + 1`. Para la segunda opción, si tuviéramos el óptimo para 6, el óptimo para esa opción sería la cantidad óptima para 6, más 1 por el $$2^2$$ (se escribe en un solo término, esa es la gracia). Entonces, la ecuación de recurrencia nos quedaría:
`opt(n) = 0 si n == 0; min(opt(n-i^2) + 1), para i tal que i^2 <= n, en otro caso`

(Notar que los cuadrados perfectos van a ser tenidos en cuenta ya que al hacer, por ejemplo, $$9 = 0 + 3^2$$, el 0 no agrega término).

Obviando la implementación recursiva (la dejamos de tarea, pero será muy parecida a la anterior), la solución optimizada será:

``` python
def terminos(n):
    int v[n+1];
    v[0] = 0
    for i in [1.. n]:
        j = 1
        v[i] = i
        #veo todos los cuadrados perfectos menores o iguales a i:
        while j*j <= i:
            v[i] = min(v[i], v[i - j*j] + 1)
            j += 1
    return v[n]
```

Sobre el orden, es fácil primero pensar que es $$\mathcal{O}(n^2)$$. A los fines de un parcialito, si alguien escribiera esto para dicha solución, sería visto como correcto.

Ahora bien, en realidad si bien el primer for se itera _n_ veces, el while no itera _n_ veces, sino que itera por los cuadrados perfectos anteriores. La variable _j_ a lo sumo va a valer la raíz cuadrada de _i_. Eso implica que ese for se itera $$\sqrt{i}$$ veces, por lo tanto el orden va a ser $$\mathcal{O}(n * \sqrt{n}) = \mathcal{O}(n^{1.5})$$.

Otra forma de verlo, es que este ejercicio es *muy similar* al problema del cambio. Supongamos que nuestras monedas fueran los infinitos cuadrados perfectos (o con considerar hasta el próximo al _N_ que nos interese, sería suficiente). Antes tratábamos de formar el cambio con las monedas que teníamos, ahora tratamos de formar un número con los cuadrados perfectos. Se puede ver que hay una equivalencia directa, teniendo de monedas el 1, 4, 9, 16, 25, ...
A su vez, también se puede ver que la solución greedy para el problema del cambio no aplicaría para este problema (al menos de forma óptima), puesto que no se cumple la propiedad de tener que una moneda sea al menos del doble de valor que su anterior.


## Ejercicios propuestos

1. La cantidad de posibles colocaciones de paréntesis para n operadores binarios está dada por la fórmula:

   $$
   v[n] = \sum_{j=0}^{n-1} v[j] * v[(n-1)-j]$$, con $$v[0] = 1$$ y $$v[1] = 1
   $$

   Escribir una función que obtenga la cantidad de agrupaciones para un valor N de operadores de forma eficiente.

2. Dado el binomio $$(a + b)^n$$ (donde _n_ es nuestra variable), queremos conocer todos los coeficientes resultantes de desarrollar el mismo.

   Tener en cuenta que: $$(a + b)^n = \sum_{k=0}^n \binom{n}{k} a^{n} \times b^{n-k}$$

   Por lo tanto, lo que nos interesa conocer son los valores de todos esos combinatorios. Sabiendo que:
   - $$\binom{n}{0} = 1$$.
   - $$\binom{n}{n} = 1$$.
   - $$\binom{n}{k} = \binom{n-1}{k} + \binom{n-1}{k-1}$$ (en otro caso).

   Implementar un algoritmo que por programación dinámica nos permita obtener todos los coeficientes de un binomio de grado _n_.

3. Juan es ambicioso pero también algo vago. Dispone de varias ofertas de trabajo diarias, pero no quiere trabajar dos días seguidos. Dado un arreglo con el monto esperado a ganar cada día, determinar por programación dinámica el máximo monto a ganar, sabiendo que no aceptará trabajar dos días seguidos.

   Por ejemplo, si el arreglo es `[100, 20, 30, 70, 50]` el monto máximo que podrá ganar serán $180 (trabajar el primer, tercer y quinto día). En cambio, si el arreglo fuera `[100, 20, 30, 70, 20]`, el monto máximo a ganar serían $170 (resultado de trabajar el primer y cuarto día).

   *Aclaración*: estos fueron tan solo ejemplos, no quiere decir que el arreglo vaya a tener tan solo 5 elementos.

4. Se tiene una grilla de `MxN` casilleros. Si solo se puede comer hacia abajo y hacia la derecha:

   1. Determinar la cantidad de caminos posibles que hay para llegar desde el casillero `(0, 0)` hasta el casillero `(M-1, N-1)`.
   2. Idem anterior, pero teniendo en cuenta que hay casilleros (conocidos) sobre los que no se puede pisar (hay obstáculos).
   3. Si en cada casillero hubiera una cantidad de dinero (que pudiera ser 0) que se puede recoger, determinar la máxima cantidad de dinero que se puede obtener partiendo desde el casillero `(0, 0)` hasta el `(M-1, N-1)`.
   4. Idem anterior, pero sabiendo que además hay obstáculos en algunos casilleros (símil al inciso b).

5. Dado un conjunto de números positivos _L_ y un número _n_, determinar si existe un subconjunto de _L_ que sume exactamente _n_.

6. ¡Ejercicio difícil! En este barrio todos viven alrededor de la plaza y los vecinos contiguos se odian entre sí. Hay _n_ vecinos y el primer vecino es contiguo con el último. Cuando le preguntan a cada uno cuánto es lo máximo que va a donar para arreglar la plaza la respuesta se registra en el array `donar = [d0, d1, ..., d(n-1)]`, pero la condición es: solo donaré si no dona ninguno de mis vecinos contiguos.

   Usando programación dinámica resolver cuánto es lo máximo que se puede recolectar por donaciones.

## Bibliografía y referencias

- Weiss, Mark Allen: "Data Structures and Algorithms" (tercera edición), Pearson, 1999. Cap. 10.3: _Dynamic programming_.
- Guerequeta, Rosa; Vallecillo, Antonio: "Técnicas de Diseño de Algoritmos" (segunda edición), Servicio de Publicaciones de la Universidad de Málaga, 1998. Cap 5: _Programación dinámica_.
- Cormen, Thomas; Leiserson, Charles; Rivest, Ronald; Stein, Clifford: "Introduction to Algorithms" (tercera edición), MIT Press, 2009. Cap. 15: _Dynamic programming_.
