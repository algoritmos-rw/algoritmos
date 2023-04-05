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

Implementar un algoritmo en Go que reciba un arreglo de enteros de tamaño $$n$$, ordenado ascendentemente y sin elementos repetidos, y determine en $$\mathcal{O}(\log n)$$ si es mágico. Un arreglo es mágico si existe algún valor $$i$$ tal que $$0 \le i \lt n$$ y `arr[i] = i`. Justificar el orden del algoritmo.

Ejemplos:

* `A = [ -3, 0, 1, 3, 7, 9 ]` es mágico porque `A[3] = 3`.

* `B = [ 1, 2, 4, 6, 7, 9 ]` no es mágico porque `B[i] != i` para todo `i`.

### Solución

Como es mencionado en clase, al ver que se nos pide:

* Un algoritmo de división y conquista,

* Un orden $$\mathcal{O}(\log n)$$

Si no se nos pidiera que sea de división y conquista, y más aún que su orden sea logarítimico, podríamos simplemente ir elemento por elemento chequeando si se cumple la condición:

```golang
func ArregloEsMagico(arr []int) bool {
    for elem, i := range(arr) {
        if elem == i {
            return true
        }
    }
    return false
}
```

Por supuesto, esta sería la solución _trivial_, casi con nulo esfuerzo de pensar y aprovechar la cualidad de que el
arreglo se encuentre ordenado y sin repetidos. Se podría hasta implementar con división y conquista, pero no dejará
de ser $$\mathcal{O}(n)$$. Como en otros problemas, vamos a buscar aprovechar las precondiciones que nos dan para el
arreglo.

Lo primero que tenemos que pensar es en el algoritmo _estrella_ de división y conquista que tiene ese orden: Búsqueda Binaria. Al ver que se nos pide eso, seguramente nuestro algoritmo no sea muy distinto al de búsqueda binaria (o bien, que la forma de la función va a ser similar). Pero para poder aplicar un algoritmo así, necesariamente tenemos que poder desechar toda una proporción del problema original en cada iteración. Ya vemos que tenemos la condición de que el arreglo se encuentra ordenado ascendentemente, y no cuenta con repetidos. Veremos si esa última restricción es realmente necesaria, pero al menos con la primera ya contamos con una restricción bastante fuerte.

Lo primero a pensar es el caso base: si se nos da vuelta el inicio y fin, significa que nunca nos topamos con un índice que cumpla la condición (no siempre va a ser este nuestro caso base, ojo).

Ahora, lo crucial: pensar la condición de éxito. Acá es donde analizamos qué resuelve nuestro algoritmo. Vamos al medio, y lo que tenemos que verificar es si `arr[medio] == medio`. Si eso sucede, ¡éxito! Entonces, por ahora tenemos:

```golang
func ArregloEsMagico(arr []int) bool {
    return arregloEsMagico(arr, 0, len(arr) - 1)
}

func arregloEsMagico(arr []int, inicio int, fin int) bool {
    if inicio > fin {
        return false
    }
    medio := (inicio + fin) / 2
    if arr[medio] == medio {
        return true
    }
    // nos falta el caso sin exito
}
```

Ahora, pensemos que eso no sucede. Necesitamos quedarnos con una sola de las mitades, lo cual implica descartar la otra. Pero ¿cómo descartamos una mitad? Bueno, podemos ver qué pasó con `arr[medio]` que no cumple con la condición de éxito. ¿Qué sucede si `arr[medio] < medio`? ¿Puede suceder que algún elemento anterior sí cumpla la condición? **¡NO!**, porque al no poder haber repetidos, si `arr[medio] < medio`, entonces `arr[medio - 1] < medio - 1`, y tambien para todos los anteriores. Por eso, podemos simplemente ver de la mitad en adelante, descartando la primera mitad. Ahí vemos que la condición extra era necesaria; si no, no podríamos descartar la primera mitad. Podemos hacer el mismo análisis al revés, vamos a ver que si `arr[medio] >  medio`, no puede ser que se cumpla la condición para los elementos siguientes.

Luego de este análisis, podemos escribir el código:

