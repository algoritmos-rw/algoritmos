Algoritmos y Programación II - Preguntas frecuentes
===================================================

## Preguntas generales

### ¿Cómo funciona una lista de correos?

Las listas de correo o listas de discusión son grupos formado por usuarios que están interesados en un tema en común. De esta manera se crean foros en dónde los mensajes se leen y escriben mediante correo electrónico.  Estos foros pueden estar gestionados por administradores o moderadores que controlan el tráfico y deciden quiénes pueden formar parte de las discusiones.

Los mensajes en este foro están organizados de acuerdo a temas (también llamados hilos o threads). Se inicia un nuevo tema enviando un nuevo correo y sus respuestas se agruparan en ese mismo tema, creando así una discusión sobre un asunto.

La lista de correos es el medio de comunicación principal de este curso. Está activa usando el servicio de Grupos de Google, por lo tanto para participar es necesaria una cuenta email vinculada con Google.
Para más información se puede ver la ayuda de Google sobre el tema.

### ¿Cómo hago para instalar el entorno de desarrollo en mi PC?

Hay varias opciones, según tu sistema operativo y tus preferencias. Contamos con una página dedicada al entorno de desarrollo donde explicamos cómo instalar Ubuntu dentro de una máquina virtual, y luego cómo instalar el editor y compilador dentro de Ubuntu.


## Lenguaje C

### ¿Cómo hago para tener una función que usa otra, pero está más adelante en el código?

Se puede incluir el prototipo de la función para 'avisarle' al compilador que se va a encontrar con la definición de la función más adelante:

    void f(int x);

    int main(){
        f(3);
        return 0;
    }

    void f(int x){
        ...
    }

De esta forma, el compilador puede hacer el chequeo de tipos sin conocer el cuerpo de la función.

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

Si al compilar varios archivos que se incluyen entre ellos se obtiene el error multiple definition of `nombre de la función` o bien redefinition of typedef tipo_de_datos, aún cuando las funciones y los tipos se están definiendo una única vez, es muy probable que se deba a que no se están protegiendo los encabezados de forma correcta.  Para ello, es necesario utilizar el siguiente formato en todos los archivos .h del programa:

    #ifndef NOMBRE_DEL_ARCHIVO_H
    #define NOMBRE_DEL_ARCHIVO_H

    // Contenido del .h

    #endif

Donde NOMBRE_DEL_ARCHIVO_H se debe reemplazar por el nombre del archivo.h correspondiente.

### ¿Qué significa assignment makes pointer from integer without a cast?

La siguiente operación es incorrecta:

    int* valor = 4;

Ya que está asignando un valor entero a algo que es un puntero, y claramente es una dirección de memoria inválida.

Si lo que se quiere es tener un puntero a un entero, y que el valor del entero sea 4, existen estas dos alternativas:

    int i = 4;
    int* x = &i;

Esto funciona, pero hay que tener mucho cuidado, ya que la variable i se encuentra en el stack, por lo que la dirección de i sólo tiene sentido mientras la función actual no se termine.  Al terminar la función actual pasa a ser una dirección de memoria inválida.  Por otro lado:

    int* x = malloc(sizeof(int));
    if (!x) return false;
    *x = 4;

En este caso, la dirección de memoria de x es válida aún cuando termine la función actual.  Pero hay que tener cuidado de liberar ese espacio de memoria cuando ya no sea necesario.

## Valgrind

### ¿Cómo hago para que valgrind me indique la línea en la que hay un error?

Es necesario agregar la opción -g (debug) a la línea de compilación. Eso le dice al compilador que incluya la información de debugging en el binario, que despues el valgrind usa para saber en qué línea están las instrucciones.

Además, la opción --track-origins=yes sirve para llevar un registro del uso de valores sin inicializar que pueden llegar a estar trayendo problemas.

### ¿Qué significa Conditional jump or move depends on uninitialised value?

