---
math: true
---

# FAQ - Tipos de Datos Abstractos
{:.no_toc}

* Contenido
{:toc}

## Abstracción

### ¿Qué son los Generics?

Generics, en una forma simplista de explicarlo, es una forma de parametrizar una función, interfaz o estructura (`struct`) para que funcione con diferentes tipos de datos, sin necesidad de tener que definir el mismo TDA para que funcione con `string`, otro para `int` y así sucesivamente. A este generic se le pueden poner, eventualmente, restricciones.

### ¿Qué es una estructura en Go?

Una estructura en Go es un tipo de variables que nos permite almacenar distintos elementos dentro de ellas. Sirven para encapsular lo que refiere a una variable que contendrá distintos atributos. Su uso es con la palabra reservada de Go `struct`. Por ejemplo, para una entidad de persona, con edad y nombre, se define la estructura:

```golang
type persona struct {
    edad uint
    nombre string
    dni *int
}
```

Ahora, ya sabemos que el `struct persona` contiene una edad del tipo `uint` y una cadena para el nombre. También contiene un puntero al dni, que es un entero.

Para acceder a estos miembros de la estructura, se puede acceder tanto al atributo mismo, con el operador punto `juan.nombre`.


### ¿Por qué no puedo acceder a un miembro de una estructura de un TAD?

Los miembros de las estructuras (como `pila.cantidad`, por ejemplo) son datos internos de la implementación de cada tipo abstracto de datos, a los que no se debe acceder fuera del archivo `.go` en el que se encuentran las primitivas correspondientes al TAD.

Este es el principio básico de abstracción, que nos permite operar con una pila, una lista o un árbol sin tener en cuenta cómo están implementados, y que si la implementación cambia, el código que utiliza el TAD sigue funcionando sin necesidad de ser modificado.

Cuando se realizan pruebas sobre un TAD para verificar su comportamiento, no es necesario acceder a los miembros de la estructura, ya que lo que se desea verificar es que se comporte de la forma esperada y no cuáles son los valores utilizados internamente por la implementación.  Las pruebas deben funcionar aún si la implementación interna cambia (siempre que se respeten las primitivas).

## Redimensionamiento automático

Estas respuestas son útiles tanto para la pila dinámica, como para la tabla de hash, o cualquier otra estructura que deba agrandarse y achicarse automáticamente.

### ¿Cuánto conviene agrandar una estructura dinámica?

Hacer un realloc es una operación lenta: $$\mathcal{O}(n)$$ (siendo n la cantidad de bytes que se mantienen en el bloque de memoria).  De modo que es importante planificar cuánto se va a agrandar la estructura, para que el tiempo gastado en el redimensionamiento no influya en el comportamiento general de la estructura.

Para ello, lo que se hace es que al agrandar, el espacio utilizado se multiplique -generalmente por 2, pero puede ser por otro factor, según las condiciones del problema a resolver-, de modo que la incidencia del realloc se distribuya siempre de forma pareja entre los elementos, lo que no sucede en el caso de que la estructura crezca una cantidad constante. Una demostración formal sobre cómo afecta esta redimensión en el costo total de las operaciones puede encontrarse en la [lista de mails](https://groups.google.com/d/msg/fiuba-7541rw-alu/t86CJcNv2UU/Irb7J899DgAJ).

### ¿Cuándo y cuánto conviene achicar una estructura dinámica?

Si para agrandar la estructura multiplicamos su tamaño por 2, no es una buena idea reducirla a la mitad ni bien llega a la mitad de espacio utilizado, ya que en el caso de que se quisiera agregar un nuevo elemento, sería necesario agrandarla y si se lo quita, otra vez achicarla, por lo que en definitiva, habría una cantidad de elementos para la que las operaciones de agregar o sacar de la estructura serían particularmente lentas.

Es por eso que lo que se puede hacer es reducir la estructura a la mitad, pero sólo cuando la cantidad de espacio ocupada llega a 1/4 de la deseada.  De este modo, se libera la memoria fuera de uso, pero sin el riesgo de caer en un caso patológicamente lento.

Tanto en el caso de agrandar como el de achicar, se pueden tomar criterios distintos para buscar mayor eficiencia en tiempo o en memoria, según el problema a resolver.


## Iteradores

### ¿Qué es un iterador?

Es una construcción que nos permite recorrer los elementos almacenados dentro de una estructura en cierto orden. Por ejemplo, en un arreglo:

``` golang
var arr [TAM_ARR]double;
for i := 0; i < TAM_ARR; i++ {
    // Hacer algo con arr[i]
}
```

La variable `i` hace de iterador del arreglo `arr`.

En listas enlazadas, árboles, tablas de hash y otras estructuras ese `int i` no es suficiente para recorrer la estructura, por lo que se generaliza esa idea en el concepto de "iterador".

Las operaciones básicas que puede tener un iterador son:
  - `Iterador` (primitiva del TDA que me permite obtener su iterador)
  - ver_actual
  - avanzar/siguiente
  - ¿hay_siguiente?

### ¿Cómo se usan los iteradores de una estructura?

En la materia adoptamos la siguiente convención para todos los iteradores:
  - La creacion de un iterador en una estructura es siempre una operación válida:
  - Si la estructura tiene elementos, el iterador apunta al primer elemento.
  - Si la estructura no tiene elementos, el iterador se crea, pero apuntando al final.
  - Avanzar un iterador cuando no está al final siempre es una operación válida.
  - Avanzar un iterador que está al final es una operacion inválida, por lo que devuelve false.
  - Ver actual es siempre una operación válida. Cuando está al final devuelve siempre `NULL`.

Considerando esta convención, la forma canónica de iterar una estructura es la siguiente:

``` golang
iter := estructura.Iterador()

for iter.HaySiguiente() {
    dato := iter.Siguiente()
}
```

### Una vez que se llega al fin, ¿El iterador no sirve más?

En efecto, los iteradores son descartables, una vez que se termina de recorrer la estructura, sea porque está vacía o se llegó al final, el iterador termina su vida útil, hay que destruirlo y crear uno nuevo.
