# FAQ - Hash
{:.no_toc}

* Contenido
{:toc}

## ¿Qué son las claves y los datos dentro del hash?

La clave es la cadena mediante la cual se ubica el dato, tanto al guardarlo como al obtenerlo o borrarlo. Por ejemplo, si se guarda una estructura `Alumno`, la clave podría ser el padrón (como cadena o número) o el apellido, según con qué criterio se quiere guardar y luego encontrar los datos.

A esta clave será necesario aplicar la función de hashing, que debe devolver un número, y luego debemos asegurar que quede entre 0 y _m-1_, siendo _m_ el largo de la tabla de hash. La forma más usada de obtener un valor en este rango es aplicando la operación módulo _m_, que devuelve el resto de la división entera entre un número y _m_.

Las claves y los datos asociados se guardan en la tabla de hash como una pareja. Para esto usamos una estructura adicional (que se puede llamar, por ejemplo, `hashCampo` o `hashElem`).  De esta forma es posible recuperar el dato asociado a la clave cuando así se lo solicite.

## ¿Cómo se itera un hash abierto?

El objetivo del iterador es permitir recorrer todos los elementos de la tabla de hash, sin importar el orden en que se encuentren. Cada vez que se pide ver el elemento actual, se deben devolver tanto la clave como el dato, ya que el usuario no sabe cuál es ninguno de los dos.

Al crear el iterador, tiene que quedar apuntando al "primer" elemento que hay en el hash.  Para ello, tiene que verificar cuál es el primer balde que contiene una lista no-vacía, y de esa lista crear un iterador.

Al avanzar el iterador de hash, debe avanzar el iterador de la lista actual, y en el caso de que llegue al final, buscar la siguiente lista no vacía.

Debe indicar que llegó al final cuando ya no queden listas por recorrer.

## ¿Debo codificar una función de hashing propia?

No. Las funciones de hashing son un tema muy extenso en la computación, y no se pretende que se codifique una. Cabe destacar que estas pueden llegar a impactar sobre el rendimiento de la tabla de hash, así que de encontrarse con un hash que no rinde como uno esperaría, uno de las primeras cosas a probar es cambiar la función de hash.

## ¿Qué es esto de la función de igualdad?

En Go no podemos usar el operador `==` para tipos de dato `any`. Entonces, necesitamos de _algo_ que nos indique si dos claves son en efecto equivalentes (lo que haríamos con dicho `==`). Por lo tanto, lo que hacemos es recibir una función por parámetro al crear el hash que justamente nos determine si dos claves son en efecto iguales. 

Anteriormente (hasta 2025C1), para evitar esto, lo que se hacía es que el hash no trabaje con tipos de dato `any` como claves, sino con `comparable`, que es una restricción de Go que permite únicamente usar tipos de datos que soporten el uso del operador `==`. Esto traía algunas confusiones y problemas, por lo que desde 2025C2 decidimos cambiar esto por la función de equivalencia. 

## ¿Por qué la capacidad de una tabla de hash puede ser conveniente que sea un número primo?

Para obtener el mejor rendimiento de nuestra tabla de hash, queremos que las claves esten lo mejor distribuidas posibles en la capacidad. Es decir, que reduzcamos al mínimo posible las colisiones que obtendremos. Recordemos que una colisión es cuando dos claves van a parar al mismo 'balde' de la tabla de hash, sin importar si es abierto o cerrado.

A lo que nos referimos con esto es que si tenemos un hash con 5 baldes y tiene un elemento en cada uno de esos 5 baldes, la búsqueda de un elemento será más rápida que si tenemos los 5 elementos sobre el mismo balde, lo cual necesita de más operaciones.

Por otro lado, el concepto básico de una función de hashing es el de tomar una cadena y convertirla en un número. Más alla de la implementación de la función, ese número puede ser cualquier número. Ahora, suponiendo que la cadena 'holamundo' se encripte al número '3310', pero mi tabla de hash tiene una capacidad de 30 bloques, de alguna forma tengo que reducir el 3310 a un número entre 0 y 30. ¿Cómo hago esto? Facil! Con el operador de módulo (en código, el `%`), que es el resto de la división entre dos números. En este caso, `3310 mod 30 = 10`.

Entonces, con la idea de que queremos generar la menor cantidad de colisiones posibles, y que una colisión nos sucedera cuando el aplicarle modulo a dos números distintos sobre la capacidad nos de el mismo resultado, estamos en búsqueda de un número que distribuya lo mas variado posible los resultados al aplicarsele modulo.

Claramente, si se hace un modulo de un multiplo de un número a otro, el resultado sera 0, ya que la división es perfecta, sin resto.

```
4 mod 2 = 0
8 mod 2 = 0
16 mod 2 = 0
...
```

Extendiendo un poco esto, con la notación `n mod d = r`, cualquier n que comparta un factor común con d nos dará como resultado ese factor común. Entonces, cualquier multiplo de este n nos dara como resultado un multiplo de ese r. Por ejemplo:

```
18 mod 16 = 2 //18 y 16 comparten factor común 2
36 mod 16 = 4 //36 es múltiplo de 18, y su resultado es múltiplo de 2
54 mod 16 = 6
72 mod 16 = 8
...
20 mod 16 = 4 //20 también comparte factor común con 16, haciendo que vuelva a parar en el 4. Acá tenemos una colisión
40 mod 16 = 8//40 es múltiplo de 20, haciendo que vaya a parar a donde ya paró el 72. Otra colisión!
```

Entonces, estamos en búsqueda de un d que contenga la menor cantidad posible de factores, para que todo n que usemos comparta pocos factores con el, así logrando que la distribución sea variada. Y sabiendo que los números primos solo pueden dividirse por 1 o por si mismos, son un muy buen número para utilizar!

```
18 mod 7 = 4
36 mod 7 = 1
54 mod 7 = 5
20 mod 7 = 6
```

Cabe destacar que si las claves originales vienen distribuidas uniformemente, esto no soluciona el problema, porque nos dara resultados similares para cualquier capacidad utilizada. Pero, como en la mayoría de los casos las claves no vienen con distribución específica, terminamos concluyendo que lo mejor es usar un número primo como capacidad de la tabla de hash.

## ¿Cómo podemos asegurar que al redimensionar mantengamos un tamaño primo? 

En sí hay dos formas simples de hacer esto: 

1. Duplicar tamaño y luego, mientras el valor no sea un número primo, le sumamos 1. 
2. Tener una tabla de números primos cargada ya de antemano en el hash (que sea un arreglo constante ya precalculado).

El problema de la opción 1 es que nos hace perder toda ganancia. Determinar si un número es primo es al menos $$\mathcal{O}\left(\sqrt{n})$$. Si eso lo aplicamos hasta obtener un siguiente número primo, esto puede demorar demasiado, haciéndonos perder cualquier mínima ventaja que podríamos tener por utilizar un número primo. 

La segunda opción implica tener estado en el hash recordando en cuál índice de dicho arreglo estamos, y obviamente hacer un arreglo que pueda tener todos los posibles tamaños que pueda manejar el hash. 

En general, esta ventaja que obtenemos es mínima y no vale la pena la implementación de la opción 2 para los fines del curso y los usos que les damos al hash, por lo que simplificamos y simplemente duplicamos el tamaño de la tabla y listo. 

## ¿Por qué al redimensionar no puedo crear un hash nuevo?

Lo primero a entender es que no podemos redimensionar sobre la misma tabla que estábamos antes. De una forma u otra, necesitamos poder re-hashear los elementos sobre una tabla. 

Algo que surge como primera opción es "me creo un hash nuevo al que le agrego los datos, y listo, que ese sea el hash de ahora en más". El problema que surge de esa solución va a ser que luego de guardar el elemento nuevo e irnos de la función,
el hash "vuelve a como estaba antes", sin la clave reciéntemente guardada (en teoría) y sin la redimensión hecha. ¿Es acaso un bug en Go? No. El problema es conceptual de referencias (y punteros). 

Veamos un ejemplo básico. Supongamos que tenemos: 
```golang
func cambio(a int) {
	a = 10
}
// ...
b := 7
cambio(b)
```

La primera pregunta será: ¿Cuánto vale `b` luego de invocar `cambio`? Esperamos que no resulte difícil ver que sigue valiendo 7. Estamos modificando una variable local de la función `cambio` (que recibió su valor por copia, como todo en Go!) por ende cambiar la variable local no va a hacer que cambie el valor de quien poseía ese valor originalmente. El concepto para el caso del hash va a terminar siendo el mismo, pero nos vamos acercando. Modificamos un poco el ejemplo: 

```golang
func cambio(a *int) {
	a = new(int) // suponer que luego de la invocación devuelve 0xCAFE
	*a = 15
}
// ...
b := 10 // Suponer que la variable vive en 0xFECA
cambio(&b) 
```

¿Cuánto vale `b` luego de invocar `cambio`? Nuevamente, va a seguir valiendo lo mismo que antes (`0xFECA`). Lo que se modifica en `cambio` es una variable local. 

Entonces, ahora lo llevamos a nuestro caso del hash: 
```golang
func (hash *hash[K, V]) Guardar(clave K, dato V) { // esto vale tanto para el hash abierto como cerrado
	if hay que redimensionar {
		hash = _crearHash(...)
	}
	// ...

}
```

Lo que sucede es que al `Guardar` se le pasa un puntero al hash. Eso dentro de `guardar` lo tengo como una variable local. 
Por lo tanto, si yo hago `hash = _hash_crear(...)`, lo que hago es pisar la referencia (esa variable local). 
El hash "real" (el que me pasaron por parámetro) lo perdí (al menos para el scope de esta función), y todo lo que haga 
de acá en adelante no afecta al original. Eso incluye guardar el dato. Pero también la redimensión no se hizo porque 
lo que se hizo fue crear OTRO hash, por lo que el original no vio nada.