Significa que una variable utilizada en un if no está inicializada. Puede ser que se trate de una variable local que no se asignó a nada, o de una variable que otra función debía guardar, y por algún motivo no la guardó.

### ¿Qué significa Invalid read of size X / Invalid write of size X?

Este tipo de mensajes suele aparecer cuando se trata de leer o escribir más posiciones de las que fueron reservadar originalmente. Por ejemplo si se hizo:

    void** datos = malloc(10*sizeof(void*))

Despues se podrá leer y escribir hasta datos[9], al acceder a datos[10] o mayor, dará este error.

### Al ejecutar un programa dentro de valgrind sucede algo distinto que sin valgrind, ¿Cómo puede ser?

Puede pasar que dentro de valgrind falle y fuera de valgrind no, o al revés.  Ambas situaciones son medianamente normales.

Esto se debe a que para poder verificar que no haya pérdidas de memoria, valgrind maneja la memoria diferente que como se maneja normalmente.  Es por eso que es algo más o menos común que cuando se ejecuta un programa con problemas dentro de valgrind no se comporte exactamente igual que fuera de valgrind.

Solucionando los problemas de memoria que tenga el programa se debería obtener el mismo comportamiento tanto dentro como fuera de valgrind.

## Cadenas

### ¿Cómo comparo si dos cadenas son iguales?
En C las cadenas de caracteres son vectores que tienen caracteres como elementos.  C no sabe comparar vectores, de ningún tipo.  Al hacer una comparación del tipo: cadena1 == cadena2, lo que se compara es que las direcciones de memoria de ambas variables sean iguales, es decir que sólo van a ser iguales cuando realmente sean el mismo puntero.

Para poder comparar el contenido de dos cadenas, es necesario usar la función strcmp(cadena1, cadena2), que devuelve 0 si son iguales, menor que 0 si la primera es menor y mayor que 0 si la primera es mayor.  En este caso no importa que las cadenas ocupen o no la misma porción de memoria.

## Abstracción

### ¿Qué significa el error dereferencing pointer to incomplete type?

Este error se da cuando se trata de acceder a un miembro de una estructura de la cual no se tiene información.  Si en el archivo .h aparece únicamente:

    typedef struct _mitipo mitipo;

No va a ser posible acceder a los miembros internos de esa estructura, ya que es un tipo incompleto.  Sobre las razones de por qué esto está bien en el caso de un TAD, ver la siguiente pregunta.

### ¿Por qué no puedo acceder a un miembro de una estructura de un TAD?

Los miembros de las estructuras (como pila->cantidad, por ejemplo) son datos internos de la implementación de cada tipo abstracto de datos, a los que no se debe acceder fuera del archivo .c en el que se encuentran las primitivas correspondientes al TAD.

Este es el principio básico de abstracción, que nos permite operar con una pila, una lista o un árbol sin tener en cuenta cómo están implementados, y que si la implementación cambia, el código que utiliza el TAD sigue funcionando sin necesidad de ser modificado.

Cuando se realizan pruebas sobre un TAD para verificar su comportamiento, no es necesario acceder a los miembros de la estructura, ya que lo que se desea verificar es que se comporte de la forma esperada y no cuáles son los valores utilizados internamente por la implementación.  Las pruebas deben funcionar aún si la implementación interna cambia (siempre que se respeten las primitivas).

### ¿Qué significa implicit declaration of function 'una_funcion_interna'?

Las funciones que están definidas en un archivo .c pero que no están declaradas en el correspondiente archivo .h no pueden ser llamadas fuera de ese archivo .c.

Sólo se puede llamar a funciones que están declaradas en el .h, una función interna del archivo .c no debe ser llamada desde fuera de este archivo.

No se puede probar esas funciones directamente mediante las pruebas, sino que es necesario probarlas indirectamente, mediante llamadas a las funciones que sí están declaradas en el .h.

## Redimensionamiento automático

