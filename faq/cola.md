# FAQ - Cola
{:.no_toc}

* Contenido
{:toc}

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

## ¿Qué es la primitiva cola_destruir y para que sirve su segundo parametro?

El fin de los TDA es que puedan ser utilizados para almacenar y trabajar con datos genéricos. Sea esto un caracter, un número entero, un número flotante, estructuras definidas por el usuario o demás. Siempre se deben poder manejar estos datos de la misma manera, con las primitivas definidas en el TDA. Ahora, ¿y si estos datos están almacenados en la memoria dinámica?

Recordando las que podrían ser las reglas fundamentales de la memoria dinámica:

1. Para cada `malloc()` tiene que haber un `free()` antes de finalizar el programa.

2. Cuando alguien llama a `malloc()` se convierte en el “dueño simbólico” de esa región de memoria.

3. `free()` lo tiene que llamar el “dueño” de la región de memoria.

4. En determinadas circunstancias, y si las partes se ponen de acuerdo, es posible transferir, simbólicamente, la “propiedad” de una región de memoria.

Hasta ahora (hasta el TDA Pila), nuestro usuario siempre almacenó datos que existían en la memoria estática. A estos datos nunca hubo que liberarlos con `free()` porque nunca hubo un `malloc()` asociado ni eramos nosotros (los creadores del TDA pero no del dato) los responsables de liberarlos. De haber insertado datos de la memoria dinámica, habría sido el usuario el responsable de liberarlo y no la estructura.

En el TDA cola, si bien no somos los dueños de las regiones de memoria donde se encuentran almacenados los datos a encolar, si el usuario nos dice **cómo**, podemos tomar "propiedad transitoria" en `cola_destruir()` y encargarnos de liberar los datos a la vez que destruimos el TDA

Es este "**cómo**" el segundo parametro de cola_destruir, en forma de [puntero a función de destrucción](lenguaje-c.md#funptr). (Leer sí o sí antes de continuar.)

Si el usuario almacenó enteros, caracteres o cualquier cosa que 'viva' en la memoria estática, llamará a `cola_destruir(cola, NULL)` ya que no hay función de destrucción para datos estáticos.

Si el usuario almacenó punteros a memoria dinámica, llamará a `cola_destruir(cola, free)` ya que un `malloc()` se destruye con un `free()`.

Si el usuario creó su propia estructura para almacenar, la función de destrucción deberá ser la asociada a la estructura (de forma que se libere la estructura junto con todo lo que en ella se almacene). Por ejemplo, si el usuario inserta pilas, el llamado será `cola_destruir(cola, pila_destruir)`.
