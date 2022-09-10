# FAQ - Pila
{:.no_toc}

* Contenido
{:toc}

## Problemas con la función de creación:

#### No entendí bien cómo es lo de la función de creación...

La firma de la función de creación es: 
```golang
func CrearPilaDinamica[T any]() Pila[T]
```

Es decir, la función es para crear nuestro tipo específico (siempre va a haber algo así al final del día), pero la misma devuelve el tipo interfaz. Esto es por dos razones, uno conceptual y otro técnico: 
* Conceptual: no queremos exponer en absoluto a la implementación, así que devolvemos una `Pila` (el tipo de la interfaz, el TDA propiamente dicho). De esta forma _Bárbara_ no necesita saber de la existencia siquiera del struct de la implementación. Por otro lado, nos permite (didácticamente) poder separar aún más la interfaz de la implementación, y que quede claro que _Bárbara_ trabaja contra la interfaz. 
* Técnico: por lo anterior, y al no querer exportar los tipos específicos, la implementación no se exportar (es decir, se llama `pilaDinamica`, no `PilaDinamica`). Si la firma fuera `CrearPilaDinamica[T any]() pilaDinamica[T]`, _Bárbara_ no podría usarla porque como el tipo no se exporta, no va a poder trabajar con ella. Incluso, es posible que directamente esto no compile por esta razón: la función se exporta, pero el tipo que devuelve no. 

Este tamaño inicial debe ser definido por _Alan_ y, esperamos, sea una _constante_. 

#### La función de creación no me compila y no me queda del todo claro con el mensaje del compilador. 

Acá pueden suceder diferentes cosas. Supongamos que tenemos el siguiente código: 

```golang
func CrearPilaDinamica[T any]() T[] {
    pila := pilaDinamica{}
    // hago lo que deba hacer
    return pila
}
```

Esto va a fallar porque necesitamos devolver si o si un puntero. La explicación completa de por qué es eso se ve en clase. Entonces:
```golang
func CrearPilaDinamica[T any]() T[] {
    pila := new(pilaDinamica)
    // hago lo que deba hacer
    return pila
}
```

Esto nuevamente fallará. Y aquí si el error del compilador puede no ser del todo claro. Lo que sucede es que `pila` es un `pilaDinamica`, y no así una `pilaDinamica[T]`, que es lo que _matchea_ con el tipo `Pila[T]`. Es decir, falta el generic. Y el mensaje es literalmente que no matchea el tipo nada más (lo cual puede ser cierto, como veremos en el siguiente caso). Entonces:
```golang
func CrearPilaDinamica[T any]() T[] {
    pila := new(pilaDinamica[T]) // se agrega el generic
    // hago lo que deba hacer
    return pila
}
```

#### Eso no resolvió mi problema, me sigue sin compilar esa función!

Lo anterior funcionaría en tanto y en cuanto nuestro tipo de dato efectivamente se trate de una pila. Que se llame `pilaSarasa` no lo vuelve una `Pila`. Lo que lo vuelve `Pila` es justamente cumplir con su interfaz. Es decir, tener sus primitivas. 
Entonces, lo que hay que hacer es tener las primitivas definidas para el tipo de dato. Con eso, y asegurándose de no tener los errores marcados arriba, la función de creación ya no debería presentar más problemas de compilación. 

## Detalles de Implementación: ¿dónde está la redimensión?

#### ¿Cómo se va a redimensionar si el tipo `Pila` no tiene primitiva de redimensionar, como sí lo tenía el vector?

La redimensión es algo completamente interno a esta implementación, porque hay un arreglo/slice. Si la implementación fuera diferente, podría no ser necesaria, por lo que no tiene sentido que `Pila` tenga una primitiva de redimensión. 

#### ¿Cuál es el tamaño inicial de la pila, si no lo recibimos en el Crear?

Similar a la respuesta anterior: que haya un tamaño inicial es puramente un detalle de implementación, porque aquí hay un arreglo. Si fuera otra la implementación, no tendría sentido ese número que se pase por parámetro, si lo agregáramos. 

