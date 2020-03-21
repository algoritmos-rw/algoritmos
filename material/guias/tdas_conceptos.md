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

Implementar la _primitiva_ de la pila `void** pila_multitop(const pila_t* pila, size_t n)`, que devuelve un arreglo de tamaño $$n$$ con los $$n$$ topes de la pila (los primeros $$n$$ elementos si estos fueran desapilados), sin utilizar estructuras auxiliares. Completar el arreglo a devolver con NULL cuando el $$n$$ recibido por parámetro sea mayor a la cantidad de elementos de la pila.

Indicar el orden de complejidad de la primitiva.

### Solución
{:.no_toc}

Algo que está implícito en el ejercicio es que se asume que la implementación del TDA Pila es sobre un arreglo dinámico, tal
cual fue visto en clase. Siempre es válido asumir que la implementación es la misma a la que debieron implementar, salvo que
el enunciado especifique lo contrario.

Dos cosas que es necesario entender desde el inicio del ejercicio:

1.  En este ejercicio _no se puede_ modificar la pila, pues el puntero recibido es de tipo _const_; ello quiere decir que la pila a la que apunta es de sólo lectura, y por tanto sería erróneo modificar cualquiera de sus campos. _Además, no se debe_ modificarla pues, al ser una primitiva y tener acceso a los miembros internos de la estructura, no es necesario desapilar para acceder a los datos.

1.  Se pide devolver un arreglo, pero es muy importante entender que debe ser un arreglo dinámico (creado con _malloc_). Sería un error **muy grave** devolver un arreglo estático, pues al terminar la ejecución de la función, la memoria de ese arreglo pasaría a ser inválida. Un error de este tipo anula el ejercicio por completo.

Una vez esto quede claro, la solución es bastante directa: si queremos que los elementos sean aquellos que desapilaríamos, simplemente tendríamos que iterar el arreglo en ese orden. Dada la implementación de la pila, deberíamos
hacerlo de atrás hacia delante. Si fuera una pila enlazada, simplemente sería iterar por los nodos.

```cpp
void** pila_multitop(const pila_t* pila, size_t n) {
    void** topes = malloc(sizeof(void*) * n);
    if (!topes) {
        return NULL;
    }
    // Se podria hacer que i comience en k o pila->cantidad - 1, pero hay que
    // tener cuidado con esto, y con la condicion de corte: un size_t nunca
    // va a ser menor a 0
    for (size_t i = 0; i < n; i++) {
        if (i < pila->cantidad) {
            topes[i] = pila->datos[pila->cantidad - 1 - i];
        } else {
            topes[i] = NULL;
        }
    }
    return topes;
}
```

También sería válido hacerlo en dos iteraciones: una para llenar con los topes, y otra para rellenar con `NULL`s el resto.
Así como también lo sería iterar hasta el más pequeño entre `n` y `pila->cantidad`, habiendo inicializado antes el
arreglo con `NULL`s (ya sea iterando, o usando `calloc`). Otras tantas variantes también serían aceptadas, no hay una única
forma de resolver este ejercicio.

Sobre la complejidad, sea cual sea el caso, vamos a estar llenando siempre el arreglo de $$n$$ elementos con algo (datos de
la pila, o `NULL`). Acceder a cada elemento de la pila, siendo que accedemos directamente, es $$\mathcal{O}(1)$$, y nunca
vamos a ver más elementos de la pila si son más de $$n$$, por ende la primitiva es $$\mathcal{O}(n)$$. Es importante denotar
que $$n$$ en este caso no es la cantidad de elementos de la pila, sino la cantidad de elementos pedidos. Si quisiéramos
hacer más clara la distinción, podríamos haber llamado a dicho parámetro con otro nombre. Tener cuidado con esto, porque
si el parámetro tuviera otro nombre no sería correcto decir que es $$\mathcal{O}(n)$$, salvo que se aclare qué signifique
$$n$$.



## Ejercicios propuestos

1.  (★) Implementar el TDA Fracción. Dicho TDA debe tener las siguientes primitivas, cuya documentación
    puede encontrarse [aquí](extra/fraccion.h):
    ```
    fraccion_t* fraccion_crear(int numerador, int denominador);
    fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2);
    fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2);
    char* fraccion_representacion(fraccion_t* fraccion);
    int fraccion_parte_entera(fraccion_t* fraccion);
    void fraccion_destruir(fraccion_t* fraccion);
    ```

    _Nota_: considerar que se puede utilizar la función `sprintf` para generar la representación de
    la fracción. Por ejemplo: `sprintf(buffer, "%d/%d", num1, num2)`.
    Puede encontrarse la resolución de este ejercicio [aquí](soluciones/fraccion.c).

1.  (★) Implementar el TDA NumeroComplejo. Dicho TDA debe tener las siguientes primitivas, cuya documentación
    puede encontrarse [aquí](extra/complejo.h):
    ```
    complejo_t* complejo_crear(double real, double img);
    void complejo_multuplicar(complejo_t* c1, complejo_t* c2);
    void complejo_sumar(complejo_t* c1, complejo_t* c2);
    double complejo_obtener_imaginaria(const complejo_t* complejo);
    double complejo_obtener_real(const complejo_t* complejo);
    double complejo_obtener_modulo(const complejo_t* complejo);
    double complejo_obtener_angulo(const complejo_t* complejo);
    void complejo_destruir(complejo_t* complejo);
    ```

    _Nota_: considerar que se puede utilizar la función `sprintf` para generar las representaciones.

