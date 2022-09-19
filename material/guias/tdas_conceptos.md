---
math: true
---

# Conceptos de TDAs, Pilas, Colas y Listas
{:.no_toc}


## Contenidos
{:.no_toc}

1. TOC
{:toc}


## Ejercicio resuelto

Implementar la _primitiva_ de la pila `func (pila PilaDinamica[T]) Miltitop(n int) []T`, que devuelve un arreglo de 
tamaño $$n$$ con los $$n$$ topes de la pila (los primeros $$n$$ elementos si estos fueran desapilados), sin utilizar estructuras auxiliares. Si la pila tiene menos de $$n$$ elementos, el arreglo/slice debe ser del tamaño de la pila. 

Indicar el orden de complejidad de la primitiva.

### Solución
{:.no_toc}

Dos cosas que es necesario entender desde el inicio del ejercicio:

1.  En este ejercicio _no se puede_ modificar la pila, pues el puntero recibido es de tipo constante (no tiene el asterisco de puntero); ello quiere decir que la pila a la que apunta es de sólo lectura, y por tanto sería erróneo modificar cualquiera de sus campos. 
1. _Además, no se debe_ modificarla pues, al ser una primitiva y tener acceso a los miembros internos de la estructura, no es necesario desapilar para acceder a los datos.

Una vez esto quede claro, la solución es bastante directa: si queremos que los elementos sean aquellos que desapilaríamos, simplemente tendríamos que iterar el arreglo en ese orden. Dada la implementación de la pila, deberíamos
hacerlo de atrás hacia delante. Si fuera una pila enlazada, simplemente sería iterar por los nodos.

```golang
func (pila PilaDinamica[T]) Miltitop(n int) []T {
    cant := min(n, pila.cantidad)
    topes := make([]T, cant)
    for i := 0; i < cant; i++ {
        topes[cant - i - 1] = pila.datos[i]
    }
    return topes
}
```

Sobre la complejidad: Acceder a cada elemento de la pila, siendo que accedemos directamente, es $$\mathcal{O}(1)$$, y nunca
vamos a ver más elementos de la pila si son más de $$n$$, por ende la primitiva es $$\mathcal{O}(n)$$. Podríamos considerar que va a ser el mínimo con la cantidad de elementos de la pila, pero si la cantidad de elementos de la pila fuera mucho más grande que $$n$$, de todas formas no superaría $$n$$. Es importante denotar
que $$n$$ en este caso no es la cantidad de elementos de la pila, sino la cantidad de elementos pedidos. Si quisiéramos
hacer más clara la distinción, podríamos haber llamado a dicho parámetro con otro nombre. Tener cuidado con esto, porque
si el parámetro tuviera otro nombre no sería correcto decir que es $$\mathcal{O}(n)$$, salvo que se aclare qué signifique
$$n$$.

## Ejercicios propuestos

1.  (★) Implementar el TDA Fracción. Dicho TDA debe tener las siguientes primitivas, cuya documentación
    puede encontrarse [aquí](extra/fraccion.go):
    ```
    CrearFraccion(numerador, denominador int) Fraccion
    Sumar(otra Fraccion) Fraccion
    Multiplicar(otra Fraccion) Fraccion
    ParteEntera() int
    Representacion() string
    ```

    Puede encontrarse la resolución de este ejercicio [aquí](soluciones/fraccion.go).

1.  (★) Implementar el TDA NumeroComplejo. Dicho TDA debe tener las siguientes primitivas, cuya documentación
    puede encontrarse [aquí](extra/complejo.go):
    ```
    CrearComplejo(real float, img float) Complejo
    Multiplicar(otro Complejo)
    Sumar(otro Complejo)
    ParteReal() float
    ParteImaginaria() float
    Modulo() float
    Angulo() float
    ```

1.  (★)  Implementar una función que reciba un arreglo genérico e invierta su orden, utilizando los TDAs vistos.
    Indicar y justificar el orden de ejecución.

1.  (★★) Implementar en Go el TDA `ComposiciónFunciones` que emula la composición de funciones (i.e. `f(g(h(x))`).
    Se debe definir la estructura del TDA, y las siguientes primitivas:
    ```
    CrearComposicion() ComposicionFunciones
    AgregarFuncion(func (float64) float64)
    Aplicar(float64) float64
    ```
    Considerar que primero se irán agregando las funciones como se leen, pero tener en cuenta el correcto orden
    de aplicación. Por ejemplo: para emular `f(g(x))`, se debe hacer:

        composicion.AgregarFuncion(f)
        composicion.AgregarFuncion(g)
        composicion.Aplicar(x)

    Indicar el orden de las primitivas.

1. (★★★) Dada una lista enlazada implementada con las siguientes estructuras:

    ```golang
        type nodoLista[T any] struct {
            prox *nodoLista[T]
            dato T
        }
        type ListaEnlazada[T any] struct {
            prim *nodoLista[T]
        }
    ```

    Escribir una primitiva de lista que devuelva el elemento que esté a $$k$$ posiciones del final (el
    ante-k-último), recorriendo la lista una sola vez y sin usar estructuras auxiliares. Considerar que
    $$k$$ es siempre menor al largo de la lista.
    Por ejemplo, si se recibe la lista `[ 1, 5, 10, 3, 6, 8 ]`, y `k = 4`, debe devolver 10.
    Indicar el orden de complejidad de la primitiva.


