---
math: true
---

# Diccionarios, Hashing y Hash
{:.no_toc}

## Contenidos
{:.no_toc}

1. TOC
{:toc}

## Ejercicio resuelto

1. Para un hash cerrado, implementar una primitiva `func (hash hashCerrado[K, V]) Claves() Lista[K]` que reciba
un hash y devuelva una lista con sus claves, sin utilizar el iterador interno. 

1. Repetir lo mismo para un hash abierto.

1. Implementar de nuevo la operación, en este caso como una función.
{:.lower_alpha}

### Solución

Partiendo del punto _a)_, es importante notar que no podemos utilizar el iterador externo, ya que se trata de una primitiva para
el hash (y es una mala práctica que, dado que el iterador dependa del hash, ahora hagamos que el hash dependa del iterador).

#### Hash Cerrado

Para este punto, sólo es necesario iterar campo por campo, considerando únicamente aquellos que están ocupados.

```golang
func (hash hashCerrado[K, V]) Claves() Lista[K] {
    claves := CrearListaEnlazada[K]()
    for _, celda := range hash.tabla {
        if celda.estado == OCUPADO {
            claves.InsertarUltimo(celda.clave)
        }
    }
    return claves
}
```

Es importante notar que en este ejercicio se está evaluando que sabemos trabajar internamente con el hash cerrado. Los puntos importantes:

* Sabemos cuáles son los campos de la estructura.

* Sabemos que la tabla es de tipo `[]campo[K, V]` o bien `[]celda[K, V]`, y no `[]*celda[K, V]`, puesto que es completamente innecesario otro grado de indirección (como se analiza en la respectiva clase práctica).

* Entendemos que el estado correcto a considerar es el de `OCUPADO`, que es un enumerativo. Cuanto mucho, una constante. Definitivamente no un `"ocupado"`.


#### Hash Abierto

Para este caso, consideramos todas las listas, las cuales podemos ir iterando utilizando el iterador externo o interno. Aquí mostramos una implementación utilizando el iterador interno, no porque sea mejor implementación, sino para que tengan un ejemplo de uso (ya que probablemente la primera idea que tengan ustedes será con el externo).

```golang
func (hash hashAbierto[K, V]) Claves() Lista[K] {
    claves := CrearListaEnlazada[K]()
    for _, lista := range hash.tabla {
        lista.Iterar(func (par parClaveValor[K, V]) bool {
            claves.InsertarUltimo(par.clave)
            return true
        })
    }
    return claves
}
```

_Aclaración_: Hay quienes deciden implementar el Hash Abierto de tal forma que
no tenga listas vacías (esto es, si una posición aún
no ha sido utilizada, entonces se guarda `nil` y se crea la lista cuando sea necesaria). Esto es totalmente válido, y en todo
caso con aclararlo en algún lado es suficiente (pero debe hacerse la validación contra `nil` en ese caso).

#### Función

En este caso, no sólo sí está permitido utilizar el iterador externo del hash,
sino que **no nos queda otra opción**, dado que no es posible acceder a los
campos internos de la estructura. Además, en particular no se nos dice cuál es la implementación, cosa que no es necesario conocer.

Entonces, simplemente iteramos utilizando el iterador externo y guardamos en una lista.

```golang
func ClavesDiccionario(dic Diccionario) Lista[K] {
    claves := CrearListaEnlazada[K]()
    for iter := dic.Iterador(); iter.HaySiguiente(); iter.Siguiente() {
	clave, _ := iter.VerActual()
        claves.InsertarUltimo(clave)
    }
    return claves
}
```

#### Utilizando el iterador interno

Ahora implementamos también (ya sea como función o primitiva) utilizando el iterador interno exclusivamente: 

```golang
func (hash hashAbierto[K, V]) Claves() Lista[K] { // Vale también para el cerrado y como función
    claves := CrearListaEnlazada[K]()
    hash.Iterar(func (clave K, valor V) bool {
        claves.InsertarUltimo(clave)
        return true
    })
    return claves
}
```

## Ejercicios propuestos

