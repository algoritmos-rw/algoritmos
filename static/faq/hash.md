---
layout: page
title: FAQ - Hash
permalink: /faq/hash
---

FAQ - Hash
=========
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