1.  (★★★) Dada una pila de enteros, escribir una función que determine si sus elementos están ordenados de manera ascendente. Una pila de enteros está ordenada de manera ascendente si, en el sentido que va desde el tope de la pila hacia el resto de elementos, cada elemento es menor al elemento que le sigue.
    La pila debe quedar en el mismo estado que al invocarse la función.
    Indicar y justificar el orden del algoritmo propuesto.

1.  (★★) Implementar la primitiva `func (cola *colaEnlazada[T]) Multiprimeros(k int) []T` que dada una cola y un
    número $$k$$, devuelva los primeros $$k$$ elementos de la cola, en el mismo orden en el que habrían
    salido de la cola. En caso que la cola tenga menos de $$k$$ elementos. Si hay menos elementos que $$k$$ en
    la cola, devolver un slice del tamaño de la cola. Indicar y justificar el orden de ejecución del algoritmo.

1.  (★★) Implementar la **función** `func Multiprimeros[T any](cola Cola[T], k int) []T` con el mismo comportamiento de la
    primitiva anterior.

1.  (★★) Implementar en Go una primitiva `func (lista *ListaEnlazada) Invertir()` que invierta la lista, 
    sin utilizar estructuras auxiliares. Indicar y justificar el orden de la primitiva.

1.  (★★) Se quiere implementar un TDA ColaAcotada sobre un arreglo. Dicho TDA tiene un espacio para $$k$$ elementos
    (que se recibe por parámetro al crear la estructura). Explicar cómo deberían implementarse las primitivas
    encolar y desencolar de tal manera que siempre sean operaciones de tiempo constante.

1.  (★★★★) Implementar una función que ordene de manera ascendente una pila de enteros sin conocer su estructura interna y
    utilizando como estructura auxiliar sólo otra pila auxiliar.
    Por ejemplo, la pila `[ 4, 1, 5, 2, 3 ]` debe quedar como `[ 1, 2, 3, 4, 5 ]` (siendo el último elemento el tope de la pila, en ambos casos). Indicar y justificar el orden de la función.

1.  (★★) Implementar una función `func FiltrarCola[K any](cola Cola[K], func filtro(K) bool)` , que elimine los
    elementos encolados para los cuales la función _filtro_ devuelve `false`. Aquellos elementos que no son eliminados
    deben permanecer en el mismo orden en el que estaban antes de invocar a la función. No es necesario destruir los
    elementos que sí fueron eliminados. Se pueden utilizar las estructuras auxiliares que se consideren necesarias y
    no está permitido acceder a la estructura interna de la cola (es una función). ¿Cuál es el orden del algoritmo
    implementado?

1.  (★★★) Sabiendo que la firma del iterador interno de la lista enlazada es:

    ```golang
        Iterar(func(K) bool)
    ```
    
    Se tiene una lista en donde todos los elementos son punteros a números enteros. Implementar la función _visitar_ para que calcule la suma de todos los números pares. Mostrar, además, una invocación completa a `Iterar()` que haga uso del _visitar_ implementado.

1.  (★★★★★) Diseñar un TDA `PilaConMáximo`, que tenga las mismas primitivas de la pila convencional, 
    y además permita obtener el máximo de la pila. **Todas**
    las primitivas deben funcionar en $$\mathcal{O}(1)$$. Explicar cómo implementarías el TDA para
    que cumpla con todas las restricciones.

1.  (★★★) Implementar el TDA Mamushka (matrioshka, o muñeca rusa), teniendo en cuenta que una Mamushka puede
    tener otra Mamushka dentro de si misma. Las primitivas deben ser:
        
     - `CrearMamushka(tam int, color Color) Mamushka`: Crea una mamushka con un tamaño y color definido.
     - `ObtenerColor() Color`: Obtiene el color de la Mamushka.
     - `Guardar(Mamushka) bool`: _Intenta_ guardar la segunda 
        mamushka en la primera. Si la primera ya tiene una mamushka guardada, entonces debe
        intentar guardar la mamushka `a_guardar` dentro de la mamushka que ya estaba guardada.
        La operación falla (y devuelve `false`) si en algún momento se intenta guardar una mamushka
        en otra de menor o igual tamaño. 
        Por ejemplo: si tenemos una mamushka de tamaño 10 que dentro tiene una de tamaño 8, y se
        intenta guardar una de tamaño 5, ésta debe guardarse dentro de la de tamaño 8.
        Si, luego, se intentara guardar una de tamaño 6, la operación debe fallar dado
        que no se puede guardar una mamushka de tamaño 6 dentro de una de tamaño 5.
     - `ObtenerGuardada() Mamushka`: Devuelve un puntero a la mamushka guardada. 
        `NULL` en caso de no tener ninguna guardada. En el ejemplo anterior, si utilizaremos esta primitiva
        con la Mamushka de tamaño 10, nos devolvería la Mamushka de tamaño 8 que guardamos (y que dentro
        tiene la de tamaño 5). 

    Definir la estructura (`struct`) del TDA, y escribir estas 5 primitivas. Indicar el orden de cada una de ellas.
    
    _Nota_: `Color` corresponde a un enumerado, que está definido en algún lugar.
    
1.  (★★★) Dadas dos pilas de enteros positivos (con posibles valores repetidos) cuyos elementos fueron ingresados de menor
    a mayor, se pide implementar una **función** `func MergePilas[T any](pila1, pila2 Pila[T]) []T` que devuelva un array
    ordenado de menor a mayor con todos los valores de ambas pilas sin repeticiones.
    Detallar y justificar la complejidad del algoritmo considerando que el tamaño de las pilas es N y M respectivamente.