1.  (★) Suponer que se tiene un hash cerrado que se redimensiona cuando el factor de carga llega a 0.75, y que
    no se tienen en cuenta los elementos borrados a la hora de calcular el factor de carga.

    {:.lower_alpha}
    1. Describir, en términos generales, el peor escenario posible para esta implementación.

    1. Dado un hash de estas características, con capacidad inicial 100, calcular el número máximo de casillas que podría llegar a visitar `hash_obtener()` si la cantidad actual de elementos en el hash es 1, y no se realizó ningúna redimensión, pero sí se insertaron y borraron elementos. (En otras palabras, poner una cota superior al caso peor de este hash.)

1.  (★) ¿Para qué casos la función `hash_obtener()` tiene una complejidad peor que $$\mathcal{O}(1)$$? Explicar tanto para el hash abierto, como el cerrado.

1.  (★) Justificar si la siguiente función de hashing es correcta o no:
    ```golang
    func calcularHash(string clave) int {
        // rand.Intn(x) devuelve un numero entero entre 0 y x
        return rand.Intn(10000)
    }
    ```

1.  (★★) a. Mostrar el resultado de las siguientes operaciones tanto para un hash cerrado como para un hash abierto,
    ambos de capacidad 9 e inicialmente vacíos (los números son también el resultado de la función de hashing): insertar 17, insertar 22,
    insertar 35, borrar 17, insertar 52, insertar 54.

    b. Tras estas inserciones ¿qué pasos hay que seguir para verificar si el 70 pertenece al hash?

    c. Posteriormente se realizan más inserciones. ¿Cuándo redimensionaría cada hash?
    ¿Qué pasos hay que seguir para hacerlo?

1.  (★★) Implementar una función de orden $$\mathcal{O}(n)$$ que dado un arreglo de _n_ números enteros devuelva `true`
    o `false` según si existe algún elemento que aparezca más de la mitad de las veces. Justificar el orden de
    la solución. Ejemplos:

        [1, 2, 1, 2, 3] -> false
        [1, 1, 2, 3] -> false
        [1, 2, 3, 1, 1, 1] -> true
        [1] -> true

1.  (★★) Asumiendo que se tiene disponible una implementación completa del TDA Hash, se desea implementar una función
    que decida si dos Hash dados representan o no el mismo Diccionario. Considere para la solución que
    es de interés la mejor eficiencia temporal posible. Indique, para su solución, eficiencia en tiempo y espacio.
    Nota: Dos tablas de hash representan el mismo diccionario si tienen la misma cantidad de elementos; todas las claves
    del primero están en el segundo; todas las del segundo, en el primero; y los datos asociados a cada una de esas claves son iguales (se pueden comparar los
    valores con "==").

1.  (★★) Implementar el TDA MultiConjunto. Este es un Conjunto que permite más de una aparición de un elemento,
    por lo que eliminando una aparición, el elemento puede seguir perteneciendo. Dicho TDA debe tener como
    primitivas:
    * `CrearMulticonj[K]()`: crea un multiconjunto.
    * `Guardar(elem K)`: guarda un elemento en el multiconjunto. 
    * `Pertence(elem K) bool`: devuelve `true` si el elemento aparece al menos una vez en el conjunto.
    * `Borrar(elem K) bool`: elimina *una aparición* del elemento dentro del conjunto. Devuelve `true` 
    si se eliminó una aparición del elemento.

    Dar la estructura del TDA y la implementación de las 4 primitivas marcadas, de forma tal que todas sean
    $$\mathcal{O}(1)$$.

1.  (★★★) $$\spadesuit$$ Se tiene un hash que cuenta con una función de hashing que, recibida una clave,
    devuelve la posición de su inicial en el abecedario. La capacidad inicial del hash
    es 26. Para los puntos B, C y D indicar y justificar si las afirmaciones son
    verdaderas o falsas. Se puede considerar que todas las claves serán palabras
    (sólo se usan letras para las claves).

    a. Mostrar cómo quedan un hash abierto y un hash cerrado (sólo el resultado final)
    tras guardar las siguientes claves: Ambulancia (0), Gato (6), Manzana (12), Ananá (0),
    Girasol (6), Zapato (25), Zapallo (25), Manzana (12), Bolso (1).
    _Aclaración_: No es necesario hacer una tabla de 26 posiciones, lo importante es que
    quede claro en cuál posición está cada elemento.

    b. En un hash **abierto** con dicha función de hashing, se decide redimensionar cuando la
    cantidad alcanza la capacidad (factor de carga = 1). El rendimiento de
    `hash_obtener()` es mejor en este caso respecto a si se redimensionara al alcanzar
    un factor de carga 2.

    c. En un hash **cerrado** con dicha función de hashing, si se insertan `n + 1` claves diferentes
    (considerar que se haya redimensionado acordemente), `n` con la misma letra
    inicial, y 1 con otra distinta, en el primer caso `Obtener()` es $$\mathcal{O}(n)$$ y en el
    segundo siempre $$\mathcal{O}(1)$$.

    d. En un hash **abierto** con dicha función de hashing, si se insertan `n + 1` claves diferentes
    (considerar que se haya redimensionado acordemente), `n` con la misma letra
    inicial, y 1 con otra distinta, en el primer caso `Obtener()` es $$\mathcal{O}(n)$$ y en el
    segundo siempre $$\mathcal{O}(1)$$.

