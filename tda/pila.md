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

Importante notar que la función debe devolver un elemento de tipo Pila, ya que la estructura no debe exportarse. 

Hay que escribir el archivo `pila_dinamica.go`, con la implementación de la estructura de la pila y de cada una de las primitivas incluidas en el encabezado.  Además de las primitivas, pueden tener funciones auxiliares, de uso interno, que no deben estar declaradas dentro de `pila.go`. En `pila.go` se encuentran únicamente las primitivas que el usuario de la pila tiene que conocer.

Además, deben incluir la primitiva para crear la pila:

```golang
func CrearPilaDinamica[T any]() Pila[T] {
	// ...
}
```

Les sugerimos la siguiente implementación para la estructura interna de la pila:

```golang
type pilaDinamica[T any] struct {
	datos    []T
	cantidad int // Cantidad de elementos almacenados.
}
```

Además de `pila_dinamica.go`, tienen que entregar otro archivo `pila_test.go`, que contenga las pruebas unitarias para verificar que la pila funciona correctamente, y que al ejecutarlo puede verificarse que todo funciona bien. Se permite y recomienda usar funciones auxiliares en donde crean necesario.
Es necesario separar los _tests_ en diferentes funciones que prueben los escenarios. No es válido tener un único _test_ que pruebe todo. 

El archivo `pila_dinamica.go` debe ser parte del paquete `pila` (tal y como se encuentra en el archivo base adjunto), y el archivo de pruebas debe ser parte del paquete `pila_test`.

Las pruebas deberán verificar que:
1. Se pueda crear una Pila vacía, y ésta se comporta como tal.
1. Se puedan apilar elementos, que al desapilarlos se mantenga el invariante de pila (que esta es LIFO). Probar con elementos diferentes, y ver que salgan en el orden deseado. 
1. _Prueba de volumen_: Se pueden apilar muchos elementos (1.000, 10.000 elementos, o el volumen que corresponda): hacer crecer la pila, y desapilar elementos hasta que esté vacía, comprobando que siempre cumpla el invariante. Recordar _no apilar siempre lo mismo_, validar que se cumpla siempre que el tope de la pila sea el correcto paso a paso, y que el nuevo tope después de cada `desapilar` también sea el correcto.
1. Condición de borde: comprobar que una pila vacía se comporte como recién creada.
1. Condición de borde: las acciones para desapilar y ver tope de una pila recién creada son inválidas.
1. Condición de borde: la acción para ver si una pila recién creada está vacía es verdadero.
1. Condición de borde: las acciones para desapilar y ver el tope de una pila a la que se le apiló y desapiló hasta estar vacía son inválidas.
1. Probar apilar diferentes tipos de datos: probar con una pila de enteros, con una pila de cadenas, etc...

Además de todos los casos no descriptos que ustedes crean necesarios.

La estructura de directorios del módulo/proyecto en el que se deberá trabajar es: 
```
tdas
   |--> pila
   	|---> pila.go
   	|---> pila_dinamica.go
   	|---> pila_test.go
   |--> go.mod
```

Revisar [el video de cómo realizar los módulos para las diferentes entregas](https://youtu.be/IZrQt-vR3E4).

Para compilar y verificar las pruebas:
1. Compilar todo el código:

        go build pila

1. Ejecutar las pruebas: 

        go test pila_test.go

Adicionalmente, pueden utilizar el _flag_ `-v` para que se muestre la salida de cada prueba, incluyendo _logs_ (esto es lo que se hace en el corrector automático).

Al igual que en los casos anteriores, deberán entregar el código en formato digital subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo. Se debe entregar un archivo `zip` con la carpeta `pila` (que dentro debe tener `pila_dinamica.go` y `pila_test.go`) así como el archivo `go.mod` (tanto la carpeta como el archivo `go.mod` deben estar en el mismo nivel, sin `.`). No es necesario enviar el archivo `pila.go`. Incluso, este será ignorado para evitar cualquier modificación sobre las primitivas.

**No olviden revisar las [preguntas frecuentes de la pila](/algoritmos/faq/pila)**.

---
### Bibliografia recomendada
* Weiss, Mark Allen, "Data Structures and Algorithm Analysis": *3.3. The Stack ADT*.
* Cormen, Thomas H. "Introduction to Algorithms": *10.1. Stacks and queues*.
