---
layout: default
title: Algoritmos de Ordenamiento Externo
permalink: /apuntes/ordenamiento_externo
math: true
---

# Algoritmos de Ordenamientos Externos

Llamamos ordenamiento externo cuando debemos ordenar archivos que son (mucho) más grandes de lo que nuestra memoria puede llegar a abarcar. Esto es así porque, sino, podríamos simplemente cargar el archivo en memoria y ordenarlo usando cualquier algoritmo de ordenamiento convencional. 

Hoy en día es raro necesitar utilizar algoritmos como estos debido a que contamos con mucha más memoria RAM de lo que se hacía una década atrás. 
Este era un tema que hasta hace unos años se daba en la materia _Organización de Datos_, pero dado que poco tenía que ver con el resto del temario, y que tiene más sentido en nuestra materia, decidieron dejar de darlo. 

Supongamos entonces que contamos con un caso así. Estamos queriendo ordenar un archivo completamente desordenado, bajo algún criterio que no es importante. El algoritmo que podríamos utilizar podría hacer algo como:
1. Generar _k_ particiones ordenadas. Cada archivo tendrá $$n_i$$ (_i_ entre 0 y _k-1_) elementos, donde la suma de todos los $$n_i$$ será _n_, la cantidad total de elementos del archivo original. 
2. Juntar las _k_ particiones ordenadas en un nuevo archivo ordenado. Esto sería una generalización del _intercalar ordenado_ de mergesort. 

Veremos cómo podemos implementar cada una de esas partes. Primero veremos la segunda, que es la más sencilla.

## Juntar _k_ archivos ordenados

Esto en sí ya no necesariamente aplica para archivos, podría tranquilamente ser para arreglos (solo que en el caso de archivos, iremos leyendo del archivo en vez de un arreglo). La idea va a ser reutilizar el heap. Así como tenemos la opción de utilizar un heap para obtener los _k_ elementos más grandes de un arreglo de _n_ elementos en _O(n log k)_, también podemos hacer el merge de _k_ archivos (o arreglos) **ordenados** que tienen en total _n_ elementos, en _O(n log k)_.

Así como es el caso del otro algoritmo, que el orden sea logarítmico sobre _k_ implica que en nuestro heap no tendremos nunca más de _k_ elementos. Pero recordemos que _k_ es la cantidad de archivos que tenemos. La idea es aprovechar el ordenamiento que tiene los archivos desde el inicio. 

El primer elemento en cada archivo es el menor de todos los elementos dentro de cada uno de ellos. Digamos, en el primer archivo el primer elemento es el más chico entre todos los elementos del primer archivo (o a lo sumo, igual).

Eso quiere decir, que el menor entre todos los _K_ primeros va a ser el menor de todos los _n_ elementos, entonces va a ser el primer elemento, si o si, del archivo (o archivo) final. Ahora tenemos que ver cuál va a ser el segundo. Pero, no es posible que el segundo elemento sea también proveniente del archivo del que vino el más chico que sacamos antes? Por ejemplo, si tenemos los archivos [0, 1, 2] y [2, 3, 4], los dos elementos más chicos vienen del primer archivo. Entonces, tenemos que conseguir siempre comprar _k_ elementos, pero cuanod sacamos uno, entonces quedarnos con _su sucesor_. Ya sabiendo que vamos a comprar _k_ cosas, podemos usar el heap de manera similar:
1. Creamos un heap de minimos (o de máximos con función de comparación alternada).
2. Guardamos el primer elemento de cada archivo. Importante: vamos a necesitar poder reconstruir de dónde vino ese elemento, por lo que no se puede encolar así nada más. Será necesario crear una estructura ad-hoc solamente para este fin, y guardar: el elemento en si y el número de archivo del que vino. La función de comparación solo debe tener en cuenta lo primero. 
3. Sacamos un elemento del heap, que sabemos será el menor de todos, por lo que será el primer elemento de nuestro archivo final (por lo que directamente deberíamos escribirlo).
4. Agarramos el siguiente elemento del archivo del cual provino ese elemento anterior (simplemente lo leemos), y lo guardamos en el heap. Si el archivo ya fue completamente leido, salteamos esto porque ya terminamos de procesarlo. 
5. Si el heap aun tiene elementos, volvemos al paso 3. 
6. Sino, entonces el algoritmo termina y ya tenemos nuestro archivo ordenado. 

Dado que se hacen _n_ encolar y desencolar en un heap que siempre tiene a lo sumo _k_ elementos, cada operación es _O(log k)_, al ser _n_ las veces que se hace: _O(n log k)_.

## Generar particiones ordenadas

Veremos 3 implementaciones para esto. Una particularidad: el valor de _n_ no puede cambiar (depende del archivo original), pero si podemos ver de manejar el valor de _k_. Cuanto menor cantidad de particiones ordenadas genermos, menor costo tendremos a la hora de hacer el merge ordenado explicado arriba. 


Para los 3 algoritmos propuestos vamos a suponer que tenemos una cota _C_ de elemenos máximos que podemos tener en memoria. Nunca podemos tener más de _C_ elementos en memoria. El valor de _C_ óptimo será cuestión de experimentación, o de poner un valor razonable. 

