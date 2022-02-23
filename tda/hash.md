---
title: Hash
permalink: /tps/hash/
trabajo: Hash
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Tabla de Hash
=============

El trabajo que deben entregar de **forma grupal** es el tipo abstracto de datos Diccionario, con una implementación de Tabla de Hash, que se puede implementar mediante un hash abierto o cerrado, a elección.

#### Primitivas del Diccionario
``` golang
type Diccionario interface {
	Guardar(clave interface{}, dato interface{})
	Pertenece(clave interface{}) bool
	Obtener(clave interface{}) interface{}
	Borrar(clave interface{}) interface{}
	Cantidad() int
	ForEach(func(clave interface{}, dato interface{}))
	Iterador() IterDiccionario	
}
```

Además, la primitiva de creación del Hash deberá ser: 
```golang
func CrearHash(funcion_hash func(interface{}) int, comparacion func(interface{}, interface{}) int) HashAbierto o HashCerrado
```

La primer función pasada por parámetro será una función hashing, que recibirá una clave y devolverá un número. 
La segunda función es una función de comparación, que tomará dos claves e indicará la relación entre estas. Debe devolver lo siguiente:
* Un entero menor que 0 si la primera cadena es menor que la segunda.
* Un entero mayor que 0 si la primera cadena es mayor que la segunda.
* 0 si ambas claves son iguales.

Nuevamente, el iterador interno (`ForEach`) debe iterar internamente el hash, aplicando la función pasada por parámetro a la clave y los datos. 


#### Primitivas del iterador
``` golang
type IterDiccionario interface {
	HaySiguiente() bool
	VerActual() (interface{}, interface{})
	Siguiente() interface{}
}
```

El iterador debe permitir recorrer todos los elementos almacenados en el hash, sin importar el orden en el que son devueltos.


### Pruebas

Se adjunta, además, un [archivo de pruebas]({{site.skel}}) que pueden utilizar para verificar que la estructura funciona correctamente.  El corrector automático, igualmente, puede añadir más pruebas. Para esta entrega no es necesario entregar pruebas propias.

Al igual que para las entregas anteriores, deberán entregar el código en formato digital, subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

Para ejecutar las pruebas, incluyendo las pruebas de volumen (benchmarks, que toman los tiempos y consumos de memoria), ejecutar: 

	go test -bench=. -benchmem

**No olviden revisar las [preguntas frecuentes del hash](/algo2/faq/hash)**

---
### Bibliografia recomendada
* Weiss, Mark Allen, "Data Structures and Algorithm Analysis": *Chapter 5: Hashing*.
* Cormen, Thomas H. "Introduction to Algorithms": *11. Hash Tables*.
