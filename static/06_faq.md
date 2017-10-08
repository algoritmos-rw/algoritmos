---
layout: page
title: FAQ
permalink: /faq/
---

Preguntas frecuentes
=========
{:.no_toc}

* Contenido
{:toc}

## Preguntas generales

### ¿Cómo funciona una lista de correos?

Las listas de correo o listas de discusión son grupos formado por usuarios que están interesados en un tema en común. De esta manera se crean foros en dónde los mensajes se leen y escriben mediante correo electrónico.  Estos foros pueden estar gestionados por administradores o moderadores que controlan el tráfico y deciden quiénes pueden formar parte de las discusiones.

Los mensajes en este foro están organizados de acuerdo a temas (también llamados hilos o threads). Se inicia un nuevo tema enviando un nuevo correo y sus respuestas se agruparan en ese mismo tema, creando así una discusión sobre un asunto.

La [lista de correos](https://groups.google.com/forum/#!forum/fiuba-7541rw-alu) es el medio de comunicación principal de este curso. Está activa usando el servicio de Grupos de Google, por lo tanto para participar es necesaria una cuenta email vinculada con Google.

Para más información se puede ver la [ayuda de Google](https://support.google.com/groups/?hl=es#topic=9216) sobre el tema.

### ¿Cómo hago para instalar el entorno de desarrollo en mi PC?

Hay varias opciones, según tu sistema operativo y tus preferencias. Contamos con una página dedicada al [entorno de desarrollo](entorno) donde explicamos cómo instalar Ubuntu dentro de una máquina virtual, y luego cómo instalar el editor y compilador dentro de Ubuntu.


## Lenguaje C y compilación

### ¿Para qué se usa el tipo size_t?

`size_t` es un tipo entero sin signo devuelto por el operador `sizeof` y es usado para representar el tamaño de construcciones en bytes. Este tipo está definido de manera tal de garantizar que siempre va a poder almacenar el tamaño del tipo más grande posible, por lo que también garantiza que va a poder almacenar cualquier índice de cualquier arreglo.

Estas características lo convierten en el tipo adecuado para manejar tamaños e índices.

### ¿Cómo hago para tener una función que usa otra, pero está más adelante en el código?

Se puede incluir el prototipo de la función para 'avisarle' al compilador que se va a encontrar con la definición de la función más adelante:

``` c
void f(int x);

int main(){
    f(3);
    return 0;
}

void f(int x){
    ...
}
```

De esta forma, el compilador puede hacer el chequeo de tipos sin conocer el cuerpo de la función.

### ¿Por qué mis `printf` no se imprimen?  

La convención en Unix es que la entrada estándar y la salida estándar tengan un búfer asociado. Esto significa que al utilizar `printf` de la manera normal, no se imprime inmediatamente a la consola: sólo sucede cuando suficientes mensajes están esperando ser impresos. Por esto, si el programa se termina por algún error entre que llamamos a `printf` y que el búfer se vacía, nuestro mensaje no se muestra.   
La solución es utilizar un canal específico para los errores, que no tiene un búfer asociado: `stderr`. Se puede utilizar como cualquier archivo llamando a `fprintf`:  

```c
fprintf(stderr, ...);
```   

## ¿Cómo hago para que gcc escupa los mensajes de error en inglés?

Cuando gcc (o cualquier otro programa) imprime un mensaje de error en castellano e intentamos buscarlo en internet porque no lo entendemos, es probable que encontremos poca información. Lamentablemente hay muchísima más información en inglés que en castellano.

Por lo tanto, es una buena idea obligar a un programa a imprimir los mensajes en el idioma original antes de buscar en internet:

    $ LANG=C programa

Por ejemplo:

    $ gcc noexiste.c
    gcc: error: noexiste.c: No existe el fichero ó directorio
    gcc: error fatal: no hay ficheros de entrada
    $ LANG=C gcc noexiste.c
    gcc: error: noexiste.c: No such file or directory
    gcc: fatal error: no input files

## ¿Qué significa el error "assignment discards qualifiers from pointer target type"?

Significa que con la asignación se está descartando un calificador de un puntero. Particularmente se suele dar cuando el dato recibido es un const y se lo asigna a una variable (o miembro de una estructura) que no es const, por lo que se le estaría dando luz verde para que se cambie, ya que a través de un puntero se puede cambiar el dato.

## Problemas de redefinición de funciones y/o tipos al compilar varios archivos

Si al compilar varios archivos que se incluyen entre ellos se obtiene el error `multiple definition of nombre de la función` o bien `redefinition of typedef tipo_de_datos`, aún cuando las funciones y los tipos se están definiendo una única vez, es muy probable que se deba a que no se están protegiendo los encabezados de forma correcta.  Para ello, es necesario utilizar el siguiente formato en todos los archivos .h del programa:

``` cpp
#ifndef NOMBRE_DEL_ARCHIVO_H
#define NOMBRE_DEL_ARCHIVO_H

// Contenido del .h

#endif
```

Donde `NOMBRE_DEL_ARCHIVO_H` se debe reemplazar por el nombre del archivo.h correspondiente.

### ¿Qué significa assignment makes pointer from integer without a cast?

La siguiente operación es incorrecta:

``` cpp
int* valor = 4;
```

Ya que está asignando un valor entero a algo que es un puntero, y claramente es una dirección de memoria inválida.

Si lo que se quiere es tener un puntero a un entero, y que el valor del entero sea 4, existen estas dos alternativas:

``` cpp
int i = 4;
int* x = &i;
```

Esto funciona, pero hay que tener mucho cuidado, ya que la variable i se encuentra en el stack, por lo que la dirección de i sólo tiene sentido mientras la función actual no se termine.  Al terminar la función actual pasa a ser una dirección de memoria inválida.  Por otro lado:

``` cpp
int* x = malloc(sizeof(int));
if (!x) return false;
*x = 4;
```

En este caso, la dirección de memoria de `x` es válida aún cuando termine la función actual.  Pero hay que tener cuidado de liberar ese espacio de memoria cuando ya no sea necesario.

### ¿Qué es un archivo Makefile?

Un archivo Makefile es un archivo creado para automatizar el proceso de compilación, ejecución y mantenimiento del código fuente. Al ejecutar el programa `make` se buscan estos archivos para ejecutar sus instrucciones y compilar el código fuente cuando sea necesario.

Para más información se puede consultar este [apunte de la cátedra](https://sites.google.com/site/fiuba7541rw/apuntes/Makefile.pdf?attredirects=0) y el [Makefile de ejemplo](https://sites.google.com/site/fiuba7541rw/ejemplos-de-codigo/Makefile?attredirects=0).

## Valgrind

### ¿Cómo hago para que Valgrind me indique la línea en la que hay un error?

Es necesario agregar la opción `-g` (debug) a la línea de compilación. Eso le dice al compilador que incluya la información de debugging en el binario, que despues Valgrind usa para saber en qué línea están las instrucciones.

Además, la opción `--track-origins=yes` sirve para llevar un registro del uso de valores sin inicializar que pueden llegar a estar trayendo problemas.

### ¿Qué significa Conditional jump or move depends on uninitialised value?

Significa que una variable utilizada en un `if` no está inicializada. Puede ser que se trate de una variable local que no se asignó a nada, o de una variable que otra función debía guardar, y por algún motivo no la guardó.

### ¿Qué significa Invalid read of size X / Invalid write of size X?

Este tipo de mensajes suele aparecer cuando se trata de leer o escribir más posiciones de las que fueron reservadar originalmente. Por ejemplo si se hizo:

``` cpp
void** datos = malloc(10*sizeof(void*))
```

Despues se podrá leer y escribir hasta `datos[9]`, al acceder a `datos[10]` o mayor, dará este error.

### Al ejecutar un programa dentro de Valgrind sucede algo distinto que sin él, ¿cómo puede ser?

Puede pasar que dentro de Valgrind falle y fuera de este no, o al revés.  Ambas situaciones son medianamente normales.

Esto se debe a que para poder verificar que no haya pérdidas de memoria, Valgrind maneja la memoria diferente que como se maneja normalmente.  Es por eso que es algo más o menos común que cuando se ejecuta un programa con problemas dentro de Valgrind no se comporte exactamente igual que fuera de Valgrind.

Solucionando los problemas de memoria que tenga el programa se debería obtener el mismo comportamiento tanto dentro como fuera de Valgrind.

## Cadenas

### ¿Cómo comparo si dos cadenas son iguales?
En C las cadenas de caracteres son vectores que tienen caracteres como elementos.  C no sabe comparar vectores, de ningún tipo.  Al hacer una comparación del tipo: `cadena1 == cadena2`, lo que se compara es que las direcciones de memoria de ambas variables sean iguales, es decir que sólo van a ser iguales cuando realmente sean el mismo puntero.

Para poder comparar el contenido de dos cadenas, es necesario usar la función `strcmp(cadena1, cadena2)`, que devuelve 0 si son iguales, menor que 0 si la primera es menor y mayor que 0 si la primera es mayor.  En este caso no importa que las cadenas ocupen o no la misma porción de memoria.

### ¿Cómo copio dos cadenas?

La sentencia:

``` cpp
char* cad_1 = cad_2;
```

No crea una copia de una cadena, sino una copia de la referencia a la cadena. Para hacer una copia de una cadena es necesario hacer:

``` cpp
strcpy(buf_destino, cad_origen);
```

Siendo `buf_destino` una posición de memoria tal que pueda albergar la cadena a copiar, típicamente reservada con `malloc` y `strlen` (teniendo en cuenta el espacio necesario para alojar el fin de cadena).

Desde el curso se recomienda la creación de una función auxiliar `strdup` que encapsule esta lógica.

Pueden leer más sobre sobre cadenas en el [apunte del curso](https://sites.google.com/site/fiuba7541rw/apuntes/Vectores_y_Punteros.pdf?attredirects=0).

### ¿Cómo se le pasan parámetros por línea de comandos a un programa?

Al ejecutar un programa se pueden pasar parámetros por línea de comandos:

	$ ./tp productos.csv registros.csv

El programa los puede recibir como cadenas cuando se declara la función main con la siguiente firma:

``` cpp
int main(int argc, char* argv[])
```

En dónde el primer argumento es la cantidad de parámetros, y el segundo es un arreglo con cada uno de ellos. En todos los casos `argc` siempre es mayor que 1 porque `argv[0]` contiene el nombre con el que se invocó al programa.

Pueden leer más sobre parámetros de la línea de comandandos en el [apunte del curso](https://sites.google.com/site/fiuba7541rw/apuntes/Parametros.pdf?attredirects=0).

## Abstracción

### ¿Qué es el tipo void*?

El tipo `void*` es un tipo que representa un puntero a un tipo no especificado. Es usado cuando el tipo apuntado no es de importancia para la función que la recibe.

Este tipo de punteros puede ser convertido a cualquier otro puntero sin necesidad de un casteo explícito, pero debido a que no se sabe a qué apunta no puede ni desreferenciarse ni ser usado para calcular aritmética de punteros.

### ¿Qué significa el error dereferencing pointer to incomplete type?

Este error se da cuando se trata de acceder a un miembro de una estructura de la cual no se tiene información.  Si en el archivo .h aparece únicamente:

``` cpp
typedef struct _mitipo mitipo;
```

No va a ser posible acceder a los miembros internos de esa estructura, ya que es un tipo incompleto.  Sobre las razones de por qué esto está bien en el caso de un TAD, ver la siguiente pregunta.

### ¿Por qué no puedo acceder a un miembro de una estructura de un TAD?

Los miembros de las estructuras (como `pila->cantidad`, por ejemplo) son datos internos de la implementación de cada tipo abstracto de datos, a los que no se debe acceder fuera del archivo `.c` en el que se encuentran las primitivas correspondientes al TAD.

Este es el principio básico de abstracción, que nos permite operar con una pila, una lista o un árbol sin tener en cuenta cómo están implementados, y que si la implementación cambia, el código que utiliza el TAD sigue funcionando sin necesidad de ser modificado.

Cuando se realizan pruebas sobre un TAD para verificar su comportamiento, no es necesario acceder a los miembros de la estructura, ya que lo que se desea verificar es que se comporte de la forma esperada y no cuáles son los valores utilizados internamente por la implementación.  Las pruebas deben funcionar aún si la implementación interna cambia (siempre que se respeten las primitivas).

### ¿Qué significa implicit declaration of function 'una_funcion_interna'?

Las funciones que están definidas en un archivo `.c` pero que no están declaradas en el correspondiente archivo `.h` no pueden ser llamadas fuera de ese archivo `.c`.

Sólo se puede llamar a funciones que están declaradas en el `.h`, una función interna del archivo `.c` no debe ser llamada desde fuera de este archivo.

No se puede probar esas funciones directamente mediante las pruebas, sino que es necesario probarlas indirectamente, mediante llamadas a las funciones que sí están declaradas en el `.h`.

### ¿Qué es un puntero a función?

Los punteros a funcion son variables que apuntan a funciones para que puedan ser invocadas sin conocer su nombre. En C, la sintaxis para declararlas es diferente al resto de los tipos. Por ejemplo, la sintaxis para declarar un puntero a función que recibe dos cadenas y devuelve un entero es la siguiente:

``` cpp
int (*func)(char*, char*);
```

Estas funciones se usan típicamente para delegar la ejecución de un fragmento de código a otra función. Por ejemplo, para aplicarle una operación a todos los elementos de un arreglo de enteros podríamos tener la función:

``` cpp
/* Aplica la operación pasada por parámetro a todos los elementos del arreglo. */
void aplicar(int arreglo[], size_t cant, void (*operacion)(int));
```

Entonces si tuviéramos una función para multiplicar por dos:

``` cpp
void multiplicar_por_dos(int numero)
{
    return numero * 2;
}
```

Podríamos multiplicar por dos a todos los elementos del arreglo usando un puntero a la función:

``` cpp
int arreglo[3] = { 2, 5, 4 };
aplicar(arreglo, 3, multiplicar_por_dos);
```


### ¿Qué es un wrapper?
En la materia usamos los punteros a función para garantizar un comportamiento que no dependa del tipo de datos que se maneje. Por ejemplo, si quisiéramos destruir todos los elementos de una estructura podríamos crear una funcion:

``` cpp
void estructura_destruir(estructura_t* estructura, void (*f_dest)(void*));
```

Que le aplique la función de destrucción a todos los elementos que están almacenados en ella. Si estos elementos también son genéricos y tienen su propia función de destrucción:

``` cpp
void elemento_destruir(elemento_t* elem);
```

No se puede invocar directamente a la primitiva `estructura_destruir` con `elemento_destruir`, porque sus firmas son diferentes. Lo que se suele hacer es crear una función wrapper que enmascare el comportamiento:

``` cpp
void elemento_destruir_wrapper(void* elem)
{
    elemento_destruir((elemento_t*) elem));
}
```

De esta manera, la función `elemento_destruir_wrapper` es genérica y puede ser usada con la función `estructura_destruir`.

## Redimensionamiento automático

Estas respuestas son útiles tanto para la pila dinámica, como para la tabla de hash, o cualquier otra estructura que deba agrandarse y achicarse automáticamente.

### ¿Cuánto conviene agrandar una estructura dinámica?

Hacer un realloc es una operación lenta: _O(n)_ (siendo n la cantidad de bytes que se mantienen en el bloque de memoria).  De modo que es importante planificar cuánto se va a agrandar la estructura, para que el tiempo gastado en el redimensionamiento no influya en el comportamiento general de la estructura.

Para ello, lo que se hace es que al agrandar, el espacio utilizado se multiplique -generalmente por 2, pero puede ser por otro factor, según las condiciones del problema a resolver-, de modo que la incidencia del realloc se distribuya siempre de forma pareja entre los elementos, lo que no sucede en el caso de que la estructura crezca una cantidad constante.

### ¿Cuándo y cuánto conviene achicar una estructura dinámica?

Si para agrandar la estructura multiplicamos su tamaño por 2, no es una buena idea reducirla a la mitad ni bien llega a la mitad de espacio utilizado, ya que en el caso de que se quisiera agregar un nuevo elemento, sería necesario agrandarla y si se lo quita, otra vez achicarla, por lo que en definitiva, habría una cantidad de elementos para la que las operaciones de agregar o sacar de la estructura serían particularmente lentas.

Es por eso que lo que se puede hacer es reducir la estructura a la mitad, pero sólo cuando la cantidad de espacio ocupada llega a 1/4 de la deseada.  De este modo, se libera la memoria fuera de uso, pero sin el riesgo de caer en un caso patológicamente lento.

Tanto en el caso de agrandar como el de achicar, se pueden tomar criterios distintos para buscar mayor eficiencia en tiempo o en memoria, según el problema a resolver.

## Iteradores

### ¿Qué es un iterador?

Es una construcción que nos permite recorrer los elementos almacenados dentro de una estructura en cierto orden. Por ejemplo, en un arreglo:

``` cpp
double arr[TAM_ARR];
for (size_t i = 0; i < TAM_ARR; i++) {
    // Hacer algo con arr[i]
}
```

La variable `i` hace de iterador del arreglo `v`.

En listas enlazadas, árboles, tablas de hash y otras estructuras ese `size_t i` no es suficiente para recorrer la estructura, por lo que se generaliza esa idea en el concepto de "iterador".

Las operaciones básicas que puede tener un iterador son:
  - crear
  - ver_dato
  - avanzar
  - ¿esta_al_final?
  - destruir

### ¿Cómo se usan los iteradores de una estructura?

En la materia adoptamos la siguiente convención para todos los iteradores:
  - La creacion de un iterador en una estructura es siempre una operación válida:
  - Si la estructura tiene elementos, el iterador apunta al primer elemento.
  - Si la estructura no tiene elementos, el iterador se crea, pero apuntando al final.
  - Avanzar un iterador cuando no está al final siempre es una operación válida.
  - Avanzar un iterador que está al final es una operacion inválida, por lo que devuelve false.
  - Ver actual es siempre una operación válida. Cuando está al final devuelve siempre `NULL`.

Considerando esta convención, la forma canónica de iterar una estructura es la siguiente:

``` cpp
estructura_iter_t* iter = estructura_iter_crear(estructura);

while(!estructura_iter_al_final(iter))
{
    void* dato = estructura_iter_ver_actual(iter);
    /* Usar dato. */

    estructura_iter_avanzar(iter);
}

estructura_iter_destruir(iter);
```

O usando la sintaxis de ciclos definidos de C:

``` cpp
estructura_iter_t* iter;

for(iter = estructura_iter_crear(estructura);
  !estructura_iter_al_final(iter);
  estructura_iter_avanzar(iter))
{
    void* dato = estructura_iter_ver_actual(iter);
    /* Usar dato. */
}

estructura_iter_destruir(iter);
```

Se debe tener en cuenta que si bien `estructura_iter_t* iter` puede ser inicializado en el `for` (como en el ejemplo) o fuera del mismo (al ser declarada la variable), la declaración debe estar siempre fuera del `for` para no perder la referencia y poder de esta forma destruirlo cuando se termina de iterar.

### Una vez que se llega al fin, ¿El iterador no sirve más?

En efecto, los iteradores son descartables, una vez que se termina de recorrer la estructura, sea porque está vacía o se llegó al final, el iterador termina su vida útil, hay que destruirlo y crear uno nuevo.

## Destrucción de datos

### Si tengo una estructura que guarda datos de distintos tipos, ¿Cómo hago para destruirlos?

Cuando una estructura, por ejemplo una lista, se utiliza en un mismo programa para guardar distintos datos, se los almacena como `void*` y es necesario castearlos cuando se los quiere acceder.  En particular es interesante el caso de la función de destrucción, que está definida como `void destruir_dato(void*)`.

Supongamos que se tiene una lista que contiene `mensaje_t*` y otra que contiene `char*`.  Las funciones de destrucción  correspondientes deberán recibir `void*` en ambos casos, y por dentro hacer los casteos:

``` cpp
void destruir_dato_char(void* dato) {
   char* dato_c = dato;
   free(dato_c);
}

void destruir_dato_mensaje(void* dato) {
   mensaje_t* dato_m = dato;
   mensaje_destruir(dato_m);
}
```

O sea, para cada tipo de dato, se lo interpreta para liberarlo según corresponda.

### Si una lista guarda listas, ¿cómo se hace para destruirla?

Como para cualquier otro tipo de listas, para destruir una lista de listas, el usuario que está usando la estructura deberá definir una función para la destrucción de las listas contenidas dentro de la otra lista.  Suponiendo que las listas de adentro contienen mensajes, podría ser de la siguiente forma:

``` cpp
void destruir_dato_lista(lista_dato_t dato) {
    lista_t* lista = (lista_t*) dato;
    lista_destruir(lista, destruir_dato_mensaje);
}
```

### ¿Qué se debe hacer cuando el tipo de datos no necesita ser destruido?

Si dentro del código de la estructura de datos se verifica que la función se haya recibido:

``` cpp
if (destruir_dato) destruir_dato(dato);
```

Se puede llamar a la función de destrucción simplemente pasando `NULL` como parámetro:

``` cpp
lista_destruir(lista, NULL)
```

### ¿Por qué no reciben la función de destrucción las funciones que eliminan de a uno?

En varias estructuras, como listas, colas, pilas o árboles, a la función de destruir se le pasa una función para destruir el dato, mientras que a la función de borrar (desapilar, desencolar, etc) no se le pasa esta función.

Esto se debe a que las funciones que eliminan elementos de las estructuras no los tienen que destruir, ya que los guardan en la referencia al dato recibida por puntero, y es el usuario el encargado de liberar el dato de ser necesario.

## Lista enlazada

### ¿Cómo se comporta el agregado y la eliminación en una lista enlazada con iteradores?

La inserción en una lista enlazada sigue dos reglas:
  - El elemento insertado va a tomar la posicion del elemento al que se apunta.
  - Luego de una insercion, el iterador va a apuntar al nuevo elemento.

Esto no quiere decir que `lista_insertar` sobreescriba datos; sino que si el actual del iterador es el segundo elemento de la lista, realizar una inserción colocaría un nuevo dato entre el elemento uno y el dos:

![Inserciones en una lista](../assets/img/faq/lista_iter_1.png)

Dos implicaciones que surgen son:
  - Si se inserta un elemento con un iterador apuntando al primer elemento de la lista, la operación es idéntica a llamar a `lista_insertar_primero`.
  - Si se inserta un elemento con un iterador apuntando al final, la operación es idéntica a llamar a `lista_insertar_ultimo`.

La eliminación funciona de manera análoga: se elimina el elemento al que está apuntando el iterador y este apunta al elemento siguiente:

![Eliminaciones en una lista](../assets/img/faq/lista_iter_2.png)

Considerando esto resulta:
  - La eliminación de un elemento con un iterador apuntando al primer elemento de la lista es idéntica a `lista_borrar_primero`.
  - La eliminacion de un elemento con un iterador apuntando al último elemento de la lista (esto es: al elemento tal que cuando se avanza el iterador está al final) se comportaría como una primitiva `lista_borrar_ultimo`. Eliminar este elemento haría que el iterador apunte al final de la lista.

### ¿Cómo se comporta el iterador interno?

El iterador interno es una herramienta para poder procesar los elementos de la lista sin necesidad de manejar la memoria del iterador externo.
Para hacer esto es necesario escribir la función visitar en donde se especifique qué es lo que se va a hacer con estos nodos:

``` cpp
bool visitar(void* dato, void* extra);
```

Esta función va a ser llamada inicialmente con el dato que ocupa la primera posición de la lista. Como esta función va a ser llamada de manera automática por la primitiva lista_iterar, además debe recibir un puntero extra que puede ser usado para mantener una memoria entre las las sucesivas llamadas.
Adicionalmente, esta función devuelve un valor booleano. Si en algún momento se devuelve false, la iteración se interrumpiría automáticamente.

## Hash

### ¿Qué son las claves y los datos dentro del hash?

La clave es la cadena mediante la cual se ubica el dato, tanto al guardarlo como al buscarlo o sacarlo.  Por ejemplo, si se guarda una estructura alumno, la clave podría ser el padrón o el apellido, según con qué criterio se quiere guardar y luego encontrar los datos.

A esta clave será necesario aplicar la función de hashing, que debería dar un número más o menos grande, al que luego se lo acota aplicando el resto de la división entera con el largo del arreglo del hash.

Por otro lado, el `hash_dato_t` es la información que va ir asociada a esa clave, y puede ser cualquier puntero.  En la tabla de hash esta información tiene que quedar guardada como una pareja, ya que la clave y el dato tienen que estar juntos, en una estructura adicional (que se puede llamar, por ejemplo, `hash_nodo_t` o `hash_elem_t`).  De esta forma es posible recuperar el dato asociado a la clave cuando así se lo solicite.

### ¿Cómo se itera un hash abierto?

El objetivo del iterador es permitir recorrer todos los elementos de la tabla de hash, sin importar el orden en que se encuentren. Cada vez que se pide ver el elemento actual, se deben devolver tanto la clave como el dato, ya que el usuario no sabe cuál es ninguno de los dos.

Al crear el iterador, tiene que quedar apuntando al "primer" elemento que hay en el hash.  Para ello, tiene que verificar cuál es el primer balde que contiene una lista no-vacía, y de esa lista crear un iterador.

Al avanzar el iterador de hash, debe avanzar el iterador de la lista actual, y en el caso de que llegue al final, buscar la siguiente lista no vacía.

Debe indicar que llegó al final cuando ya no queden listas por recorrer.

### ¿Cómo se destruye un hash abierto?

La lista que está asociada a cada uno de los baldes de la tabla de hash debe contener parejas de clave-valor.  De modo que si al momento de destruir la lista se le pasara una función de destrucción del dato, esta función debería destruir estas parejas.  Pero el usuario almacena en el hash una función de destrucción del valor almacenado, a la que no se puede acceder desde la función de destrucción del dato de la lista.

La forma más sencilla de resolver este problema es, entonces, ir llamando a la función `lista_borrar_primero` hasta que la lista se encuentre vacía y destruir apropiadamente cada uno de los elementos que se van sacando de la lista.


## Árboles binarios de búsqueda

### ¿Cómo se destruye un dato en un ABB?

Recomendamos seguir este algoritmo para destruir datos en un árbol binario de búsqueda: después de localizar el nodo a eliminar se consideran tres casos:
  - Si el nodo es una hoja (es decir: no tiene hijos), se elimina.
  - Si el nodo tiene un solo hijo, se elimina el nodo y se reemplaza con su hijo.
  - Si el nodo tiene dos hijos no se elimina el nodo, sino que se reemplaza con el siguiente inorder (es decir, con el menor de sus hijos mayores) o con el anterior inorder (el mayor de sus hijos menores).

Luego se llama a la eliminación recursiva en el subárbol correspondiente de acuerdo a la estrategia de eliminación elegida. Como se eligió o bien el menor de sus hijos mayores o el mayor de sus hijos menores, obligatoriamente al nodo a borrar le va a faltar un hijo, haciendo que se caiga en alguno de los dos primeros casos.

## Heaps

### ¿Por qué no representamos heaps con nodos enlazados?
Los heaps son árboles completos, por lo que si se representa la estructura con un arreglo se pueden calcular de manera sencilla y elegante las posiciones de los padres e hijos de cada nodo. De esta manera los algoritmos resultan muy fáciles de programar y se evita la creación y el encadenamiento de los nodos en cada operación de alta o baja. Además, se ahorra memoria ya que no es necesario almacenar referencias entre nodos.
