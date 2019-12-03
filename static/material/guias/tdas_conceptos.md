---
title: Conceptos de TDAs, Pilas, Colas y Listas
layout: default
permalink: 'material/guias/tdas_conceptos'
math: true
---

# Conceptos de TDAs, Pilas, Colas y Listas
{:.no_toc}

## Contenidos

1. TOC
{:toc}

## Ejercicio resuelto

Implementar la _primitiva_ de la pila `void** pila_multitop(const pila_t* pila, size_t n)`, que devuelve un arreglo de tamaño $$n$$ con los $$n$$ topes de la pila (los primeros $$n$$ elementos si fueran desapilados) sin utilizar estructuras auxiliares. Completar el arreglo a devolver con NULL cuando el $$n$$ recibido por parámetro es mayor a la cantidad de elementos de la pila.

Indicar el orden de complejidad de la primitiva.

### Solución

Algo que está implícito en el ejercicio es que se asume que la implementación del TDA Pila es sobre un arreglo dinámico, tal
cual fue visto en clase. Siempre es válido asumir que la implementación es la misma a la que debieron implementar, salvo que
el enunciado especifique lo contrario. 


Dos cosas que son necesarias entender desde el inicio del ejercicio: 
1. 	En esa primitiva no se puede modificar la pila. No sólo porque se reciba un `const pila_t*`, sino porque sería erroneo
	modificar la pila si ya desde el vamos podemos acceder a los campos de la misma. 
2.  Se pide devolver un arreglo, pero es muy importante entender que sería un error **muy grave** devolver un arreglo de 
	memoria estática. Esto es, porque al terminar la ejecución de la función, el arreglo (la posición de memoria) pasaría
	a ser inválida. Esta clase de errores anulan ejercicios por completo. 

Una vez que esto quede claro, la solución es bastante directa: si queremos que los elementos sean aquellos que desapilaríamos, simplemente tendríamos que iterar el arreglo en ese orden. Dada la implementación de la pila, deberíamos
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

También sería válido hacerlo en dos iteraciones: una para llenar con los datos, y otra para rellenar con `NULL`s.
Así como también sería válido iterar hasta el más pequeño entre `n` y `pila->cantidad`, y haber inicializado de antes el
arreglo con `NULL`s (sea iterando o usando `calloc`). Otras tantas variantes también serían aceptadas, no hay una única forma de resolver este ejercicio. 

Sobre la complejidad, sea cual sea el caso, vamos a estar llenando siempre al arreglo de $$n$$ elementos con algo (datos de la pila, o `NULL`). Acceder a los elementos de la pila, siendo que accedemos directamente, es $$\mathcal{O}(1)$$, y nunca vamos a ver más elementos de la pila si son más de $$n$$, por ende la primitiva es $$\mathcal{O}(n)$$. 



## Ejercicios propuestos

1. 	Implementar una función que reciba un arreglo de `void*` e invierta su orden, utilizando los TDAs vistos.
	Indicar y justificar el orden de ejecución. 

1. 	Mismo a lo anterior, pero que el arreglo sea de `int` (no de `int*`), utilizando los TDAs tal cual se los
	implementa en clase.

1. 	Implementar en C el TDA `ComposiciónFunciones` que emula la composición de funciones (i.e. `f(g(h(x))`). 
	Se debe definir la estructura del TDA, y las siguientes primitivas:
		
		composicion_t* composicion_crear()
		void composicion_destruir(composicion_t*)
		bool composicion_agregar_funcion(composicion_t*, double (*f)(double))
		double composicion_aplicar(composicion_t*, double)

	Considerar que primero se irán agregando las funciones como se leen, pero tener en cuenta el correcto orden
	de aplicación. Por ejemplo: para emular `f(g(x))`, se debe hacer:
		
		composicion_agregar_funcion(composicion, f);
		composicion_agregar_funcion(composicion, g);
		composicion_aplicar(composicion, x);

	Indicar el orden de las primitivas.

1. Dada una lista enlazada implementada con las siguientes estructuras:

		typedef struct nodo_lista { 		typedef struct lista {
			struct nodo_lista* prox; 			nodo_lista_t* prim;
			void* dato; 			} lista_t;
		} nodo_lista_t;

	Escribir una primitiva que reciba una lista y devuelva el elemento que esté a $$k$$ posiciones del final (el
	ante-k-último), recorriendo la lista una sola vez y sin usar estructuras auxiliares. Considerar que
	$$k$$ es siempre menor al largo de la lista.
	Por ejemplo, si se recibe la lista `[ 1, 5, 10, 3, 6, 8 ]`, y `k = 4`, debe devolver 10.
	Indicar el orden de complejidad de la primitiva.


1. 	Dada una pila de enteros, escribir una función que determine si es piramidal. Una pila de enteros es
	piramidal si cada elemento es menor a su elemento inferior (en el sentido que va desde el tope de la 
	pila hacia el otro extremo). La pila no debe ser modificada al terminar la función.
	Indicar el orden del algoritmo propuesto. Justificar.

1. 	Implementar la primitiva `void** cola_multiprimeros(const cola_t* cola, size_t k)` que dada una cola y un 
	número $$k$$, devuelva los primeros $$k$$ elementos de la cola, en el mismo orden en el que habrían
	salido de la cola. En caso que la cola tenga menos de $$k$$ elementos, rellenar con NULL.
	La cola debe quedar en el mismo estado que al invocarse la primitiva.
	Indicar el orden de ejecución del algoritmo. Justificar.

1. 	Implementar la función `void** cola_multiprimeros(cola_t* cola, size_t k)` con el mismo comportamiento de la 
	primitiva anterior.

1. 	Implementar en C una primitiva void `lista_invertir(lista_t* lista)` que invierta la lista recibida
	por parámetro, sin utilizar estructuras auxiliares. Indicar y justificar el orden de la primitiva.

1. 	Se quiere implementar un TDA ColaAcotada sobre un arreglo. Dicho TDA tiene un espacio para $$k$$ elementos 
	(que se recibe por parámetro al crear la estructura). Explicar cómo deberían implementarse las primitivas 
	encolar y desencolar de tal manera que siempre sean operaciones de tiempo constante.

1. 	Implementar una función que ordene de manera ascendente una pila de enteros sin conocer su estructura interna y 
	utilizando como estructura auxiliar sólo una pila auxiliar.
	Por ejemplo, la pila `[ 4, 1, 5, 2, 3 ]` debe quedar como `[ 1, 2, 3, 4, 5 ]` (siendo el último elemento el tope de la pila, en ambos casos). Indicar y justificar el orden de la función.

1. 	Implementar una función `void cola_filtrar(cola_t* cola, bool (*filtro)(void*))`, que elimine los elementos encolados
	para los cuales la función filtro devuelve `false`. Aquellos elementos que no son eliminados deben permanecer en el
	mismo orden en el que estaban antes de invocar a la función. No es necesario destruir los elementos que sí fueron eliminados. Se pueden utilizar las estructuras auxiliares que se consideren necesarias y no está permitido acceder a la estructura interna de la cola (es una función). ¿Cuál es el orden del algoritmo implementado? 

1. Sabiendo que la firma del iterador interno de la lista enlazada es:

		void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra);

	Se tiene una lista en donde todos los elementos son punteros a números enteros. Implementar la función visitar para que calcule la suma de todos los números pares. Mostrar, además, la invocación a la función.