## ¿Cómo es el formato de las pruebas?

Tal como pueden pueden ver en las pruebas del TP0 y Administración de Memoria, las pruebas suelen tener un formato particular, y es el mismo que les presentamos en la _prueba esqueleto_ que les damos en `pila_test.go`:

1. El paquete de prueba siempre debe ser `mitda_test`, en este caso `pila_test`.
2. Una función de prueba debe siempre empezar con la palabra `Test` (y cualquier otra cosa que venga debe comenzar en mayúsculas). Pueden tener otro tipo de funciones, pero no se van a interpretar como tests. 
3. La función debe recibir `*testing.T`. Que el parámetro se llame `t` no es estrictamente necesario, como siempre. Es simplemente por convención. Pueden ver las diferentes formas de testear usando el módulo `require` tal como se hace en el tp0 y los demás. La documentación completa del módulo `require` la pueden encontrar [aquí](https://pkg.go.dev/github.com/stretchr/testify/require).

Es importante que los 3 pasos anteriores se cumplan para que Go interprete a los tests justamente como tests.

## ¿Cómo debo probar mi programa / librería de funciones / TDA?

Siempre que se codifica algo, hay que comprobar que funcione correctamente. Pero esto no puede ser solo ejecutarlo un par de veces y comprobar 'a mano' que funcione todo, porque no se puede confiar en esos resultados. ¿Y si me olvido de probar un caso? ¿Y si cambio una primitiva y nunca confirmo que siga funcionando?

Es por esto que siempre se que codifica algo, hay que codificar en paralelo un set de pruebas. Pruebas tales que **si modifico la _implementación_ del programa, puedo correr las pruebas y verificar que de todas formas no cambiaron los resultados**. Siempre hay que tener en mente la reutilización de las pruebas. Si se rompió algo, las pruebas deben decirme lo más detalladamente posible qué rompió y dónde.

Las pruebas que hacemos en el curso son **unitarias**, es decir, prueban solo una cosa a la vez. Algunas propiedades que debe cumplir cada prueba:

* **Unitarias**: Cada prueba verifica el funcionamiento de una sola cosa y tiene una sola responsabilidad. Tienen que tener un objetivo bien claro. Esto debe reflejarse en el nombre de la prueba. Cada prueba debe ser facil, corta y rápida. Una prueba donde haya que leer más de 20 lineas de código no es una prueba facil de entender ni rápida de depurar.

* **Explicitas**: Las pruebas deben poder ser leidas en ejecución y confirmado que se pasen. Para esto, los mensajes deben ser lo más descriptivos posibles, para que cuando algo rompa, se tenga en claro donde fue. "Prueba 1 OK" no es descriptivo. "Insertar dos elementos iguales en una cola vacía OK" si lo es.

* **Aisladas y sin orden**: Cada prueba debe poder ser corrida sin depender del resto. No deberían ser corridas en orden para un correcto funcionamiento. No hay que nombrar a las pruebas según su orden, porque no lo tienen.

* **Deterministicas**: Mientras no se cambie el código, una prueba debe siempre devolver el mismo resultado, sea que paso (OK) o que no (ERROR). El resultado debe ser el mismo todas las veces. Si no, ¿qué esta probando?

* **Prueban resultados**: Las pruebas no deben dependender de la implementación del programa. Como si fuesen una caja negra que no sabe nada de adentro, solamente deben probar que dado unos parametros, se devuelva un resultado. Nunca debo tener que cambiar una prueba para que la nueva implementación la pase. Las pruebas son fijas, el programa no.

Estas pruebas deben cubrir tanto el funcionamiento básico de un programa que haría el usuario tipo (hay que probar todo el programa, codificar una función sin pruebas subsecuentes es equivalente a no haberla codificado en una primera instancia) como los casos borde y los casos triviales. El fin es siempre tener el programa lo más robusto posible. Un buen set de pruebas inicial siempre ahorra errores en el futuro.
