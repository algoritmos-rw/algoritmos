# FAQ - Hash
{:.no_toc}

* Contenido
{:toc}

## ¿Qué son las claves y los datos dentro del hash?

La clave es la cadena mediante la cual se ubica el dato, tanto al guardarlo como al obtenerlo o borrarlo. Por ejemplo, si se guarda una estructura `alumno_t`, la clave podría ser el padrón (como cadena) o el apellido, según con qué criterio se quiere guardar y luego encontrar los datos.

A esta clave será necesario aplicar la función de hashing, que debe devolver un número entre 0 y _m-1_, siendo _m_ el largo de la tabla de hash. La forma más usada de obtener un valor en este rango es aplicando la operación módulo _m_, que devuelve el resto de la división entera entre un número y _m_.

Las claves y los datos asociados se guardan en la tabla de hash como una pareja. Para esto usamos una estructura adicional (que se puede llamar, por ejemplo, `hash_campo_t` o `hash_elem_t`).  De esta forma es posible recuperar el dato asociado a la clave cuando así se lo solicite.

## ¿Por qué se crean copias de las claves al guardar?

Las claves en nuestra implementación del hash son cadenas, que en C son arreglos
de caracteres. Si no se hicieran copias de las claves, el usuario podría
modificar la cadena (sin cambiar el puntero). Tal cambio podría ocasionar que la
función de hash devuelva un resultado diferente, haciendo que el par clave–valor
fuera imposible de localizar nuevamente.

## ¿Cómo se itera un hash abierto?

El objetivo del iterador es permitir recorrer todos los elementos de la tabla de hash, sin importar el orden en que se encuentren. Cada vez que se pide ver el elemento actual, se deben devolver tanto la clave como el dato, ya que el usuario no sabe cuál es ninguno de los dos.

Al crear el iterador, tiene que quedar apuntando al "primer" elemento que hay en el hash.  Para ello, tiene que verificar cuál es el primer balde que contiene una lista no-vacía, y de esa lista crear un iterador.

Al avanzar el iterador de hash, debe avanzar el iterador de la lista actual, y en el caso de que llegue al final, buscar la siguiente lista no vacía.

Debe indicar que llegó al final cuando ya no queden listas por recorrer.

## ¿Cómo se destruye un hash abierto?

La lista que está asociada a cada uno de los baldes de la tabla de hash debe contener parejas de clave-valor.  De modo que si al momento de destruir la lista se le pasara una función de destrucción del dato, esta función debería destruir estas parejas.  Pero el usuario almacena en el hash una función de destrucción del valor almacenado, a la que no se puede acceder desde la función de destrucción del dato de la lista.

La forma más sencilla de resolver este problema es, entonces, ir llamando a la función `lista_borrar_primero` hasta que la lista se encuentre vacía y destruir apropiadamente cada uno de los elementos que se van sacando de la lista.

## ¿Debo codificar una función de hashing?

No. Las funciones de hashing son un tema muy extenso en la computación, y no se pretende que se codifique una. Cabe destacar que estas pueden llegar a impactar sobre el rendimiento de la tabla de hash, así que de encontrarse con un hash que no rinde como uno esperaría, uno de las primeras cosas a probar es cambiar la función de hash.

## ¿Por qué la capacidad de una tabla de hash debe ser un número primo?

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
