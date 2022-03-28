---
title: Cola
permalink: /tps/cola/
trabajo: Cola
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Cola enlazada
=============

Se incluye en [el sitio de descargas]({{site.skel}}) el archivo `cola.go` correspondiente al ejercicio de la cola enlazada.

La entrega es muy similar a la realizada para el TDA Pila. La función para crear la cola debe ser: 

```golang
func CrearColaEnlazada[T any]() Cola[T] {
	// ...
}
```
La cola debe ser enlazada, es decir que en lugar de usar un arreglo, usa nodos enlazados, de los cuales se desencola el primero y se encola a continuación del último. Por tanto, se debe implementar solamente con punteros, y no se debe guardar en un campo el tamaño de la cola. El archivo a entregar para la implementación debe ser `cola_enlazada.go`, que se encuentre en el paquete `cola`.

Deben entregar también un archivo `cola_test.go` (que esté dentro del paquete `cola_test`) que haga las correspondientes pruebas unitarias, análogas a las pedidas para Pila, obviamente considerando que el invariante cambia a su opuesto (FIFO).

Deberán entregar el código en formato digital, subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

**No olviden revisar las [preguntas frecuentes de la cola](/algo2/faq/cola)**

---
### Bibliografia recomendada
* Weiss, Mark Allen, "Data Structures and Algorithm Analysis": *3.4. The Queue ADT*.
* Cormen, Thomas H. "Introduction to Algorithms": *10.1. Stacks and queues*.