1.  (★★★) El Ing. Musumeci quiere implementar un hash abierto, pero en el que las listas de cada posición
    se encuentren ordenadas por clave (se le pasa por parmámetro la función de comparación, por ejemplo 
    `strcmp`). Explicar cómo mejora o empeora respecto a la versión que vemos en clase para el caso de 
    inserciones, borrados, búsquedas con éxito (el elemento se encuentra en el hash) y sin éxito (no se encuentra).


1.  (★★) En un diccionario todas las claves tienen que ser diferentes, no así sus valores.
    Escribir en Go una primitiva para el hash cerrado `func (dicc *hashCerrado[K, V]) CantidadValoresDistintos() int` que, 
    sin usar el iterador interno, dado un hash devuelva la cantidad de **valores** diferentes que almacena. Se puede suponer que el tipo `V` (el genérico de los valores) en este caso también es `comparable`, como
    lo son las claves. Indicar y justificar el orden del algoritmo.


1.  (★★★) $$\spadesuit$$ La diferencia simétrica entre dos conjuntos A y B es un conjunto que
    contiene todos los elementos que se encuentran en A y no en B, y
    viceversa.

    Implementar una _función_ 
    `DiferenciaSimetricaDict[K comparable, V any](d1, d2 Diccionario[K, V]) Diccionario[K, V]`
    que devuelva un nuevo Diccionario (puede ser el hash que hayas implementado) 
    con la diferencia simétrica entre los dos
    recibidos por parámetro. La diferencia tiene que ser calculada
    teniendo en cuenta las claves, y los datos asociados a las claves
    deben ser los mismos que estaban en cada uno de los hashes
    originales. 
    Ejemplo:

    ```
    d1 = { "perro": "guau", "gato": "miau", "vaca": "mu" }
    d2 = { "perro": "woof", "zorro": "ding-ding" }
    DiferenciaSimetricaDict(d1, d2) => { "gato": "miau", "vaca": "mu", "zorro": "ding-ding" }
    ```

    Indicar y justificar el orden de la función implementada.

1.  (★★) Una fábrica de pastas de Lanús le pide a alumnos de Algoritmos y Estructuras de Datos que 
    le solucionen un problema: sus dos distribuidoras de materias primas le enviaron un 
    hash cada una, dónde sus claves son los nombres de los productos, y sus valores 
    asociados, sus precios. La fábrica de pastas le pide a los alumnos que le implementen 
    una **función** que le devuelva un nuevo hash con la unión de todos esos productos, 
    y en caso de que una misma materia prima se encuentre en ambos hashes, elegir la que tenga 
    el precio más barato. 
    Indicar y justificar el orden del algoritmo.

1.  (★★★★★) Se quiere implementar un TDA Diccionario con las siguientes primitivas:
    `Obtener(x)` devuelve el valor de `x` en el diccionario; `Insertar(x, y)` inserta en el diccionario
    la clave `x` con el valor `y` (entero); `Borrar(x)` borra la entrada de `x`; `Add(x, n)` le
    suma `n` al contenido de `x`; `AddAll(m)` le suma `m` a **todos** los valores.

    Proponer una implementación donde **todas** las operaciones sean $$\mathcal{O}(1)$$. Justificar el
    orden de las operaciones.
    
1.  (★★★) $$\spadesuit$$ Implementar un algoritmo que reciba un arreglo desordenado de enteros, su largo ($$n$$) y un 
	número $$K$$ y determinar en $$\mathcal{O}(n)$$ si existe un par de elementos en el arreglo que 
	sumen exactamente $$K$$.
