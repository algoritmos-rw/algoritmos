---
layout: page
title: FAQ - Lenguaje C Compilación y Ejecución
permalink: /faq/compilacion-ejecucion
math: true
---

FAQ - Lenguaje C Compilación y Ejecución
=========
{:.no_toc}

* Contenido
{:toc}

## ¿Cómo hago para tener una función que usa otra, pero está más adelante en el código?

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

## ¿Por qué mis `printf` no se imprimen?  

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

## ¿Qué significa assignment makes pointer from integer without a cast?

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

## ¿Qué es un archivo Makefile?

Un archivo Makefile es un archivo creado para automatizar el proceso de compilación, ejecución y mantenimiento del código fuente. Al ejecutar el programa `make` se buscan estos archivos para ejecutar sus instrucciones y compilar el código fuente cuando sea necesario.

Para más información se puede consultar este [apunte de la cátedra](https://drive.google.com/open?id=1iMUDd8tPJ-uZrZWRlw7uTmfcM1CEAJva) y el [Makefile de ejemplo](https://drive.google.com/open?id=15QDg5EmjCXVE_jrthNm-78TkG9fvG9K8).


## ¿Cómo se le pasan parámetros por línea de comandos a un programa?

Al ejecutar un programa se pueden pasar parámetros por línea de comandos:

	$ ./tp productos.csv registros.csv

El programa los puede recibir como cadenas cuando se declara la función main con la siguiente firma:

``` cpp
int main(int argc, char* argv[])
```

En dónde el primer argumento es la cantidad de parámetros, y el segundo es un arreglo con cada uno de ellos. En todos los casos `argc` siempre es mayor que 1 porque `argv[0]` contiene el nombre con el que se invocó al programa.

Pueden leer más sobre parámetros de la línea de comandandos en el [apunte del curso](https://drive.google.com/open?id=18tXTY-zwSTGlbeFHhyxQ9MAG1XJlZwyu).


## ¿Qué significa implicit declaration of function 'una_funcion_interna'?

Las funciones que están definidas en un archivo `.c` pero que no están declaradas en el correspondiente archivo `.h` no pueden ser llamadas fuera de ese archivo `.c`.

Sólo se puede llamar a funciones que están declaradas en el `.h`, una función interna del archivo `.c` no debe ser llamada desde fuera de este archivo.

No se puede probar esas funciones directamente mediante las pruebas, sino que es necesario probarlas indirectamente, mediante llamadas a las funciones que sí están declaradas en el `.h`.