```golang
func ArregloEsMagico(arr []int) bool {
    return arregloEsMagico(arr, 0, len(arr) - 1)
}

func arregloEsMagico(arr []int, inicio int, fin int) {
    if inicio > fin {
        return false
    }
    medio := (inicio + fin) / 2
    if arr[medio] == medio {
        return true
    }
    if (arr[medio] < medio) {
        return arregloEsMagico(arr, medio + 1, fin);
    } else {
        return arregloEsMagico(arr, inicio, medio - 1);
    }
}
```

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

    ```golang
    // Algoritmo ¿por D&C? para obtener el máximo de un arreglo
    func maximo(arreglo []int) int {
        if len(arreglo) == 1 {
            return arreglo[0]
        }
        max_restante := maximo(arreglo[0:len(arreglo)-1])
        if arreglo[len(arreglo) - 1] > max_restante {
            return arreglo[len(arreglo) - 1]
        } else {
            return max_restante
        }
    }
    ```

1.  (★) Explicar por qué el siguiente siguiente código **no** es de división y conquista.

    ```golang
    // Algoritmo ¿por D&C? para obtener el máximo de un arreglo
    func maximo(arreglo []int) int {
        medio = len(arreglo) / 2
        max_izquierda := _maximo(arreglo, 0, medio)
        max_derecha := _maximo(arreglo, medio + 1, len(arreglo) - 1)
        if max_izquierda > max_derecha {
            return max_izquierda
        } else {
            return max_derecha
        }
    }
    
    func _maximo(arreglo []int, inicio int, fin int) int {
        max := arreglo[inicio]
        for i := inicio + 1; i <= fin; i++ {
            if max < arreglo[i] {
                max = arreglo[i]
            }
        }
        return max
    }
    ```

1.  (★★) Indicar la complejidad del siguiente algoritmo, utilizando el teorema maestro:

    ```golang
    // Busca un elemento usando D&C. El arreglo se encuentra ordenado.
    func elementoEsta(arreglo []int, inicio int, fin int, elem int) bool {
        if inicio > fin {
            return false
        }
        medio := (inicio + fin) / 2
        if arreglo[medio] == medio {
            return true
        }
        if arreglo[medio] < elem {
            return elementoEsta(arreglo, medio + 1, fin, elem)
        }
        for i := medio - 1; i > inicio; i-- {
            if arreglo[i] == elem {
                return true
            }
        }
        return false
    }
    ```

1.  (★) Hacerle el seguimiento al siguiente algoritmo:

    ```golang
    func imprimirDyC(m int) {
        if m < 4 {
            return
        }
        fmt.Println(m)
        imprimirDyC(m / 4)
        imprimirDyC(m - (m / 4))
    }
    ```

1.  (★) Indicar, utilizando el Teorema Maestro, la complejidad del ejercicio anterior.

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

1.  (★★★) Implementar, por división y conquista, una función que dado un arreglo sin elementos repetidos y _casi ordenado_ (todos los elementos se
    encuentran ordenados, salvo uno), obtenga el elemento fuera de lugar. Indicar y justificar el orden.

1.  (★★★) Se tiene un arreglo tal que `[1, 1, 1, ..., 0, 0, ...]` (es decir, _unos seguidos de ceros_). Se pide:
    1. una función de orden $$\mathcal{O}(\log n)$$ que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.
    1. demostrar con el Teorema Maestro que la función es, en efecto, $$\mathcal{O}(\log n)$$.
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
    $$p$$ del pico: `func PosicionPico(v []int, ini, fin int) int`. La función será invocada inicialmente como:
    `PosicionPico(v, 0, len(v)-1)`, y tiene como pre-condición que el arreglo tenga forma de pico.
    1. Justificar el orden del algoritmo mediante el teorema maestro.
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

1.  (★★★★★) Tenemos un arreglo de tamaño `2n` de la forma `{C1, C2, C3, … Cn, D1, D2, D3, … Dn}`, 
	tal que la cantidad total de elementos del arreglo es potencia de 2 (por ende, `n` 
	también lo es). Implementar un algoritmo de División y Conquista que modifique el arreglo 
	de tal forma que quede con la forma `{C1, D1, C2, D2, C3, D3, …, Cn, Dn}`, **sin utilizar 
	espacio adicional** (obviando el utilizado por la recursividad). ¿Cual es la complejidad 
	del algoritmo?

	_Pista_: Pensar primero cómo habría que hacer si el arreglo tuviera 4 elementos 
	(`{C1, C2, D1, D2}`). Luego, pensar a partir de allí el caso de 8 elementos, etc...
	para encontrar el patrón. 
	
