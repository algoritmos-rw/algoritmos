---
title: Pila
permalink: /tps/pila/
trabajo: Pila
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Pila
====

El trabajo a realizar es el de una implementación de pila dinámica (es decir, una pila sobre un arreglo que pueda crecer o reducirse según la cantidad de elementos) que contenga datos genéricos.

En el adjunto en [el sitio de descargas]({{site.skel}}) encontrarán el archivo `pila.go` que tienen que utilizar. En este archivo están definidas las primitivas que tendrán que implementar, con su correspondiente documentación. Todas las primitivas tienen que funcionar en _tiempo constante_.
Además, deben incluir la primitiva para crear la pila:

```golang
func CrearPilaDinamica[T any]() Pila[T] {
	// ...
}
```

Importante notar que la función debe devolver un elemento de tipo Pila, ya que la estructura no debería exportarse. 

Hay que escribir el archivo `pila_dinamica.go`, con la implementación de la estructura de la pila y de cada una de las primitivas incluidas en el encabezado.  Además de las primitivas, pueden tener funciones auxiliares, de uso interno, que no deben estar declaradas dentro de `pila.go`. En `pila.go` se encuentran únicamente las primitivas que el usuario de la pila tiene que conocer.

Les sugerimos la siguiente implementación para la estructura interna de la pila:

``` golang
type pilaDinamica[T any] struct {
	datos    []T
	cantidad int // Cantidad de elementos almacenados.
}
```

Además de `pila_dinamica.go`, tienen que entregar otro archivo `pila_test.go`, que contenga las pruebas unitarias para verificar que la pila funciona correctamente, y que al ejecutarlo puede verificarse que todo funciona bien. Se permite (y recomienda) usar funciones auxiliares en donde crean necesario.
Es necesario separar los tests en diferentes funciones que prueben los escenarios. No es válido tener un único test que pruebe todo. 

El archivo `pila_dinamica.go` debe ser parte del paquete `pila` (tal y como se encuentra en el archivo base adjunto), y el archivo de pruebas debe ser parte del paquete `pila_test`.

Las pruebas deberán verificar que:
1. Se pueda crear una Pila vacía, y esta se comporta como tal.
1. Se puedan apilar elementos, que al desapilarlos se mantenga el invariante de pila (que esta es LIFO). Probar con elementos diferentes, y ver que salgan en el orden deseado. 
1. _Prueba de volumen_: Se pueden apilar muchos elementos (1000, 10000 elementos, o el volumen que corresponda): hacer crecer la pila, y desapilar elementos hasta que esté vacía, comprobando que siempre cumpla el invariante. Recordar _no apilar siempre lo mismo_, validar que se cumpla siempre que el tope de la pila sea el correcto paso a paso, y que el nuevo tope después de cada `desapilar` también sea el correcto.
1. Condición de borde: comprobar que al desapilar hasta que está vacía hace que la pila se comporte como recién creada.
1. Condición de borde: las acciones de desapilar y ver_tope en una pila recién creada son inválidas.
1. Condición de borde: la acción de esta_vacía en una pila recién creada es verdadero.
1. Condición de borde: las acciones de desapilar y ver_tope en una pila a la que se le apiló y desapiló hasta estar vacía son inválidas.
1. Probar apilar cosas diferentes: probar con una pila de enteros, con una pila de cadenas, etc...

Además de todos los casos no descriptos que ustedes crean necesarios.

Para compilar y verificar las pruebas:
1. Compilar todo el código:

        go build pila

1. Ejecutar las pruebas: 

		go test pila_test.go

Adicionalmente, pueden utilizar el flag `-v` para que se muestre la salida de cada prueba, incluyendo logs (esto es lo que se hace en el corrector automático).

Al igual que en los casos anteriores, deberán entregar el código en formato digital subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo. Se debe entregar un archivo `zip` con todos los archivos (sin subcarpetas). No es necesario enviar el archivo `pila.go`. Incluso, este será ignorado para evitar cualquier modificación sobre las primitivas.

---
### Bibliografia recomendada
* Weiss, Mark Allen, "Data Structures and Algorithm Analysis": *3.3. The Stack ADT*.
* Cormen, Thomas H. "Introduction to Algorithms": *10.1. Stacks and queues*.