### Opcion 1: Ordenamientos internos
1. Cargar _C_ elementos en memoria (por ejemplo, en un arreglo), y ordenarlos con algún algoritmo eficiente. 
2. Escribir el arreglo ordenado en un archivo (partición).
3. Repetir lo anterior hasta terminar el archivo original. 

Este algoritmo permite crear particiones de tamaño _C_, por lo que tendremos _n/C_ particiones. 

### Opcion 2: Replacement-Selection sort
1. Crear un heap de mínimos, y una lista (podría ser otra estructura similar).
2. Poner _C_ elementos del archivo en un heap de mínimos. Así, el heap quedará "lleno".
3. Escribir en el archivo el primer elemento del heap (el menor dentro del heap). Con eso, liberamos algo de memoria.
4. Leemos un nuevo elemento del archivo original. 
5. Si el elemento que acabamos de leer es mayor o igual al que acabábamos de sacar, simplemente lo encolamos sin más.
6. Si en cambio, el elemento fuera menor que el que sacamos antes, lo guardamos en la lista (lo veremos más adelante). De esta manera, nuestro heap tendrá un elemento menos.  
7. Si aún quedan elementos en el heap, volvemos al paso 3. 
8. Si no quedan más elementos, cerramos la partición actual, y creamos otra. Pasamos todos los elementos de la lista al heap (que debería tener _C_ elementos). Podemos hacer esto creando el heap desde un arreglo para que sea en _O(n)_. Volvemos al paso 2. 

Si en cualquier momento el archivo ya no tiene más elementos, simplemente obviamos la acción de guardar un nuevo elemento en el heap. 

Este algoritmo permite tener particiones de, en promedio, _2C_ elementos, teniendo en total _n/2C_ particiones. 

[Aquí](https://www.youtube.com/watch?v=m0v-trXc2yI) un video donde se hace un seguimiento del algoritmo. 

### Opción 3: Natural-Selection sort

Similar al anterior, pero en vez de guardar los archivos en una lista, los guardamos en disco, y nos aseguramos de guardar hasta _C_ elementos en ese archivo temporal. Cuando llegamos a _C_ elementos en el archivo, simplemente escribimos todo el heap en la partición que estábamos armando, y cargamos los elementos del archivo temporal. 

Antes, al toparnos con que teníamos _C_ elementos en la lista, no teníamos nada para guardar, pero ahora vamos a tener _C_ elementos (los que quedaron en el heap, que siempre va a tener _C_ elementos, salvo en el caso final que tendrá uno menos). Entonces, en vez de generar particiones de _2C_, las genera de tamaño _3C_, teniendo entonces _N/3C_ particiones. La contra en este caso es tener que cargar los elementos del archivo temporal provenientes de disco. 


### Costo de generar las particiones

En cualquiera de los casos, notar que siempre estaremos trabajando con un heap con _C_ elementos, y de alguna forma u otra guardaremos todos los elementos en el heap, por lo tanto, el orden de realizar estas operaciones es _O(n log c)_. 

## Costo Total

Teniendo que _k_ valdrá _O(n/C)_ (con alguna constante dividiendo: 1, 2 o 3), tendrémos que nuestro algoritmo finalmente será: 

	_SortExterno(n) = O(particiones ordenadas) + O(merge)_
	_SortExterno(n) = _O(n log c)_ + O(n log n/c) = O(n log c) + O(n log n) - O(n log c) = O(n log n)_

Con eso comprobamos que, lógicamente, nuestro algoritmo ordena en _O(n log n)_. Ahora bien: para qué, si a cuestiones del orden no nos importa si generamos más o menos particiones, deberíamos darle importancia? Primero, porque a grandes rasgos es una buena optimización. Pero más importante: estamos hablando de operaciones de lectura y escritura sobre disco. Dichas operaciones toman más tiempo que muchas otras operaciones (si bien ese tiempo sigue siendo constante, es muy grande). Por esto, es que planteamos como posibles mejoras tanto Replacement Selection como Natural Selection. 

Recomendaciones
--------------
A la hora de trabajar con accesos a disco, es importante tener en cuenta que a menos que trabajen con un disco de estado solido (sdd), leer seguido puede ser una operación costosa, y lo mismo con escribir. 
Pueden utilizar tanto getline como cualquier otra función ya vista, pero recomendamos:
* Para lecturas: no usar getline, sino algo que les permita leer directamente una mayor cantidad de bytes de un solo acceso a disco¸usando fread. Tendrán que tener en cuenta que tendrán que separar ustedes por los \n (sencillo utilizando el `split` ya implementado, y mucho más veloz por utilizar accesos a memoria volátil). Cuidado! Recuerden que la "última linea" podría haber quedado incompleta al leer del archivo. 
* Para escrituras, hacer algún tipo de buffer. Pueden por ejemplo guardar en una lista o cola _n_ líneas (fijado por ustedes), luego unirlas (utilizando `join`), y finalmente escribirlas a disco. 