Estas respuestas son útiles tanto para la pila dinámica, como para la tabla de hash, o cualquier otra estructura que deba agrandarse y achicarse automáticamente.

### ¿Cuánto conviene agrandar una estructura dinámica?

Hacer un realloc es una operación lenta: O(n) (siendo n la cantidad de bytes que se mantienen en el bloque de memoria).  De modo que es importante planificar cuánto se va a agrandar la estructura, para que el tiempo gastado en el redimensionamiento no influya en el comportamiento general de la estructura.

Para ello, lo que se hace es que al agrandar, el espacio utilizado se multiplique -generalmente por 2, pero puede ser por otro factor, según las condiciones del problema a resolver-, de modo que la incidencia del realloc se distribuya siempre de forma pareja entre los elementos, lo que no sucede en el caso de que la estructura crezca una cantidad constante.

### ¿Cuándo y cuánto conviene achicar una estructura dinámica?

Si para agrandar la estructura multiplicamos su tamaño por 2, no es una buena idea reducirla a la mitad ni bien llega a la mitad de espacio utilizado, ya que en el caso de que se quisiera agregar un nuevo elemento, sería necesario agrandarla y si se lo quita, otra vez achicarla, por lo que en definitiva, habría una cantidad de elementos para la que las operaciones de agregar o sacar de la estructura serían particularmente lentas.

Es por eso que lo que se puede hacer es reducir la estructura a la mitad, pero sólo cuando la cantidad de espacio ocupada llega a 1/4 de la deseada.  De este modo, se libera la memoria fuera de uso, pero sin el riesgo de caer en un caso patológicamente lento.

Tanto en el caso de agrandar como el de achicar, se pueden tomar criterios distintos para buscar mayor eficiencia en tiempo o en memoria, según el problema a resolver.

## Iteradores

### ¿Qué es un iterador?

Es una construcción que nos permite recorrer los elementos almacenados dentro de una estructura en cierto orden. Por ejemplo, en un vector:

    double v[100];
    for (int i=0; i<100; i++) {
           // Hacer algo con v[i]
    }

La variable i hace de iterador del vector v.

En listas enlazadas, árboles, tablas de hash y otras estructuras ese int i no es suficiente para recorrer la estructura, por lo que se generaliza esa idea en el concepto de "iterador".

Las operaciones básicas que puede tener un iterador son:
crear
ver_dato
avanzar
¿esta_al_final?
destruir
Y la forma tradicional de usarlo sería (ejemplo para un iterador de lista):

lista_dato_t dato;
lista_iter_t* it = lista_iter_crear(lista);
while ( ! lista_iter_es_final(it) ) {
       lista_iter_ver_actual(it, &dato); /* carga el dato */
       // ... Hacer algo con dato ...
       lista_iter_avanzar(it); /* avanza al siguiente */
}
lista_iter_destruir(it);

### Una vez que se llega al fin, ¿El iterador no sirve más?

En efecto, los iteradores son descartables, una vez que se termina de recorrer la estructura, sea porque está vacía o se llegó al final, el iterador termina su vida útil, hay que destruirlo y crear uno nuevo.

## Destrucción de datos

### Si tengo una estructura que guarda datos de distintos tipos, ¿Cómo hago para destruirlos?

Cuando una estructura, por ejemplo una lista, se utiliza en un mismo programa para guardar distintos datos, se los almacena como void* y es necesario castearlos cuando se los quiere acceder.  En particular es interesante el caso de la función de destrucción, que está definida como void destruir_dato(lista_dato_t)

Supongamos que se tiene una lista que contiene mensaje_t* y otra que contiene char*.  Las funciones de destrucción  correspondientes deberán recibir lista_dato_t en ambos casos, y por dentro hacer los casteos:

    void destruir_dato_char(lista_dato_t dato) {
       char* dato_c = (char*) dato;
       free(dato_c);
    }

    void destruir_dato_mensaje(lista_dato_t dato) {
       mensaje_t* dato_m = (mensaje_t*) dato;
       mensaje_destruir(dato_m);
    }

