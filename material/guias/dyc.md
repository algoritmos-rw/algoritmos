---
math: true
---

# División y Conquista
{:.no_toc}


## Contenidos
{:.no_toc}

1. TOC
{:toc}


## Ejercicio resuelto

Implementar un algoritmo en C que reciba un arreglo de enteros de tamaño $$n$$, ordenado ascendentemente y sin elementos repetidos, y determine en $$\mathcal{O}(\log n)$$ si es mágico. Un arreglo es mágico si existe algún valor $$i$$ tal que $$0 \le i \lt n$$ y `arr[i] = i`. Justificar el orden del algoritmo.

Ejemplos:

* `A = [ -3, 0, 1, 3, 7, 9 ]` es mágico porque `A[3] = 3`.

* `B = [ 1, 2, 4, 6, 7, 9 ]` no es mágico porque `B[i] != i` para todo `i`.

### Solución

Como es mencionado en clase, al ver que se nos pide:

* Un algoritmo de división y conquista,

* Un orden $$\mathcal{O}(\log n)$$

Si no se nos pidiera que sea de división y conquista, y más aún que su orden sea logarítimico, podríamos simplemente ir elemento por elemento chequeando si se cumple la condición:

```cpp
bool arreglo_es_magico_lineal(int arr[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == i)
            return true;
    }
    return false;
}
```

Por supuesto, esta sería la solución _trivial_, casi con nulo esfuerzo de pensar y aprovechar la cualidad de que el
arreglo se encuentre ordenado y sin repetidos. Se podría hasta implementar con división y conquista, pero no dejará
de ser $$\mathcal{O}(n)$$. Como en otros problemas, vamos a buscar aprovechar las precondiciones que nos dan para el
arreglo.

Lo primero que tenemos que pensar es en el algoritmo _estrella_ de división y conquista que tiene ese orden: Búsqueda Binaria. Al ver que se nos pide eso, seguramente nuestro algoritmo no sea muy distinto al de búsqueda binaria (o bien, que la forma de la función va a ser similar). Pero para poder aplicar un algoritmo así, necesariamente tenemos que poder desechar toda una proporción del problema original en cada iteración. Ya vemos que tenemos la condición de que el arreglo se encuentra ordenado ascendentemente, y no cuenta con repetidos. Veremos si esa última restricción es realmente necesaria, pero al menos con la primera ya contamos con una restricción bastante fuerte.

Lo primero a pensar es el caso base: si se nos da vuelta el inicio y fin, significa que nunca nos topamos con un índice que cumpla la condición (no siempre va a ser este nuestro caso base, ojo).

Ahora, lo crucial: pensar la condición de éxito. Acá es donde analizamos qué resuelve nuestro algoritmo. Vamos al medio, y lo que tenemos que verificar es si `arr[medio] == medio`. Si eso sucede, ¡éxito! Entonces, por ahora tenemos:

```cpp
bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}

bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin) {
    if (inicio > fin) {
        return false;
    }

    size_t medio = (inicio + fin) / 2;
    if (arr[medio] == medio) {
        return true;
    }
    // nos falta el caso sin exito
}
```

Ahora, pensemos que eso no sucede. Necesitamos quedarnos con una sola de las mitades, lo cual implica descartar la otra. Pero ¿cómo descartamos una mitad? Bueno, podemos ver qué pasó con `arr[medio]` que no cumple con la condición de éxito. ¿Qué sucede si `arr[medio] < medio`? ¿Puede suceder que algún elemento anterior sí cumpla la condición? **¡NO!**, porque al no poder haber repetidos, si `arr[medio] < medio`, entonces `arr[medio - 1] < medio - 1`, y tambien para todos los anteriores. Por eso, podemos simplemente ver de la mitad en adelante, descartando la primera mitad. Ahí vemos que la condición extra era necesaria; si no, no podríamos descartar la primera mitad. Podemos hacer el mismo análisis al revés, vamos a ver que si `arr[medio] >  medio`, no puede ser que se cumpla la condición para los elementos siguientes.