1.	(★★★★) Debido a la trágica situación actual, es necesario realizar tests para detectar
	si alguna persona está contagiada de COVID-19. El problema es que los insumos
	tienden a ser bastante caros, y no vivimos en un país al que los recursos le sobren. 

	Supongamos que por persona se toma más de una muestra (lo cual es cierto, pero a fines
	del ejercicio supongamos que son muchas muestras), y que podemos realizar un testeo a más 
	de una persona al mismo tiempo mezclando las muestras (lo cual también es cierto): 
	determinamos un conjunto de personas a testear, obtenemos una muestra de cada una de ellas,
	las "juntamos", y al conjunto le realizamos el test. Si el test resulta negativo, 
	implica que todas las personas testeadas en conjunto resultaron negativas. Si resulta 
	positivo, implica que al menos una de las personas testedas resulta positiva. 

	Suponer que existe una función `pcr(grupo)`, que devuelve `true` si al menos una persona
	del `grupo` es COVID-positivo, y `false` en caso contrario (los `grupos` pueden estar
	formados por 1 o más personas). Suponer que la positividad es extremadamente baja, e inclusive
	pueden suponer que va a haber una única persona contagiada (por simplicidad). 

	Implementar un algoritmo que dado un conjunto de `n` personas, devuelva la o las personas
	contagiadas, utilizando la menor cantidad de tests posibles (considerando la notación Big Oh).
	En dicha notación, ¿cuántos tests se estarán utilizando?

	Pueden considerar que habrá una única persona contagiada, pero esto no cambiará el análisis
	a realizar. 
	
1. 	(★★★★) Se sabe, por el teorema de Bolsano, que si una función es continua en un intervalo `[a, b]`, 
	y que en el punto `a` es positiva y en el punto `b` es negativa (o viceversa), necesariamente
	debe haber (al menos) una raíz en dicho intervalo. Implementar una función 
	`func raiz(f func(int)int, a int, b int) int` que reciba una función (univariable) y
	los extremos mencionados y devuelva una raíz dentro de dicho intervalo (si hay más de una, 
	simplemente quedarse con una). La complejidad de dicha función debe ser logarítmica del
	largo del intervalo `[a, b]`. Asumir que por más que se esté trabajando con números enteros, 
	hay raíz en dichos valores: Se puede trabajar con `floats`, y el algoritmo será equivalente, 
	simplemente se plantea con `ints` para no generar confusiones con la complejidad.
	Justificar la complejidad de la función implementada.

1.  (★★★) Es el año 1700, y la pirata Barba-ra Verde atacó un barco de la _Royal British Shipping & Something_, 
    que transportaba una importante piedra preciosa de la corona británica. Al parecer, la escondieron
    en un cofre con muchas piedras preciosas falsas, en caso de un ataque. Barba-ra Verde sabe que
    los refuerzos británicos no tardarán en llegar, y deben uir lo más rápido posible. El problema es
    que no pueden llevarse el cofre completo por pesar demasiado. Necesita encontrar rápidamente
    la joya verdadera. La única forma de descubrir la joya verdadera es pesando. Se sabe que la joya
    verdadera va a pesar más que las imitaciones, y que las imitaciones pesan todas lo mismo. 
    Cuenta con una balanza de platillos para poder pesarlas (es el 1700, no esperen una balanza digital).

    a. Escribir un algoritmo de división y conquista, para determinar cuál es la verdadera joya de la corona. Suponer que hay una función 
    `balanza(grupo_de_joyas1, grupo_de_joyas2)` que devuelve 0 si ambos grupos pesan lo mismo, mayor a 0 si
    el `grupo1` pesa más que el `grupo2`, y menor que 0 si pasa lo contrario, y realiza esto en tiempo 
    constante.
    b. Indicar y justificar (adecuadamente) la complejidad de la función implementada. 


{::options toc_levels="2" /}