O sea, para cada tipo de dato, se lo castea a lo que corresponda y luego se opera para liberarlo según corresponda.

### Si una lista guarda listas, ¿Cómo se hace para destruirla?

Como para cualquier otro tipo de listas, para destruir una lista de listas, el usuario que está usando la estructura deberá definir una función para la destrucción de las listas contenidas dentro de la otra lista.  Suponiendo que las listas de adentro contienen mensajes, podría ser de la siguiente forma:

    void destruir_dato_lista(lista_dato_t dato) {
        lista_t* lista = (lista_t*) dato;
        lista_destruir(lista, destruir_dato_mensaje);
    }

### ¿Qué se debe hacer cuando el tipo de datos no necesita ser destruido?

Si dentro del código de la estructura de datos se verifica que la función se haya recibido:

    if (destruir_dato) destruir_dato(dato);

Se puede llamar a la función de destrucción simplemente pasando NULL como parámetro:

    lista_destruir(lista, NULL)

### ¿Por qué no reciben la función de destrucción las funciones que eliminan de a uno?

En varias estructuras, como listas, colas, pilas o árboles, a la función de destruir se le pasa una función para destruir el dato, mientras que a la función de borrar (desapilar, desencolar, etc) no se le pasa esta función.

Esto se debe a que las funciones que eliminan elementos de las estructuras no los tienen que destruir, ya que los guardan en la referencia al dato recibida por puntero, y es el usuario el encargado de liberar el dato de ser necesario.

## Hash

### ¿Qué son las claves y los datos dentro del hash?

La clave es la cadena mediante la cual se ubica el dato, tanto al guardarlo como al buscarlo o sacarlo.  Por ejemplo, si se guarda una estructura alumno, la clave podría ser el padrón o el apellido, según con qué criterio se quiere guardar y luego encontrar los datos.

A esta clave será necesario aplicar la función de hashing, que debería dar un número más o menos grande, al que luego se lo acota aplicando el resto de la división entera con el largo del arreglo del hash.

Por otro lado, el hash_dato_t es la información que va ir asociada a esa clave, y puede ser cualquier puntero.  En la tabla de hash esta información tiene que quedar guardada como una pareja, ya que la clave y el dato tienen que estar juntos, en una estructura adicional (que se puede llamar, por ejemplo, hash_nodo_t o hash_elem_t).  De esta forma es posible recuperar el dato asociado a la clave cuando así se lo solicite.

### ¿Cómo se itera un hash abierto?

El objetivo del iterador es permitir recorrer todos los elementos de la tabla de hash, sin importar el orden en que se encuentren. Cada vez que se pide ver el elemento actual, se deben devolver tanto la clave como el dato, ya que el usuario no sabe cuál es ninguno de los dos.

Al crear el iterador, tiene que quedar apuntando al "primer" elemento que hay en el hash.  Para ello, tiene que verificar cuál es el primer balde que contiene una lista no-vacía, y de esa lista crear un iterador.

Al avanzar el iterador de hash, debe avanzar el iterador de la lista actual, y en el caso de que llegue al final, buscar la siguiente lista no vacía.

Debe indicar que llegó al final cuando ya no queden listas por recorrer.

### ¿Cómo se destruye un hash abierto?
La lista que está asociada a cada uno de los baldes de la tabla de hash debe contener parejas de clave-valor.  De modo que si al momento de destruir la lista se le pasara una función de destrucción del dato, esta función debería destruir estas parejas.  Pero el usuario almacena en el hash una función de destrucción del valor almacenado, a la que no se puede acceder desde la función de destrucción del dato de la lista.

La forma más sencilla de resolver este problema es, entonces, ir llamando a la función lista_borrar_primero hasta que la lista se encuentre vacía y destruir apropiadamente cada uno de los elementos que se van sacando de la lista.
