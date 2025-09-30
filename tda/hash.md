---
title: Hash
permalink: /tps/hash/
trabajo: Hash
---
{% assign TP = site.data.trabajos[page.trabajo] %}

Tabla de *Hash*
=============

El trabajo que deben entregar de **forma grupal** es el tipo abstracto de datos Diccionario, con una implementación de Tabla de *Hash*, que se puede implementar mediante un hash abierto o cerrado, a elección. En caso de tratarse de un *hash* abierto, pueden simplemente importar la lista por estar en el mismo módulo. En ese caso, en el archivo ZIP a entregar, además de encontrarse el directorio `diccionario`, debe estar el directorio `lista` con los archivos correspondientes. Estos deben estar en un mismo módulo `tdas`. 

#### Primitivas del Diccionario
```GoLang
type Diccionario[K any, V any] interface {
	Guardar(clave K, dato V)
	Pertenece(clave K) bool
	Obtener(clave K) V
	Borrar(clave K) V
	Cantidad() int
	Iterar(func(clave K, dato V) bool)
	Iterador() IterDiccionario[K, V]
}
```

Tanto `Borrar` como `Obtener` deben entrar en pánico con el mensaje `'La clave no pertenece al diccionario'` en caso que la clave no se encuentre en el diccionario. 

Además, la primitiva de creación del *hash* deberá ser: 
```GoLang
func CrearHash[K any, V any](func(K, K) bool) Diccionario[K, V]
```

La función pasada por parámetro es una que indica si dos claves son en efecto la misma clave (dado que no es posible usar `==` con datos genéricos en Go, salvo que restrinjamos las claves a tipos de datos `comparable`s). 

Nuevamente, el iterador interno (`Iterar`) debe iterar internamente el *hash*, aplicando la función pasada por parámetro a la clave y los datos.

#### Función de *hashing*... ¿Genérica?

Es de considerar que para implementar el *hash* será necesario definir una función de *hashing* internamente. Pueden definir la que más les guste (siempre poniendo referencia o nombre de la misma). Lamentablemente, no podemos trabajar de forma completamente genérica con una función de *hashing* directamente, por lo que deberemos realizar una transformación. 
Si bien no es obligatorio pasar la clave a un arreglo de *bytes* (`[]byte`), es lo recomendado. Luego, la función de *hashing* puede siempre trabajar con la versión de arreglo de *bytes* correspondiente a la clave. El siguiente código (que pueden utilizar, modificar, o lo que gusten) transforma un tipo de dato genérico a un *array* de *bytes*:
```GoLang
func convertirABytes[K any](clave K) []byte {
	return []byte(fmt.Sprintf("%v", clave))
}
```
Para utilizar [`fmt.Sprintf`](https://pkg.go.dev/fmt#Sprintf), se debe importar `fmt`. 


#### Primitivas del iterador
```GoLang
type IterDiccionario[K any, V any] interface {
	HaySiguiente() bool
	VerActual() (K, V)
	Siguiente()
}
```

El iterador debe permitir recorrer todos los elementos almacenados en el *hash* sin importar el orden en el que son devueltos.

Tanto `VerActual` como `Siguiente` deben entrar en pánico con el mensaje `'El iterador termino de iterar'` si ya no quedan elementos a iterar (i.e. `HaySiguiente() == false`).


### Pruebas

Se adjunta, además, un [archivo de pruebas]({{site.skel}}) que pueden utilizar para verificar que la estructura funciona correctamente.  El corrector automático, igualmente, puede añadir más pruebas. Para esta entrega **no es necesario entregar pruebas propias**.

Al igual que para las entregas anteriores, deberán entregar el código en formato digital, subiendo el código a la [página de entregas de la materia]({{site.entregas}}), con el código completo.

Para ejecutar las pruebas, incluyendo las pruebas de volumen (*benchmarks*, que toman los tiempos y consumos de memoria), ejecutar: 

	go test -bench=. -benchmem


**No olviden revisar las [preguntas frecuentes del *hash*](/algoritmos/faq/hash)**.

---
### Bibliografía recomendada
* Weiss, Mark Allen, *Data Structures and Algorithm Analysis*: *Chapter 5: Hashing*.
* Cormen, Thomas H. *Introduction to Algorithms*: *11. Hash Tables*.