Luego de este análisis, podemos escribir el código:

```cpp
bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}

bool _arreglo_es_magico(int arr[], size_t inicio, size_t fin) {
    if (inicio > fin) {
        return false;
    }

    size_t medio = (inicio + fin) / 2;
    if (arr[medio] == medio) {
        return true;
    }
    if (arr[medio] < medio) {
        return _arreglo_es_magico(arr, medio + 1, fin);
    } else {
        return _arreglo_es_magico(arr, inicio, medio - 1);
    }
}
```

_Nota_: El algoritmo puede, en vez de resolverse con una función auxiliar que haga la recursión, usando directamente `arreglo_es_magico`, usando aritmética de punteros. Quien prefiera hacerlo así, bienvenido es, aunque nos parece más claro para la explicación (y más directo) el código propuesto.

#### Demostración del orden

Veamos la ecuación de recurrencia. Hay escritos dos llamados recursivos, cada uno se invoca con la mitad del problema (mitad
izquierda o derecha), y todo lo que cuesta _partir y juntar_ no son más que algunas operaciones básicas de tiempo constante.
Lo importante es que si bien hay escritos dos llamados recursivos, nunca se llamará a ambos. Siempre se llamará bien
para el lado izquierdo, bien para el derecho. Por lo tanto, la ecuación de recurrencia quedará:

$$\mathcal{T}(n) = \mathcal{T}\left(\frac{n}{2}\right) + \mathcal{O}(1)$$

Es, evidentemente, igual a la de Búsqueda Binaria, por lo que tendrá el mismo orden, pero aplicamos el Teorema Maestro para corroborar:

$$A = 1; B = 2; C = 0 \rightarrow \log_B (A) = \log_2 (1) = 0 = C$$

Caemos en el caso de $$\log_B (A) = C$$, por lo que el orden del algoritmo será $$\mathcal{O}(n^C \log n) = \mathcal{O}(\log n)$$


## Ejercicios propuestos

1.  (★) Explicar por qué el siguiente siguiente código **no** es de división y conquista.

    ```cpp
    // Algoritmo ¿por D&C? para obtener el máximo de un arreglo
    int maximo(int* arreglo, size_t n) {
        if (n == 1) {
            return arreglo[0];
        }
        int max_restante = maximo(arreglo, n - 1);
        return arreglo[n - 1] > max_restante ? arreglo[n - 1] : max_restante;
    }
    ```

1.  (★) Explicar por qué el siguiente siguiente código **no** es de división y conquista.

    ```cpp
    // Algoritmo ¿por D&C? para obtener el máximo de un arreglo
    int maximo(int* arreglo, size_t n) {
        size_t medio = n / 2;
        int max_izquierda = _maximo(arreglo, 0, medio);
        int max_derecha = _maximo(arreglo, medio + 1, n - 1);
        return max_izquierda > max_derecha ? max_izquierda : max_derecha;
    }

    int _maximo(int* arreglo, size_t inicio, size_t fin) {
        int max = arreglo[inicio];
        for (size_t i = inicio + 1; i <= fin; i++) {
            if (max < arreglo[i]) {
                max = arreglo[i];
            }
        }
        return max;
    }
    ```

1.  (★★) Indicar la complejidad del siguiente algoritmo, utilizando el teorema del maestro:

    ```cpp
    // Busca un elemento usando D&C. El arreglo se encuentra ordenado.
    bool elemento_esta(int* arreglo, size_t inicio, size_t fin, int elem) {
        if (inicio > fin) return false;
        size_t medio = (fin + inicio) / 2;
        if (arreglo[medio] == elem) {
            return true;
        }
        if (arreglo[medio] < elem) {
            return elemento_esta(arreglo, medio + 1, fin, elem);
        }

        for (size_t i = medio - 1; i > inicio - 1; i--) {
            if (arreglo[i] == elem) return true;
        }
        return false;
    }
    ```

