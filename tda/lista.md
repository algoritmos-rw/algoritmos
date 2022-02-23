---
title: Lista
permalink: /tps/lista/
trabajo: Lista
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Lista enlazada
==============

Se incluye en [el sitio de descargas]({{site.skel}}) un ejemplo de uso de iteradores internos y externos.

Estas son las primitivas de listas que tienen que implementar.

En esta entrega les agregamos el requerimiento de escribir la documentación completa de las primitivas (`lista.go`), con sus correspondientes pre y post condiciones, para esto pueden usar de muestra los archivos de interfaces que ya utilizaron para la implementación de pilas y colas.

#### Primitivas de la lista
``` golang
type Lista interface {
	EstaVacia() bool
	InsertarPrimero(interface{})
	InsertarUltimo(interface{})
	BorrarPrimero() interface{}
	VerPrimero() interface{}
	VerUltimo() interface{}
	Largo() int
	ForEach(visitar func(interface{}))
	Iterador() IteradorLista
}
```

Además, es necesario tener la primitiva de creación de la lista enlazada (en `lista_enlazada.go`):
``` golang

func CrearListaEnlazada() *ListaEnlazada {
	//...
}
```

#### Primitiva del iterador interno

Como está indicado entre las primtivas, se debe implementar el iterador interno cuya firma es:

```golang
ForEach(visitar func(interface{}))
```

#### Primitivas del iterador externo

``` golang
type IteradorLista interface {
	VerActual() interface{}
	HaySiguiente() bool
	Siguiente() interface{}
	Insertar(interface{})
	Borrar() interface{}
}
```

#### Pruebas

Recordar que el archivo de pruebas debe estar en el paquete `lista_test`, mientras que `lista_enlazada` debe estar en el paquete `lista`. 

Considerar que todas las primitivas (exceptuando `ForEach`) deben funcionar en tiempo constante.

Las pruebas deben incluir los casos básicos de TDA similares a los contemplados para la pila y la cola, y adicionalmente debe verificar los siguientes casos del iterador externo:
1. Al insertar un elemento en la posición en la que se crea el iterador, efectivamente se inserta al principio.
1. Insertar un elemento cuando el iterador está al final efectivamente es equivalente a insertar al final.
1. Insertar un elemento en el medio se hace en la posición correcta.
1. Al remover el elemento cuando se crea el iterador, cambia el primer elemento de la lista.
1. Remover el último elemento con el iterador cambia el último de la lista.
1. Verificar que al remover un elemento del medio, este no está.
1. Otros casos borde que pueden encontrarse al utilizar el iterador externo.
Y los casos del iterador interno.

Al igual que en los casos anteriores, deberán entregar en formato digital, subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

**No olviden revisar las [preguntas frecuentes de la lista enlazada](/algo2/faq/lista-enlazada)**

---
### Bibliografia recomendada
* Weiss, Mark Allen, "Data Structures and Algorithm Analysis": *3.2. The List ADT*.
* Cormen, Thomas H. "Introduction to Algorithms": *10.2. Linked lists*.
