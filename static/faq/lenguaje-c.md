---
layout: page
title: FAQ - Lenguaje C
permalink: /faq/lenguaje-c
---

FAQ - Lenguaje C
=========
{:.no_toc}

* Contenido
{:toc}

## ¿Para qué se usa el tipo size_t?

`size_t` es un tipo entero sin signo devuelto por el operador `sizeof` y es usado para representar el tamaño de construcciones en bytes. Este tipo está definido de manera tal de garantizar que siempre va a poder almacenar el tamaño del tipo más grande posible, por lo que también garantiza que va a poder almacenar cualquier índice de cu## ¿Para qué se usa el tipo size_t?

`size_t` es un tipo entero sin signo devuelto por el operador `sizeof` y es usado para representar el tamaño de construcciones en bytes. Este tipo está definido de manera tal de garantizar que siempre va a poder almacenar el tamaño del tipo más grande posible, por lo que también garantiza que va a poder almacenar cualquier índice de cualquier arreglo.

Estas características lo convierten en el tipo adecuado para manejar tamaños e índices.

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

Pueden leer más sobre sobre cadenas en el [apunte del curso](https://drive.google.com/open?id=1J3uJd0SLZ1DHvPTf7H4ZaKPTwi2mRC0X).

## ¿Qué es un puntero a función?

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

## ¿Qué es un wrapper?
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