1.  (★) Hacerle el seguimiento al siguiente algoritmo:

    ```cpp
    void imprimir_dyc(int m) {
        if (m < 4) return;
        printf("%d\n", m);
        imprimir_dyc(m / 4);
        imprimir_dyc(m - (m / 4));
    }
    ```

1.  (★) Indicar, utilizando el Teorema del Maestro, la complejidad del ejercicio anterior.

1.  (★★) Indicar cuál es la complejidad de un algoritmo cuya ecuación de recurrencia es:
    $$\mathcal{T} = 2 \mathcal{T}\left(\frac{2}{3}n\right) + \mathcal{O}\left(\sqrt{n}\right)$$.

1.  (★★) Nos dan para elegir entre los siguientes 3 algoritmos para solucionar el mismo problema.
    ¿Cuál elegirías? Justificar calculando el orden de los algoritmos.
    1. El algoritmo `A` resuelve el problema dividiéndolo en 5 subproblemas de la mitad del tamaño,
    resolviendo cada subproblema de forma recursiva, y combinando las soluciones en tiempo lineal.
    1. El algoritmo `B` resuelve el problema (de tamaño $$n$$) dividiéndolo en 9 subproblemas de tamaño
    $$\frac{n}{3}$$, resolviendo cada subproblema de forma recursiva y combinando las soluciones en
    tiempo cuadrático de $$n$$.
    1. El algoritmo `C` resuelve el problema (de tamaño $$n$$) eligiendo un subproblema de tamaño
    $$n - 1$$ en tiempo $$\mathcal{O}(n)$$, y luego resolviendo recursivamente ese subproblema.
    {:.lower_alpha}

1.  (★★) Implementar, por división y conquista, una función que determine el mínimo de un arreglo.
    Indicar y justificar el orden.

1.  (★★) Implementar, por división y conquista, una función que dado un arreglo y su largo, determine si el mismo
    se encuentra ordenado. Indicar y justificar el orden.

1.  (★★) Implementar, por división y conquista, una función que dado un arreglo sin elementos repetidos y _casi ordenado_ (todos los elementos se
    encuentran ordenados, salvo uno), obtenga el elemento fuera de lugar. Indicar y justificar el orden.

1.  (★★★) Se tiene un arreglo tal que `[1, 1, 1, ..., 0, 0, ...]` (es decir, _unos seguidos de ceros_). Se pide:
    1. una función de orden $$\mathcal{O}(\log n)$$ que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.
    1. demostrar con el Teorema del Maestro que la función es, en efecto, $$\mathcal{O}(\log n)$$.
    {:.lower_alpha}

    Ejemplos:

        [1, 1, 0, 0, 0] →  2
        [0, 0, 0, 0, 0] →  0
        [1, 1, 1, 1, 1] → -1

1.  (★★★★) Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de la raíz cuadrada de
    un número $$n$$, en tiempo $$\mathcal{O}(\log n)$$. Por ejemplo, para $$n = 10$$ debe devolver 3, y para $$n = 25$$
    debe devolver 5.

1.  (★★★) Se tiene un arreglo de $$N >= 3$$ elementos en forma de pico, esto es: estrictamente creciente hasta una
    determinada posición $$p$$, y estrictamente decreciente a partir de ella (con $$0 \lt p \lt N - 1$$). Por ejemplo,
    en el arreglo `[1, 2, 3, 1, 0, -2]` la posición del pico es $$p = 2$$. Se pide:
    1. Implementar un algoritmo de división y conquista de orden $$\mathcal{O}(\log n)$$ que encuentre la posición
    $$p$$ del pico: `size_t posicion_pico(int v[], size_t ini, size_t fin);`. La función será invocará inicialmente como:
    `posicion_pico(v, 0, n-1)`, y tiene como pre-condición que el arreglo tenga forma de pico.
    1. Justificar el orden del algoritmo mediante el teorema del maestro.
    {:.lower_alpha}