1.  (★)  Implementar una función que reciba un arreglo de `void*` e invierta su orden, utilizando los TDAs vistos.
    Indicar y justificar el orden de ejecución.

1.  (★)  Mismo a lo anterior, pero que el arreglo sea de `int` (no de `int*`), utilizando los TDAs tal cual se los
    implementa en clase.

1.  (★★) Implementar en C el TDA `ComposiciónFunciones` que emula la composición de funciones (i.e. `f(g(h(x))`).
    Se debe definir la estructura del TDA, y las siguientes primitivas:
    ```
    composicion_t* composicion_crear();
    void composicion_destruir(composicion_t*);
    bool composicion_agregar_funcion(composicion_t*, double (*f)(double));
    double composicion_aplicar(composicion_t*, double);
    ```
    Considerar que primero se irán agregando las funciones como se leen, pero tener en cuenta el correcto orden
    de aplicación. Por ejemplo: para emular `f(g(x))`, se debe hacer:

        composicion_agregar_funcion(composicion, f);
        composicion_agregar_funcion(composicion, g);
        composicion_aplicar(composicion, x);

    Indicar el orden de las primitivas.

1. (★★★) Dada una lista enlazada implementada con las siguientes estructuras:

        typedef struct nodo_lista {
            struct nodo_lista* prox;
            void* dato;
        } nodo_lista_t;

        typedef struct lista {
            nodo_lista_t* prim;
        } lista_t;

    Escribir una primitiva que reciba una lista y devuelva el elemento que esté a $$k$$ posiciones del final (el
    ante-k-último), recorriendo la lista una sola vez y sin usar estructuras auxiliares. Considerar que
    $$k$$ es siempre menor al largo de la lista.
    Por ejemplo, si se recibe la lista `[ 1, 5, 10, 3, 6, 8 ]`, y `k = 4`, debe devolver 10.
    Indicar el orden de complejidad de la primitiva.


1.  (★★★) Dada una pila de enteros, escribir una función que determine si sus elementos están ordenados de manera ascendente. Una pila de enteros está ordenada de manera ascendente si, en el sentido que va desde el tope de la pila hacia el resto de elementos, cada elemento es menor al elemento que le sigue.
    La pila debe quedar en el mismo estado que al invocarse la función.
    Indicar y justificar el orden del algoritmo propuesto.

1.  (★★) Implementar la primitiva `void** cola_multiprimeros(const cola_t* cola, size_t k)` que dada una cola y un
    número $$k$$, devuelva los primeros $$k$$ elementos de la cola, en el mismo orden en el que habrían
    salido de la cola. En caso que la cola tenga menos de $$k$$ elementos, rellenar con NULL.
    Indicar y justificar el orden de ejecución del algoritmo.

1.  (★★) Implementar la función `void** cola_multiprimeros(cola_t* cola, size_t k)` con el mismo comportamiento de la
    primitiva anterior.

1.  (★★) Implementar en C una primitiva `void lista_invertir(lista_t* lista)` que invierta la lista recibida
    por parámetro, sin utilizar estructuras auxiliares. Indicar y justificar el orden de la primitiva.

1.  (★★) Se quiere implementar un TDA ColaAcotada sobre un arreglo. Dicho TDA tiene un espacio para $$k$$ elementos
    (que se recibe por parámetro al crear la estructura). Explicar cómo deberían implementarse las primitivas
    encolar y desencolar de tal manera que siempre sean operaciones de tiempo constante.

1.  (★★★★) Implementar una función que ordene de manera ascendente una pila de enteros sin conocer su estructura interna y
    utilizando como estructura auxiliar sólo otra pila auxiliar.
    Por ejemplo, la pila `[ 4, 1, 5, 2, 3 ]` debe quedar como `[ 1, 2, 3, 4, 5 ]` (siendo el último elemento el tope de la pila, en ambos casos). Indicar y justificar el orden de la función.

1.  (★★) Implementar una función `void cola_filtrar(cola_t* cola, bool (*filtro)(void*))`, que elimine los
    elementos encolados para los cuales la función _filtro_ devuelve `false`. Aquellos elementos que no son eliminados
    deben permanecer en el mismo orden en el que estaban antes de invocar a la función. No es necesario destruir los
    elementos que sí fueron eliminados. Se pueden utilizar las estructuras auxiliares que se consideren necesarias y
    no está permitido acceder a la estructura interna de la cola (es una función). ¿Cuál es el orden del algoritmo
    implementado?

1.  (★★★) Sabiendo que la firma del iterador interno de la lista enlazada es:

        void lista_iterar(lista_t* lista,
                          bool (*visitar)(void* dato, void* extra),
                          void* extra);

    Se tiene una lista en donde todos los elementos son punteros a números enteros. Implementar la función _visitar_ para que calcule la suma de todos los números pares. Mostrar, además, una invocación completa a `lista_iterar()` que haga uso del _visitar_ implementado.

1.  (★★★★★) Diseñar un TDA `PilaConMáximo`, que tenga las mismas primitivas de la pila convencional
    (en este caso, sólo para números), y además permita obtener el máximo de la pila. **Todas**
    las primitivas deben funcionar en $$\mathcal{O}(1)$$. Explicar cómo implementarías el TDA para
    que cumpla con todas las restricciones.