1.  (★★) Se quiere implementar MergeSort pero, en vez de dividir en dos partes el arreglo, dividirlo en tres, llamando
    recursivamente al algoritmo para cada una de las partes y luego uniéndolas.
    1. Suponiendo que el merge de las tres partes se realiza en tiempo lineal, calcular el orden del algoritmo.
    1. Si en vez de dividir en tres partes, se dividiera el arreglo en $$n$$, siendo $$n$$ la cantidad de elementos del arreglo ¿a qué otro algoritmo de ordenamiento se asemeja esta implementación? ¿Cuál es el orden de dicho algoritmo?
    1. Dado lo obtenido en los puntos anteriores ¿tiene sentido implementar MergeSort con $$k$$ separaciones, para $$k > 2$$?
    {:.lower_alpha}

1.  (★★★) Un algoritmo sencillo para multiplicar matrices de $$n \times n$$ demora $$\mathcal{O}(n^3)$$.
    El algoritmo de Strassen (que utiliza División y Conquista) lo hace en $$\mathcal{O}(n^{\log_2 7})$$.
    La profesora Manterola quiere implementar un algoritmo de División y Conquista que sea aún más veloz,
    donde divida al problema en `A` subproblemas de tamaño de $$\frac{n}{4}$$, y que juntar las soluciones
    parciales sea $$\mathcal{O}(n^2)$$.
    ¿Cuál es el máximo `A` para que el orden del algoritmo sea menor que el del algoritmo de Strassen?
    Justificar.

1.  (★★★★) En Bytelandia tienen un sistema monetario extraño: su divisa es el
    bytelandés, y existen denominaciones en moneda física… ¡para todos
    los valores enteros! (Esto es, se emiten monedas de 1, 2, 3, …, 14, 15, …,
    28, 29, 30, … bytelandeses). No solo eso, _cualquier_ moneda de valor
    $$n$$ puede cambiarse en el banco por 3 monedas de menor denominación,
    de valores $$\lfloor\frac{n}{2}\rfloor$$, $$\lfloor\frac{n}{3}\rfloor$$
    y $$\lfloor\frac{n}{4}\rfloor$$ respectivamente (no existe denominación de 0 pesos,
    por lo cual es posible recibir menos de 3 monedas en el cambio); una vez hecho
    el cambio, sin embargo, no pueden cambiarse de vuelta por la moneda
    mayor (e.g., no pueden cambiase una moneda de 2 y otra de 3 por una
    de 5). Finalmente, también es posible intercambiar bytelandeses por
    pesos argentinos, a una tasa de 1 a 1.
    Se pide implementar un algoritmo que, utilizando **división y conquista**, reciba el valor
    $$n$$ de una moneda en bytelandés y devuelva la cantidad máxima de pesos argentinos que
    se podría obtener realizando los intercambios arriba mencionados. Por ejemplo, si
    $$n = 12$$, la cantidad máxima de pesos que se puede obtener es $13, ya que podemos dividir
    la moneda de 12 bytelandeses en monedas de 6, 4 y 3; y $6 + $4 + $3 = $13 (se podría seguir
    dividiendo, pero en este caso no conviene dividir ninguna de esas monedas resultantes).
    Justificar el orden del algoritmo implementado.


1.  (★★★★★) Implementar una función (que utilice división y conquista) de orden $$\mathcal{O}(n \log n)$$
    que dado un arreglo de $$n$$ números enteros devuelva `true` o `false` según si existe algún elemento que aparezca
    más de la mitad de las veces. Justificar el orden de la solución. Ejemplos:

        [1, 2, 1, 2, 3] -> false
        [1, 1, 2, 3] -> false
        [1, 2, 3, 1, 1, 1] -> true
        [1] -> true

    _Aclaración_: Este ejercicio puede resolverse, casi trivialmente, ordenando el arreglo con un algoritmo eficiente,
    o incluso se puede realizar más rápido utilizando una [tabla de hash](hash.md). Para hacer interesante el ejercicio,
    resolver **sin ordenar el arreglo**, sino puramente división y conquista.

{::options toc_levels="2" /}
